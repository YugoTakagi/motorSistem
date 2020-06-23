#include "../inc/tcp_ip.hpp"

int main(void)
{
    int port = 55555;
    const char* adr = "127.0.0.1";
    const char* item = "12345";

    Tcp_ip tcp;
    // tcp.client(port);
    tcp.server(port, adr, item);
    return 0;
}
