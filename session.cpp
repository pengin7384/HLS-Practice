#include "session.h"

namespace limos
{

Session::Session(int sock) : sock(sock)
{

}

Session::~Session()
{
    close(sock);
}

int Session::start()
{
    if (recv() == -1) 
        return log(ERR, "Start -> recv");

    std::string uri;

    if (getUri(uri) == -1) 
        return log(ERR, "Start -> getUri");

    buf = "HTTP/1.1 200 OK\r\nConnection: Close\r\nContent-Type: text/html\r\n\r\n";

    if (send() == -1) 
        return log(ERR, "send");

    if (sendFile(uri.substr(1, uri.length() - 1)) == -1) 
        return log(ERR, "sendFile");
    
    return 0;  
}

int Session::recv()
{
    char temp[RECV_BUF_SIZE];

    int recv_size = ::recv(sock, temp, BUF_SIZE, 0);
    
    if (recv_size == -1) 
        return log(ERR, "Send");
    
    buf = temp;

    return 0;
}

int Session::send()
{
    const char *temp_buf = buf.c_str();
    int buf_len = buf.length();
    int send_len = 0;

    while (send_len < buf_len) {
        int len = ::send(sock, temp_buf + send_len, buf_len - send_len, 0);
        
        if (len == -1) 
            return log(ERR, "Send");
    
        send_len += len;
    }

    return 0;
}

int Session::sendFile(std::string file_path)
{
    std::FILE *file = std::fopen(file_path.c_str(), "r");

    printf("Request (%s)\n", file_path.c_str());

    if (file == nullptr) 
        return log(ERR, "Can't open file");
    
    size_t read_len;
    char *temp_buf[BUF_SIZE];

    while ((read_len = std::fread(temp_buf, sizeof(char), BUF_SIZE, file)) > 0) {
        ::send(sock, temp_buf, read_len, 0);
    }
    
    if (read_len == -1) 
        return log(ERR, "fread");

    printf("Sent (%s)\n", file_path.c_str());

    return 0;    
}

int Session::getUri(std::string &uri)
{
    /* Check Method */
    if (buf.length() < 10 || std::strncmp("GET", buf.c_str(), 3) != 0) 
        return log(ERR, "strcmp");

    size_t n = buf.find(" ", 4);

    uri = "";

    for (size_t i = 4; i < n; i++) {
        uri += buf.at(i);
    }

    return 0;  
}



}