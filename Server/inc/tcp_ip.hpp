#ifndef TCP_IP
#define TCP_IP

#include <iostream>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUFFER_SIZE 5

class Tcp_ip
{
private:
    unsigned short _port;
    char* _ip_addres;
    struct sockaddr_in _addr;

    void Making_sockaddr_in();
    bool Connecting(int soc);
public:
    Tcp_ip(int port_num, char* ip_addres);
    ~Tcp_ip();

    bool Client(int port_num);
    bool Server(const char* send_text);
};
#endif//TCP_IP