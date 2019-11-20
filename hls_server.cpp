#include "hls_server.h"

namespace limos
{

HlsServer::HlsServer() 
{

}

int HlsServer::start(unsigned short port) 
{
    printf("Server Start!\n");

    if (serv_sock.create() < 0) 
        return log(ERR, "Create Socket");

    if (serv_sock.bind(htons(port)) < 0)
        return log(ERR, "Bind Socket");

    printf("port:%u\n", port);

    if (serv_sock.listen() < 0)
        return log(ERR, "Listen Socket");

    printf("Server: listen\n");


    while (true) {
        int ses_sock;

        if (serv_sock.accept(ses_sock) < 0) 
            return log(ERR, "Accept Socket");

        std::thread thr([](int arg_sock) {
            Session ses(arg_sock);
            ses.start();
        }, ses_sock);

        thr.detach();        
    }

}

}