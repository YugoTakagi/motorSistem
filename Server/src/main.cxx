#include "../inc/Tcp_Ip.hpp"

#define START "12345"
#define END "54321"
#define IFILE "../_input/ref.csv"

int main(void)
{
    int port = 55555;
    // const char* adr = "127.0.0.1";
    
    const float ref[]= 
    {
        #include IFILE
    };

    MemoServer tis(port);
    
    int ind=0;
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
            std::cout << ref[ind] << std::endl;
            if(!strcmp(i, END)) break;
            ++ind;
        }
    }
    std::cout << "main end." << std::endl;

    return 0;
}
