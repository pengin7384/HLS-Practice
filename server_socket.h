#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace limos
{

class ServerSocket
{
    int sock;    
    
public:
    ServerSocket();
    ~ServerSocket();

    int create();
    int bind(unsigned short port);
    int listen();
    int accept(int &ses_sock);

};

}