#ifndef SKF_CLOUD_CONF_LOADER_H
#define SKF_CLOUD_CONF_LOADER_H

#include <vector>
#include <string>

#include "yaml-cpp/yaml.h"
#include "timer.h"
#include "errors.h"

#define IPC_PATH		"../../conf/ipc_mapping.yaml"

#define PARSER_PATH		"conf/parser.yaml"
#define NETWORK_PATH	"conf/mapping_network.yaml"


namespace ConfLoader {
	class Parser {
	public:
		Parser() { run(); }
		~Parser() {}
		void	run();

        int                             get_test_mode() { return _test_mode; }
        int                             get_avro_block_size() { return _avro_block_size; }
		int								get_nb_blocks() { return _nb_block; }
		int								get_port() { return _port; }
		std::string						get_ip() { return _ip; }
		std::vector<std::string>		get_channel_names() { return _channel_names; }
		std::vector<std::uint16_t>		get_channel_offsets() { return _channel_offsets; }
		vector<pair<string, string>>	get_channels() { return _channels; }
	private:
	    bool                            _test_mode;
        int                             _avro_block_size;
		int								_nb_block;
		int								_port;
		std::string						_ip;
		std::vector<std::string>		_channel_names;
		std::vector<uint16_t>			_channel_offsets;
		vector <pair<string, string>>	_channels;
	};

	class Ipc {
	public:
		Ipc() { run(); };
		~Ipc() {};

		void	run();
		std::vector<std::string> get_ipc_names() { return _ipc_names; }
	private:
		std::vector<std::string>		_ipc_names;
	};
}
#endif //SKF_CLOUD_CONF_LOADER_H
