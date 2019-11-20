#pragma once
#include <thread>
#include "session.h"
#include "server_socket.h"
#include "log.h"

namespace limos
{

class HlsServer
{
    ServerSocket serv_sock;


public:
    HlsServer();

    int start(unsigned short port);


};

}
