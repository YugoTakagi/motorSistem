#include "../inc/Tcp_Ip.hpp"

#define START "123"
#define END "321"

int main(void)
{
    unsigned short port = 55555;
    const char* addr = "127.0.0.1";
    char item[] = START;

    // std::string buf;
    MemoClient tic(port, addr);
    while (true)
    {
        // std::cout << "Please key..." << std::endl;
        // std::cin >> buf;
        // if(buf == "exit") break;
        // std::cout << "key: ["<<buf<<"]" << std::endl;
        tic.Send(item);
    }
    
    return 0;
}
