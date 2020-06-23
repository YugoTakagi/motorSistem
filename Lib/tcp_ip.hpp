#ifndef TCP_IP
#define TCP_IP

#include <iostream>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUFFER_SIZE 5
struct Client_data
{
    unsigned short port;
    const char* ip_addres;
    int soc;
    struct sockaddr_in addr;
};

struct Server_data
{
    unsigned short port;
    int my_socket; // 自分 
    int op_socket; // 相手 (opponent)
    struct sockaddr_in my_addr; // 自分
    struct sockaddr_in op_addr; // 相手 (opponent)
};

class Tcp_ip
{
private:
    Client_data _cdata;
    Server_data _sdata;
    // int Making_sockaddr_in();
    int Making_sockaddr_in(struct sockaddr_in &addr, unsigned short port, const char* ip_addres);
    bool Connecting(int soc);
public:
    Tcp_ip();
    ~Tcp_ip();

    bool Client(int port_num, const char* ip_addres, const char* send_text);
    bool Server(int port_num);
};
#endif//TCP_IP