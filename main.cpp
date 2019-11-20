#include <iostream>
#include <string>
#include <climits>
#include "hls_server.h"

int main(int argc, char *argv[])
{
    if (argc < 2 || atoi(argv[1]) > USHRT_MAX) {
        std::cout << "Usage: ./server <port>" << "\n";
        return 1;
    }

    limos::HlsServer server;
    unsigned short port = atoi(argv[1]);
    
    if (server.start(port) < 0) 
        return 1;

    return 0;
}