#include "../inc/tcp_ip.hpp"

int main(void)
{
    int port = 55555;
    const char* adr = "127.0.0.1";
    // const char* item = "12345";

    Tcp_ip tcp;
    // tcp.Client(port);
    std::string buf;
    // while (true)
    // {
    //     std::cout << "Please key..." << std::endl;
    //     std::cin >> buf;
    //     if(buf == "exit") break;
    //     std::cout << "key: ["<<buf<<"]" << std::endl;
    //     tcp.Client(port, adr, buf.c_str());
    // }

    tcp.Server(port);
    
    return 0;
}
