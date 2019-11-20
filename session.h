#pragma once
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <cstdio>
#include "log.h"
#define RECV_BUF_SIZE 1600
#define BUF_SIZE 1024

namespace limos
{

class Session
{
    int sock;
    std::string buf;

public:
    Session(int sock);

    ~Session();

    int start();

    int recv();

    int send();

    int sendFile(std::string file_path);

    int getUri(std::string &uri);

};


}