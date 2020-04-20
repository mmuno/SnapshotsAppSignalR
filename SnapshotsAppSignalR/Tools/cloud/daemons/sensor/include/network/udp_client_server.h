#ifndef SNAP_UDP_CLIENT_SERVER_H
#define SNAP_UDP_CLIENT_SERVER_H

#include "response_snapshotv2.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <iostream>


/**
 * @namespace udp_client_server
 *
 *
 */
namespace UdpClientServer
{

    class UdpClientServerRuntimeError : public std::runtime_error
    {
    public:
        UdpClientServerRuntimeError(const char *w) : std::runtime_error(w) {}
    };

    class UdpClient
    {
    public:
        UdpClient(const std::string& addr, int port);
        ~UdpClient();

        int                 get_socket() const;
        int                 get_port() const;
        std::string         get_addr() const;
        void                init();
        int                 receive(char *);
        int                 send(const char *msg, size_t size);

    private:
        int                 f_socket;
        int                 f_port;
        std::string         f_addr;
        struct addrinfo *   f_addrinfo;
    };


    class UdpServer
    {
    public:
    	UdpServer(const std::string& addr, int port);
        ~UdpServer();

        int                 get_socket() const;
        int                 get_port() const;
        std::string         get_addr() const;

        int                 recv(char *msg, size_t max_size);
        int                 timed_recv(char *msg, size_t max_size, int max_wait_ms);

    private:
        int                 f_socket;
        int                 f_port;
        std::string         f_addr;
        struct addrinfo *   f_addrinfo;
    };

} // namespace UdpClient_server
#endif
// SNAP_UDP_CLIENT_SERVER_H