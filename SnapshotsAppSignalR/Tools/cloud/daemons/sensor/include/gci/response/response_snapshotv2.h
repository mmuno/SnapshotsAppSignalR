#ifndef NETWORK_GCI_RESPONSE_SNAPSHOTV2_H
#define NETWORK_GCI_RESPONSE_SNAPSHOTV2_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <stdio.h>
#include <unistd.h>
#include <zmq.hpp>
#include "gci_avro.h"
#include <chrono>
#include "response.h"
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

/** \addtogroup Parser
 *  @{
 */

/**
 * @class GciResponseSnapshotV2
 *
 * @brief Specializes in handling the SnapshotV2 command
 *
 * class has 8 process states:\n 0: load nb of blocks\n 1: load filetime\n 2: load frame counter\n
 * 3: load sample frequency\n 4: load nb of channels\n 5: load all the channel names\n 6: load the number of samples\n
 * 7: load the data into vectors of unin16_t
 *
 */
class GciResponseSnapshotV2 : public GciResponse {
public:
	/**
	 * @brief this constructor loads a config file and then makes an init write into the shared memory
	 */
    GciResponseSnapshotV2() {
        load_config();
        _vectorizer.init(_nb_block, _avro_block_size);
        if (_test_mode)
		    _vectorizer.gen_data_filling(_nb_block);
    };

    void        data_handler(const char *content);

private:
    void        load_config();
    void        check_block_state();
    int         byte_swapper(const char *content, int begin, int len);

    void        print_infos_data();
    void        block_reset();
    void        new_frequency_reset();

    //handler made for the case an interger is written on two different blocks of data.
    void        unfinished_handler(const char * );
    void		buf_filler(int);
    void		buf_reset();
    void        buf_handler();
    void        evolving_infos_handler(const char *content);
    void        unique_infos_handler(const char *content);
    void        data_parser(const char *content);
	bool		data_filler(const char * content);

	void		init_recovery();
    bool		apply_recovery();

    uint32_t    WindowsTickToUnixSeconds(uint64_t windowsTicks);
    uint64_t    little_endian_filetime_to_big_endian(const char *content, int len);

    /**
     * @brief this structure's here to load the data header of SnapshotV2
     *
     * for more information refer to the GCI doc
     */
    typedef struct infos_data_s {
        uint8_t nb_blocks = 0;
        uint64_t filetime = 0;
        uint16_t frame_counter = 1;
        uint16_t sample_frequency = 0;
        uint8_t nb_chan = 0;

        vector<uint8_t> chan_IDs;
        uint16_t nb_sample;
        uint8_t nb_blocks_processed = 0;
    } infos_data_t;


    bool                        _test_mode;
	size_t 						_nb_block;
	int                         _data_size;
    int                         _avro_block_size;
    uint8_t                     _process_state = 0;
    infos_data_t                _infos_data;
    uint32_t                    _data_buf_it = 0;
    vector<uint16_t>            _data_buf;

	bool						_recovery = false;


	vector<vector<uint16_t>>    _14khz;
    vector<vector<uint16_t>>    _2khz;
    vector<vector<uint16_t>>    _1khz;

public:
	/**
	 * @brief this class transfer the data received into files or shared memory
	 *
	 *
	 */
    class GciVectorizer {
    public:
		GciVectorizer() : _context(1)
		{
            mkdir("avro_files", 0777);
		};
        ~GciVectorizer() { free(_buf); }
		void		init(int, int);
		void		gen_data_filling(int);

        void        vector_handler(const vector<vector<uint16_t>> &data, int mode);
        void        vector_to_avro(vector<vector<int32_t>> to_encode, int);
        void        vector_to_shm(size_t, size_t);
        void        open_and_merge(FILE *dataset, const char *channel);
        void        generate_dataset();

        void        add_channel(string name, string type);
        void        add_channel_offset(uint16_t);
        void        add_dataset_name(string);

        void        print_channels() const;
        void        print_channel_offsets() const;
        void        print_dataset_frequencies() const;

        /**deprecated, might still be usefull **/
        void        vectorize_into_file(const vector<vector<uint16_t>> &data, int mode);
        void        normalize_vector_into_file(const vector<vector<uint16_t>> &data, int mode);

    private:
        size_t                          _avro_block_size;
        string                          _file;
        /** frequencies loaded from the config file */
        vector<string>                  _dataset_frequency;
        /** offsets based on the number of channel per frequency in the config file */
        vector<uint16_t>				_channel_offsets;
        /** offset between each frequency within the shared memory */
        vector<uint32_t>				_shm_offsets;
        /** number and name of each channel according to the config file */
        vector<pair<string, string>>	_channels;
        std::vector<c::channels>        _avro_chans;
        zmq::context_t			_context;
		vector<zmq::socket_t *>	_publications;
		/** buffer containing the data to write into shared memory*/
		uint16_t						*_buf;
    };
private:
    GciVectorizer _vectorizer;
public:
    GciVectorizer &get_vectorizer() { return _vectorizer;}

};
/** @}*/

#endif //NETWORK_GCI_RESPONSE_SNAPSHOTV2_H
