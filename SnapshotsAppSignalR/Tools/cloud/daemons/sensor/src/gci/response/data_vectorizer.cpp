#include <cmath>
#include "response_snapshotv2.h"
#include "conf_loader.h"

// block size is the size of the type we write
#define NORMALIZATION_VARIABLE 1./65535.
int		g_block_size = sizeof(uint16_t);

static uint16_t int_to_uint(int16_t value, char type)
{
	if (type == 's')
		value += 32768;
	return value;
}

/**
 *
 * @param nb_blocks number of blocks received to generate
 *
 * @brief Debug function, generate data in order to fill the shared memory.
 *
 * @note 1 block = 50ms of data
 */
void GciResponseSnapshotV2::GciVectorizer::gen_data_filling(int nb_blocks)
{
	vector<vector<uint16_t>> whole_data;
	srand(time(0));

	while(1) {
		for (int mode = 0; mode < 3; mode++) {
			uint32_t frequency = atoi(_dataset_frequency[mode].c_str());
			vector <uint16_t> data;

			for (int x = 0; x < nb_blocks ; x++) {
				uint16_t i = _channel_offsets[mode] + 1;
				for (uint32_t y = 0; y < frequency / 20 * (_channel_offsets[mode + 1] - _channel_offsets[mode]); y++) {
					data.emplace_back(i * 1000 + rand());
					if (i == _channel_offsets[mode + 1])
						i = _channel_offsets[mode] + 1;
					else
						i++;
				}
				whole_data.emplace_back(data);
			}
			Timer tt;
			tt.start("start");
			vector_handler(whole_data, mode);
			tt.stop_print("start", "stop", true);
			whole_data.clear();
		}
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

/**
 *
 * @param nb_blocks number of block that we have to put into the shared memory
 *
 * @brief Write the headers into the shared memory.
 *
 * The offset of the headers are calculated thanks to the config file loaded by GciResponseSnapshotV2().
 * @note frequency, nb channels, nb samples and nb_blocks all depends on the configuration file
 */
void GciResponseSnapshotV2::GciVectorizer::init(int nb_blocks, int avro_block_size) {
	ConfLoader::Parser pars;
	ConfLoader::Ipc ipc;
	int i = 0;
	_avro_block_size = avro_block_size;

	/** allocating space for the buffer that we'll use to write into the shared memory */
	if ((_buf = (uint16_t *) malloc(14000 * nb_blocks)) == NULL)
		throw ERROR_MEMORY_ALLOC;

	_dataset_frequency = pars.get_channel_names();
	_channel_offsets = pars.get_channel_offsets();
	_channels = pars.get_channels();
	for (size_t x = 0; x < _channels.size(); x++) {
		for (auto &name : ipc.get_ipc_names()) {
		  if (name.find(_channels[x].first) == strlen("/dev/shm/")) {
				std::string path("ipc://" + name);
				Logs::parser_log(string(path + "\n").c_str(), 1);
				_publications.emplace_back(new zmq::socket_t(_context, ZMQ_PUB));
				_publications[i]->bind(path);
				i++;
			}
		}
	}
	cout << "data vectorizer init finished" << endl;
}

avro::ValidSchema loadSchema(const char* filename)
{
    std::ifstream ifs(filename);
    avro::ValidSchema result;
    avro::compileJsonSchema(ifs, result);
    return result;
}


/**
 * this function writes the data concerned the different channel in a new avro file.
 * The name of the file correspond to is creation date (UNIX TIMESTAMP)
 * @param chans
 * @return
 */
void save_avro_in_file(std::vector<c::channels> chans)
{
    Timer t;

    std::cout << "in thread" << std::endl;
    t.start("tart");
    avro::ValidSchema schema = loadSchema("cpx.json");
    std::chrono::milliseconds ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    std::string file_name = std::string("avro_files/" + std::to_string(ms.count()) + ".avro");
    avro::DataFileWriter<c::channels> dfw(file_name.c_str(), schema);
    std::cout << chans.size() << std::endl;
    for (auto chan : chans)
        dfw.write(chan);
    dfw.close();
    t.stop_print("tart", "gra", true);

    /*avro::DataFileReader<c::channels> dfr(file_name.c_str(), schema);
    c::channels c2;
    try {
        while (dfr.read(c2)) {
            std::cout << '(' << c2.PositionV13.size() << ", " << c2.PositionW13.size() << ')' << std::endl;
        }
    }
    catch (const std::exception&e) { std::cout << e.what() << std::endl; }
    dfr.close();*/
}

/**
 * This function gather the data received from MBCSI into RAM until the maximum size (defined in conf/parser.yaml) is reached
 * on this size have been reached a thread is created to write the data into a new avro file
 *
 * @note we're creating a thread to write the data so we don't lose any incoming information from mbsci
 *  because the data writing can be quite long depending on the buffer size.
 *
 * @param to_encode here are the values to encode (all channels contained in a frequency)
 * @param mode actual frequency that's being handled
 */
void GciResponseSnapshotV2::GciVectorizer::vector_to_avro(vector<vector<int32_t>> to_encode, int mode)
{
    static c::channels chan;

    /**
     * this means that we don't want to generate avro files
     */
    if (_avro_block_size <= 0)
        return;

    if (mode == 0) {
        chan.PositionV13 = to_encode[0];
        chan.PositionW13 = to_encode[1];
        chan.PositionV24 = to_encode[2];
        chan.PositionW24 = to_encode[3];
        chan.PositionV57 = to_encode[4];
        chan.PositionW57 = to_encode[5];
        chan.Positionz1 = to_encode[6];
        chan.PositionZ12 = to_encode[7];
        chan.CommandeV1 = to_encode[8];
        chan.CommandeV3 = to_encode[9];
        chan.CommandeV2 = to_encode[10];
        chan.CommandeV4 = to_encode[11];
        chan.CommandeV5 = to_encode[12];
        chan.CommandeV7 = to_encode[13];
        chan.CommandeW1 = to_encode[14];
        chan.CommandeW3 = to_encode[15];
        chan.CommandeW2 = to_encode[16];
        chan.CommandeW4 = to_encode[17];
        chan.CommandeW5 = to_encode[18];
        chan.CommandeW7 = to_encode[19];
        chan.Commandez1 = to_encode[20];
        chan.CommandeZ2 = to_encode[21];
        chan.TDCBit = to_encode[22];
    }
    else if (mode == 1) {
        chan.CurrentV1 = to_encode[0];
        chan.CurrentV3 = to_encode[1];
        chan.CurrentV2 = to_encode[2];
        chan.CurrentV4 = to_encode[3];
        chan.CurrentV5 = to_encode[4];
        chan.CurrentV7 = to_encode[5];
        chan.CurrentW1 = to_encode[6];
        chan.CurrentW3 = to_encode[7];
        chan.CurrentW2 = to_encode[8];
        chan.CurrentW4 = to_encode[9];
        chan.CurrentW5 = to_encode[10];
        chan.CurrentW7 = to_encode[11];
        chan.CurrentZ1 = to_encode[12];
        chan.CurrentZ2 = to_encode[13];
        chan.CurrentZ3 = to_encode[14];
        chan.CurrentZ4 = to_encode[15];
    }
    else {
        chan.Rotation_Frequency_A = to_encode[0];
        chan.Rotation_Frequency_B = to_encode[1];
        chan.SPV_speed_A = to_encode[2];
        chan.SPV_speed_B = to_encode[3];
        chan.UnbalanceA13 = to_encode[4];
        chan.UnbalanceB13 = to_encode[5];
        chan.UnbalanceA24 = to_encode[6];
        chan.UnbalanceB24 = to_encode[7];
        chan.UnbalanceA57 = to_encode[8];
        chan.UnbalanceB57 = to_encode[9];
        chan.AxialHarmonic1A = to_encode[10];
        chan.AxialHarmonic1B = to_encode[11];
        chan.MachineTemp_1_A = to_encode[12];
        chan.MachineTemp_2_A = to_encode[13];
        chan.MachineTemp_3_A = to_encode[14];
        chan.MachineTemp_4_A = to_encode[15];
        chan.MachineTemp_5_A = to_encode[16];
        chan.MachineTemp_6_A = to_encode[17];
        chan.MachineTemp_7_A = to_encode[18];
        chan.MachineTemp_8_A = to_encode[19];
        chan.MachineTemp_1_B = to_encode[20];
        chan.MachineTemp_2_B = to_encode[21];
        chan.MachineTemp_3_B = to_encode[22];
        chan.MachineTemp_4_B = to_encode[23];
        chan.MachineTemp_5_B = to_encode[24];
        chan.MachineTemp_6_B = to_encode[25];
        chan.MachineTemp_7_B = to_encode[26];
        chan.MachineTemp_8_B = to_encode[27];
        chan.coilTempV1 = to_encode[28];
        chan.coilTempV3 = to_encode[29];
        chan.coilTempv2 = to_encode[30];
        chan.coilTempv4 = to_encode[31];
        chan.coilTempv5 = to_encode[32];
        chan.coilTempV7 = to_encode[33];
        chan.coilTempw1 = to_encode[34];
        chan.coilTempW3 = to_encode[35];
        chan.coilTempW2 = to_encode[36];
        chan.coilTempW4 = to_encode[37];
        chan.coilTempW5 = to_encode[38];
        chan.coilTempW7 = to_encode[39];
        chan.coilTempZI = to_encode[40];
        chan.coilTempZ2 = to_encode[41];
        chan.coilTempz3 = to_encode[42];
        chan.coilTempZ4 = to_encode[43];
        chan.peakPositionv13 = to_encode[44];
        chan.peakPositionW13 = to_encode[45];
        chan.peakPositionV24 = to_encode[46];
        chan.peakPositionW24 = to_encode[47];
        chan.peakPositionV57 = to_encode[48];
        chan.peakPositionW57 = to_encode[49];
        chan.peakPositionz1 = to_encode[50];
        chan.peakPosition22 = to_encode[51];
        chan.PeakElongation_Rotor_SPV = to_encode[52];
        chan.VDCMains = to_encode[53];
        chan.VDCPA_V13 = to_encode[54];
        chan.VDCPA_W13 = to_encode[55];
        chan.VDCPA_V24 = to_encode[56];
        chan.VDCPA_W24 = to_encode[57];
        chan.VDCPA_V57 = to_encode[58];
        chan.VDCPA_W57 = to_encode[59];
        chan.VDCPA_Z12 = to_encode[60];
        chan.VDCPA_234 = to_encode[61];
        chan.AmplifierTempv13 = to_encode[62];
        chan.AmplifierTempW13 = to_encode[63];
        chan.AmplifierTempv24 = to_encode[64];
        chan.AmplifierTempW24 = to_encode[65];
        chan.AmplifierTempV57 = to_encode[66];
        chan.AmplifierTempW57 = to_encode[67];
        chan.AmplifierTempz12 = to_encode[68];
        chan.AmplifierTempz34 = to_encode[69];
        chan.ISO_Bear_A = to_encode[70];
        chan.ISO_Det_A = to_encode[71];
        chan.ISO_Bear_B = to_encode[72];
        chan.ISO_Det_B = to_encode[73];
        chan.RadialHarmonicN2A13 = to_encode[74];
        chan.RadialHarmonicN2B13 = to_encode[75];
        chan.RadialHarmonicN2A24 = to_encode[76];
        chan.RadialHarmonicN2824 = to_encode[77];
        chan.RadialHarmonicN2A57 = to_encode[78];
        chan.RadialHarmonicN2B57 = to_encode[79];
        chan.AxialHarmonicN2A = to_encode[80];
        chan.AxialHarmonicN2B = to_encode[81];
    }
    if (mode == 2) {
        _avro_chans.emplace_back(chan);
        if (_avro_chans.size() == _avro_block_size) {
            std::thread{save_avro_in_file, std::move(_avro_chans)}.detach();
        }
    }
}

void GciResponseSnapshotV2::GciVectorizer::vector_to_shm(size_t channel_sample, size_t x)
{
    zmq::message_t message(channel_sample * g_block_size);
    memcpy(message.data(), _buf, channel_sample * g_block_size);
    _publications[x]->send(message);
}

/**
 * @param data the data received from MBCSI put together in a vector
 * @param mode defines on what kind of frequency we're working\n
 *  mode 0: the first frequency loaded from the config file\n
 *  mode 1: the second frequency loaded from the config file and so on...
 *
 *  @brief Write the data received into shared memories files (one file per channel)
 *
 *  @note using zmq library for ipc transmission
 */
void GciResponseSnapshotV2::GciVectorizer::vector_handler(const vector<vector<uint16_t>> &data, int mode)
{
    vector<vector<int32_t>> to_encode;
    size_t		nb_channels = (_channel_offsets[mode + 1] - _channel_offsets[mode]);
    size_t		nb_samples = atoi(_dataset_frequency[mode].c_str()) / 20; 	/** we divide the frequency per 20 since the frequency is on 1 sec but we got blocks of 50 ms*/
    size_t		channel = 0;
    size_t		channel_sample = 0;

    if (mode > 3 || mode < 0)
        throw ERROR_PARSER_MODE;

    for (size_t x = _channel_offsets[mode] ; x < _channel_offsets[mode + 1] ; x++) {
        channel_sample = 0;
        vector<int32_t> line_to_encode;
        for (auto &y: data) {
            for (size_t sample = 0; sample < nb_samples ; sample++) {
                _buf[channel_sample] =
                        int_to_uint(y[nb_channels * sample + channel], _channels[x].second[0]);
                line_to_encode.emplace_back(int_to_uint(y[nb_channels * sample + channel], _channels[x].second[0]));
                channel_sample++;
            }
        }
        to_encode.emplace_back(line_to_encode);
        vector_to_shm(channel_sample, x);
        channel+=1;
    }
    vector_to_avro(to_encode, mode);
}

static void check_file_is_open(FILE *to_check)
{
    if (to_check == NULL)
        throw ERROR_LOAD_FILE;
}

static char *my_read_file(const char *name, uint32_t *len_file)
{
    FILE *file;
    char *buffer;
    int ret;

    file = fopen(name, "rb");
    if (!file)
        throw ERROR_LOAD_FILE;

    fseek(file, 0, SEEK_END);
    *len_file=ftell(file);
    rewind(file);

    if ((buffer = (char *)malloc(*len_file + 1)) == NULL)
        throw ERROR_MEMORY_ALLOC;
    if ((ret = fread(buffer, *len_file, 1, file)) == -1)
        throw ERROR_LOAD_FILE;
    fclose(file);

    return buffer;
}

/**
 * deprecated, legacy code (might still be usefull)
 *
 * @param data the data received from MBCSI put together in a vector
 * @param mode defines on what kind of frequency we're working\n
 *  mode 0: the first frequency loaded from the config file\n
 *  mode 1: the second frequency loaded from the config file and so on...
 *
 *  @brief Write the data received into temporary files (one file per channel).
 *
 *  @note the temporary files are merged at the end of the program, once
 */
void GciResponseSnapshotV2::GciVectorizer::vectorize_into_file(const vector<vector<uint16_t>> &data, int mode)
{
    vector<ofstream *>  files;
    FILE *              fptr;
    ifstream            file;
    size_t              nb_channels = (_channel_offsets[mode + 1] - _channel_offsets[mode]);
    size_t              nb_samples = data.size() / nb_channels;
    size_t              channel = 0;

    if (mode > 3 || mode < 0)
        throw ERROR_PARSER_MODE;

    for (size_t x = _channel_offsets[mode] ; x < _channel_offsets[mode + 1] ; x++) {
        if ((fptr = fopen(("tmp/" + _channels[x].first + ".tmp").c_str(),"a+b")) == NULL)
            throw ERROR_LOAD_FILE;
        for (auto &y : data) {
            for (size_t samples = 0; samples < nb_samples ; samples++) {
                fwrite(&y[nb_channels * samples + channel], sizeof(uint16_t), 1, fptr);
            }
        }
        channel+=1;
        fclose(fptr);
    }
}

/**
 * deprecated, legacy code (might still be usefull)
 * @param data the data received from MBCSI put together in a vector
 * @param mode defines on what kind of frequency we're working\n
 *  mode 0: the first frequency loaded from the config file\n
 *  mode 1: the second frequency loaded from the config file and so on...
 *
 *  @brief Normalize the data received (between -1 & 1) write the data received into temporary files (one file per channel).
 */
void GciResponseSnapshotV2::GciVectorizer::normalize_vector_into_file(const vector<vector<uint16_t>> &data, int mode)
{
    vector<ofstream *>  files;
    FILE *              fptr;
    ifstream            file;
    size_t              nb_channels = (_channel_offsets[mode + 1] - _channel_offsets[mode]);
    size_t              nb_samples = data.size() / nb_channels;
    size_t              channel = 0;
    uint16_t            value;
    float               to_write = 0;

	if (mode > 3 || mode < 0)
        throw ERROR_PARSER_MODE;

    for (size_t x = _channel_offsets[mode] ; x < _channel_offsets[mode + 1] ; x++) {
        if ((fptr = fopen(("tmp/" + _channels[x].first + ".tmp").c_str(),"a+b")) == NULL)
            throw ERROR_LOAD_FILE;
        for (auto &y : data) {
            for (size_t sample = 0; sample < nb_samples ; sample++) {
                value = int_to_uint(y[nb_channels * sample + channel], _channels[x].second[0]);
                to_write = 2*(value * NORMALIZATION_VARIABLE) -1;
                fwrite(&to_write, sizeof(float), 1, fptr);
            }
        }
        channel+=1;
        fclose(fptr);
    }
}

/**
 * deprecated, legacy code (might still be usefull)
 *
 * @param dataset the file in which all the tmp files will be append
 * @param channel the actual channel that will be append to the dataset
 *
 * @brief open a tmp file, append it to the dataset
 *
 * @note refer to the class description to see the header format
 *
 */
void GciResponseSnapshotV2::GciVectorizer::open_and_merge(FILE *dataset, const char *channel)
{
    char *              buffer;
    uint32_t            len_file;
    uint8_t             to_write;
    static uint16_t     id = 0;

    buffer = my_read_file(channel, &len_file);

    //writing the channel id
    fwrite(&id, sizeof(uint16_t), 1, dataset);

    to_write = g_block_size;
    //writing the size of one block
    fwrite(&to_write, sizeof(uint8_t), 1, dataset);

    //writing the size of the channel
    fwrite(&len_file, sizeof(uint32_t), 1, dataset);
    fwrite(buffer, len_file, 1, dataset);
    id++;
}

/**
 * @brief Create a dataset with the data stocked while the program was running (if activated in config file).
 *
 * This dataset is generated from all the temporary files we wrote during the runtime Cf  GciResponseSnapshotV2::GciVectorizer::normalize_vector_into_file().
 */
void GciResponseSnapshotV2::GciVectorizer::generate_dataset()
{
    FILE *          dataset;
    int             dataset_it = 1;

    if ((dataset = fopen(_dataset_frequency[0].c_str(), "wb")) == NULL)
        throw ERROR_LOAD_FILE;
    check_file_is_open(dataset);
    for (int x = 0 ; x  < _channel_offsets[3] ; x++) {

        open_and_merge(dataset, ("tmp/" + _channels[x].first + to_string(std::time(nullptr)) + ".tmp").c_str());
        if (x + 1 == _channel_offsets[dataset_it] && dataset_it < 3) {
            fclose(dataset);
            dataset = fopen(_dataset_frequency[dataset_it].c_str(), "wb");
            check_file_is_open(dataset);
            dataset_it++;
        }
        if (remove(("tmp/" + _channels[x].first + ".tmp").c_str()) != 0)
            throw ERROR_DELETING_FILE;
    }
}

void GciResponseSnapshotV2::GciVectorizer::add_channel(string name, string type)
{
    _channels.emplace_back(make_pair(name, type));
}

void GciResponseSnapshotV2::GciVectorizer::add_channel_offset(uint16_t value)
{
    _channel_offsets.emplace_back(value);
}

void GciResponseSnapshotV2::GciVectorizer::add_dataset_name(string name)
{
    _dataset_frequency.emplace_back(name);
}

void GciResponseSnapshotV2::GciVectorizer::print_channels() const
{
    for (auto &channel : _channels)
        cout << channel.first << endl;
}

void GciResponseSnapshotV2::GciVectorizer::print_channel_offsets() const
{
    for (auto &offset : _channel_offsets)
        cout << offset << endl;
}

void GciResponseSnapshotV2::GciVectorizer::print_dataset_frequencies() const
{
    for (auto &name : _dataset_frequency)
        cout << name << endl;
}