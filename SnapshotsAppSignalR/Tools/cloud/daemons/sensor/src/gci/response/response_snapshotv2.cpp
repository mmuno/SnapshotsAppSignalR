//
// Created by cjdcoy on 4/11/19.
//

#include "response_snapshotv2.h"
#include "yaml-cpp/yaml.h"
#include "conf_loader.h"

#define WINDOWS_TICK 10000000
#define SEC_TO_UNIX_EPOCH 11644473600LL


/**
 *
 * @param path path to the config file to be loaded
 *
 * This loader's purpose is to know the frequencies, channels received from MBSCOPE.
 * Those variables must really reflect the data received otherwise the program wont work.
 */
void        GciResponseSnapshotV2::load_config()
{
	ConfLoader::Parser	loader;
	_nb_block = loader.get_nb_blocks();
	_avro_block_size = loader.get_avro_block_size();
    _test_mode = loader.get_test_mode();
}

uint32_t    GciResponseSnapshotV2::WindowsTickToUnixSeconds(uint64_t windowsTicks)
{
    return (uint32_t)(windowsTicks / WINDOWS_TICK - SEC_TO_UNIX_EPOCH);
}

uint64_t    GciResponseSnapshotV2::little_endian_filetime_to_big_endian(const char *content, int len)
{
	char		buf[len + 1];
    memset(buf, 0, sizeof(uint8_t) * len + 1);
    int begin = 0;
    int end = len -1;

    while (begin < len) {
        buf[begin] = content[_pos + end];
        end--; begin++;
    }
    return get_int(buf, 0, len);
}

/**
 *
 * @param content pointer on the data
 * @param begin offset to the data
 * @param len length of the data
 *
 * Transform a 2bytes lsb to msb.
 *
 * @return the bytes swapped
 */
int         GciResponseSnapshotV2::byte_swapper(const char *content, int begin, int len)
{
    uint16_t tmp = get_int(content, begin, begin + len);
    int final = (((tmp & 0x00ff) << 8) & 0xff00) | (((tmp & 0xff00) >> 8) & 0x00ff);
    return final;
}

/**
 * Reset the loader if all the data of a frequency withing a block (block = 50ms) have been caught
 */
void        GciResponseSnapshotV2::new_frequency_reset()
{
    _data_buf_it = 0;
    _process_state = 3;
    _infos_data.chan_IDs.clear();
    _data_buf.clear();
}

/**
 *
 * @param content pointer on the data received
 *
 * @brief Handles states 0 -> 2.
 *
 * @note for more information about the different states refer to this class detailed description
 */
void        GciResponseSnapshotV2::unique_infos_handler(const char *content)
{
    switch(_process_state) {
        case 0:
            _data_size = sizeof(_infos_data.nb_blocks);
            _infos_data.nb_blocks = (uint8_t)get_int(content, _pos, _pos + _data_size);
            break;
        case 1: //timestamp
            _data_size = sizeof(_infos_data.filetime);
            _infos_data.filetime = little_endian_filetime_to_big_endian(content, _data_size);
            break;
        case 2:
            _data_size = sizeof(_infos_data.frame_counter);
            _infos_data.frame_counter = (uint16_t)get_int(content, _pos, _pos + _data_size);
            break;
    }
    _process_state+=1;
    _pos += _data_size;
}

void        GciResponseSnapshotV2::init_recovery()
{
	if (_recovery == false)
		Logs::parser_log("recovery initiated\n", 1);
	block_reset();
	buf_reset();
	_recovery = true;
	_pos = _content_size;
	_process_state = 0;
}

bool		GciResponseSnapshotV2::apply_recovery()
{
	if (_recovery == false)
		return false;
	else {
		if (_header.block_number == 1) {
			_recovery = false;
			Logs::parser_log("recovery finished\n", 1);
			return false;
		}
		else {
			init_recovery();
			return true;
		}
	}
}

/**
 * @param content pointer on the data received
 *
 * @brief Handles states 3-> 4.
 *
 * @note for more information about the different states refer to this class detailed description
 */
void        GciResponseSnapshotV2::evolving_infos_handler(const char *content)
{
    switch (_process_state) {
        case 3:
            _data_size = sizeof(_infos_data.sample_frequency);
            _infos_data.sample_frequency = (uint16_t)byte_swapper(content, _pos, _data_size);
            if (_infos_data.sample_frequency != 14000 && _infos_data.sample_frequency != 2000 && _infos_data.sample_frequency != 1000) {
				Logs::parser_log(string("block number: " + to_string(_header.block_number) + ", frequency not recognized " + to_string(_pos) + "\n").c_str(), 1);
                init_recovery();
                return;
            }
            break;
        case 4:
            _data_size = sizeof(_infos_data.nb_chan);
            _infos_data.nb_chan = (uint8_t)get_int(content, _pos, _pos + _data_size);
            break;
    }
    _process_state+=1;
    _pos += _data_size;
}

/**
 *
 * @param content pointer on the data received
 *
 * If a variable is half written on a packet (1 byte on actual packet and 1 byte on the next)
 * this function stock the variable and inform the class that there's a data in an unfinished state.
 */
void        GciResponseSnapshotV2::unfinished_handler(const char *content)
{
    _unfinished = false;
    char buf[2] = {0};

    buf[0] = _unfinished_value;
    buf[1] = content[_pos];
    _data_buf[_data_buf_it] = byte_swapper(buf, 0, 2);
    _data_size = 1;
}

void		GciResponseSnapshotV2::buf_filler(int bufid)
{
	switch (bufid) {
		case 0:
			_14khz.emplace_back(_data_buf);
			break;
		case 1:
			_2khz.emplace_back(_data_buf);
			break;
		case 2:
			_1khz.emplace_back(_data_buf);
			break;
		default:
			throw ERROR_FILL_BUFFER;
	}
}

bool		GciResponseSnapshotV2::data_filler(const char * content)
{
	if (_pos + 1 == _content_size - 2) {
		_unfinished = true;
		_unfinished_value = content[_pos];
		_pos +=2;
		return true;
	}

	if (_unfinished == true)
		unfinished_handler(content);
	else
		_data_buf[_data_buf_it] = byte_swapper(content, _pos, _data_size);

	if (_data_buf_it >= (_infos_data.nb_chan * _infos_data.nb_sample)) {
		if (_infos_data.sample_frequency == 14000)
			buf_filler(0);
		else if (_infos_data.sample_frequency == 2000)
			buf_filler(1);
		else {
			Logs::parser_log("ERROR IN DATA SAMPLE FREQUENCY: FREQUENCY NOT RECOGNIZED", 1);
			init_recovery();
			return true;
		}
		new_frequency_reset();
		return true;
	}
	return false;
}

/**
 *
 * @param content pointer on the data received
 *
 * @brief Handles states 5 -> 7.
 *
 * @note for more information about the state refer to this class's detailed description
 */
void        GciResponseSnapshotV2::data_parser(const char *content)
{
    switch(_process_state) {
        case 5:
            _data_size = sizeof(uint8_t);
            _infos_data.chan_IDs.emplace_back((uint8_t)get_int(content, _pos, _pos + _data_size));
            if (_infos_data.chan_IDs.size() == _infos_data.nb_chan)
                _process_state+=1;
            break;
        case 6:
            _data_size = sizeof(uint16_t);
            _infos_data.nb_sample = byte_swapper(content, _pos, _data_size);
            _data_buf.resize((_infos_data.nb_chan * _infos_data.nb_sample) + 1);
            _data_buf_it = 0;
            _process_state+=1;
            break;
        case 7:
			_data_size = sizeof(uint16_t);
			if (data_filler(content) == true)
				return;
			_data_buf_it+=1;
			break;
    }
    _pos += _data_size;
}

/**
 * @brief Once a block (50ms of data) has been process, reset the program to its initial state.
 */
void        GciResponseSnapshotV2::block_reset()
{
    _infos_data.nb_blocks_processed = 0;
    _infos_data.chan_IDs.clear();
    _data_buf_it = 0;
    _process_state = 0;
    _pos = _content_size;
}

void		GciResponseSnapshotV2::buf_reset()
{
	_14khz.clear();
	_2khz.clear();
	_1khz.clear();
}

/**
 * Once the buffers are full (buffer size == nb blocks) the data is transferred into a shared memory.
 */
void        GciResponseSnapshotV2::buf_handler()
{
	cout << "buffer handler took ";
	_timer.start("buf_handler");
    _vectorizer.vector_handler(_14khz, 0);
    _vectorizer.vector_handler(_2khz, 1);
    _vectorizer.vector_handler(_1khz, 2);
    buf_reset();
	_timer.stop_print("buf_handler", "test", true);
}

/**
 * @brief Verify if caught all the data of 1 block (50 ms of data).
 *
 * Verifies if all the data of 1 block have been processed.
 * If yes, it calls  GciResponseSnapshotV2::buf_handler() else it keeps on processing the data received
 */
void        GciResponseSnapshotV2::check_block_state()
{
	/* in case of recovery mode we just want to wait for the new block to arrive */
	if (_recovery == true)
		return;

    /* verification with -2 so we skip the CRC */
    if (_pos >= _content_size -2)
        _infos_data.nb_blocks_processed += 1;

    if (_infos_data.nb_blocks_processed == _infos_data.nb_blocks) {
    	buf_filler(2);
		/* reset positions to prepare for the new block incoming */
		block_reset();
        _timer.incr_blocks_received();
        /* this allows bufferize X number of blocks (1block = 50ms) */
        if (_14khz.size() == _nb_block)
            buf_handler();
    }
}

/**
 *
 * @param content pointer on the data received
 *
 * @brief Assign work accordingly to to process state.
 *
 * @note for more information about the state refer to this class's detailed description
 */
void        GciResponseSnapshotV2::data_handler(const char *content)
{
    if (apply_recovery() == true) return;

	if (_process_state <= 2) {
		unique_infos_handler(content);
	}
	else if (_process_state >= 3 && _process_state <= 4) {
		evolving_infos_handler(content);
	}
    else {
		data_parser(content);
	}
    check_block_state();
}

/**
 * @brief Debug function that prints the data header.
 */
void        GciResponseSnapshotV2::print_infos_data() {
    cout << "_______________ INFOS DATA content _______________" << endl;
    cout << "nb_blocks: " << _infos_data.nb_blocks + 0 << endl;
    cout << "filetime: " << _infos_data.filetime << endl;
    cout << "counter: " << _infos_data.frame_counter + 0 << endl;
    cout << "sample_frequency: " << _infos_data.sample_frequency + 0 << endl;
    cout << "nb_chan: " << _infos_data.nb_chan + 0 << endl;
    cout << "nb_sample: " << _infos_data.nb_sample + 0 << endl;
    cout << "______ finished printing infos data content ______" << endl;
}