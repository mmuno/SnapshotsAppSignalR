#include <signal.h>

#include "parser.h"
#include "errors.h"
#include "conf_loader.h"

using namespace std;

static volatile int g_keep_running = 1;
/** @brief Catches catch ctrl-c set keep runing to false
 */
static void	int_handler(int dummy)
{
	(void) dummy;
	g_keep_running = 0;
}

/**
 *	@brief using our version of strncpy because std::strncpy stops at 0x00 bytes or we must copy them
 */
static char     *my_strncpy(char *dest, const char *src, std::size_t count)
{
	for (std::size_t x = 0 ; x < count ; x++) {
		dest[x] = src[x];
	}
	return dest;
}

/** @brief Starts the connection with MBCSI.
 *
 * This function sends a UDP request that asks the server to stream snapshotV2.
 *
 */
void     Parser::init()
{
	_gci_query.enable_snapshot_query();
	std::string serialized = _gci_query.serialize_data();
	char        c_serialized[serialized.size()];
	my_strncpy(c_serialized, serialized.c_str(), serialized.size());


	_client.send(c_serialized, serialized.size());
	_client.receive(_data_buf);
}

/** @brief End the connection with MBCSI
 *
 * This function sends a UDP request that informs the server that we will stop the connection.
 *
 */
void     Parser::finish()
{
	_gci_query.disable_snapshot_query();
	std::string serialized = _gci_query.serialize_data();
	char        c_serialized[serialized.size()];

	my_strncpy(c_serialized, serialized.c_str(), serialized.size());
	_client.send(c_serialized, serialized.size());
}

/** @brief Loop until we asks the program to quit (on key press)
 * @return Return 1 if an exception's caught else it returns 0.
 *
 * This function initialize the connection with MBSCI and then loop until we asks it to stop.
 * Within the loop we're using the class GciQuerySnapshotV2 to serialize the data we send to the server and
 * GciResponseSnapshotV2 to handle the data received and
 *
 */
int            Parser::run()
{
	init();
	std::cout << "Parser: press any key to exit" << std::endl;
	_gci_response.get_timer().start("init");
	while (g_keep_running) {
		int data_size = _client.receive(_data_buf);
		_gci_response.run(_data_buf, data_size);
		if (_gci_response.get_timer().get_blocks_received() > 500) {
			init();
			_gci_response.get_timer().reset_blocks_received();
		}
	}
	finish();
	return 0;
}

int			main()
{
	ConfLoader::Parser	loader;

	Parser parser(loader.get_ip().c_str(), loader.get_port());
	signal(SIGINT, int_handler);

	for (int retry = 0 ; retry < 10 ; retry++) {
		try {
			parser.run();
		}
		catch (std::exception &e) {
			std::cerr << "Exception: " << e.what() << "@n" << endl;
			std::cerr << 10 - retry << " retry left..." << endl;
			parser.finish();
			sleep(1);
			continue;
		}
		return 0;
	}
	return 1;
}