#include "../inc/Tcp_Ip.hpp"

#define START "12345"
#define END "54321"

int main(void)
{
    int port = 55555;
    // const char* adr = "127.0.0.1";
    
    MemoServer tis(port);
    
    bool recvFlag = false;
    while (true)
    {
        tis.Read();
        char* i = tis.OfRecvBuffer();
        if(!strcmp(i, START))
        {
            recvFlag = true;
            std::cout << "[TCP/IP] Start" << std::endl;
        } 
        
        if(recvFlag)
        {
            std::cout << "main: " << i << std::endl;
            if(!strcmp(i, END)) break;
        }
    }
    // tis.Read();
    // char* i = tis.OfRecvBuffer();
    std::cout << "main end." << std::endl;

    return 0;
}
