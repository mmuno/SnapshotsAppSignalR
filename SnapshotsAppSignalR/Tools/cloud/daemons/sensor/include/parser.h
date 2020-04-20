#ifndef SKF_CLOUD_PARSER_RUN_H
#define SKF_CLOUD_PARSER_RUN_H

#include "logs.h"
#include "udp_client_server.h"
#include "response_snapshotv2.h"
#include "query_snapshotv2.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

#define DATA_SIZE 4096
/** @addtogroup Parser
 * 	@brief Module receiving and placing at disposal the data from MBCSI
 *
 * 	@author Fabien Labarbe-Desvignes
 * 	@date May 2019
 *
 *
 *  @{
 */

/**
 * @brief Parser main class.
 */
class Parser {
public:
	/** @brief Class constructor, need ip and port in order to start udp client. */
	Parser(char **argv) :_client(argv[1], std::atoi(argv[2])) {};
	/** @brief Class constructor, need ip and port in order to start udp client. */
    Parser(const char *ip, const char *port) : _client(ip, std::atoi(port)) {};
	Parser(const char *ip, int port) : _client(ip, port) {};
	~Parser() {};

    int         run();
	void        init();
	void        finish();

private:
    void        assign_shared_memories();

private:
    UdpClientServer::UdpClient   	_client; /** handles the udp connection with the server */
	GciQuerySnapshotV2              _gci_query; /** responsible to generate the queries we need to send to the server */
	GciResponseSnapshotV2           _gci_response; /** handles the server responses */
    char                            _data_buf[DATA_SIZE] = {0}; /** buffer containing the data we receive from the server */
};
/** @}*/


#endif //SKF_CLOUD_PARSER_RUN_H
