#include "server_socket.h"

namespace limos
{

ServerSocket::ServerSocket()
{
    sock = 0;
}

ServerSocket::~ServerSocket()
{
    if (sock != 0) 
        close(sock);
}

int ServerSocket::create()
{
    if ((sock = ::socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return -1;
    return 0;
}

int ServerSocket::bind(unsigned short port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        return -1;
    return 0;
}

int ServerSocket::listen()
{
    if (::listen(sock, 50) == -1)
        return -1;
    return 0;
}

int ServerSocket::accept(int &ses_sock)
{
    socklen_t addr_size = sizeof(struct sockaddr_in);
    struct sockaddr_in ses_addr;
    if ((ses_sock = ::accept(sock, (struct sockaddr *)&ses_addr, &addr_size)) == -1)
        return -1;
    return 0;
}

}