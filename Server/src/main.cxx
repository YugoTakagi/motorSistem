// #include "../inc/tcp_ip.hpp"
#include "../inc/tcp_ip2.hpp"

int main(void)
{
    int port = 55555;
    // const char* adr = "127.0.0.1";
    
    TcpIpServer tis(port);
    
    while (true)
    {
        tis.Listen();
    }
    return 0;
}
