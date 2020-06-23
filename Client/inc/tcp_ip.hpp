#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUFFER_SIZE 5

class Tcp_ip
{
private:
    /* data */
public:
    Tcp_ip(/* args */);
    ~Tcp_ip();

    bool client(int port_num);
    bool server(int port_num, const char* ip_addres, const char* send_text);
};
