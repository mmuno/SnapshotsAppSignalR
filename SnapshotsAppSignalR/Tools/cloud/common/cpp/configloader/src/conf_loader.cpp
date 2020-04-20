#include "conf_loader.h"
#include "logs.h"

void ConfLoader::Parser::run()
{
	YAML::Node	config = YAML::LoadFile(PARSER_PATH);
	uint16_t	channel_offset = 0;

    _test_mode = config["test_mode"].as<bool>();
    _avro_block_size = config["avro_block_size"].as<int>();
    _port = config["port"].as<int>();
    _nb_block = config["block_size"].as<int>();
	_ip = config["ip"].as<string>();
	_port = config["port"].as<int>();
	_channel_names.emplace_back("14000");
	_channel_names.emplace_back("2000");
	_channel_names.emplace_back("1000");
	for (auto name : _channel_names) {
		_channel_offsets.emplace_back(channel_offset);
		for (auto y : config[name]) {
			Logs::parser_log(string(y[0].as<string>() + " " + y[1].as<string>() + "\n").c_str(), 2);
			_channels.emplace_back(y[0].as<string>(), y[1].as<string>());
			channel_offset += 1;
		}
	}
	_channel_offsets.emplace_back(channel_offset);
}

void ConfLoader::Ipc::run() {
	YAML::Node config = YAML::LoadFile(IPC_PATH);

	for (YAML::const_iterator it = config.begin(); it != config.end(); ++it) {
		YAML::Node name = it->first;
		YAML::Node value = it->second;

		switch (value.Type()) {
			case YAML::NodeType::Map:
				for (auto itr = value.begin(); itr != value.end(); ++itr) {
					auto name = itr->first;
					auto value = itr->second;
					_ipc_names.emplace_back(value.as<string>());
				}
				break;
			default:
				throw ERROR_LOAD_CFG;
		};
	}
}