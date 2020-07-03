#include <iostream>
#include <sstream>
#include <fstream>
#include "../inc/tcpClient.hpp"
#include "../inc/pid.hpp"
#include "../inc/virtual_motor.hpp"

#define START "start"
#define END   "end.."
#define READY "ready"

#define IFILE1 "../_input/vas_int_r.csv"
#define IFILE2 "../_input/vas_int_r.csv"
#define IFILE3 "../_input/vas_int_r.csv"

#define OFILE1 "../_output/log.csv"

#define DT    0.02//[s]
#define PGAIN 2
#define IGAIN 0.01
#define DGAIN 1

float StateForce();
int main(int argc, char const *argv[])
{
/* ============================================================== */
// Init
    // array for pid & log.
    const float ref1[]= 
    {
        #include IFILE1
    };
    int size = sizeof(ref1)/ sizeof(float);
    float state1[size];
    float adj1[size];

    // pid controler
    PidControler pidc(DT);
    pidc.SetGain(PGAIN, IGAIN, DGAIN);

    // motor
    VirtualMotor motor1, motor2, motor3;
// ~Inti 
/* ============================================================== */
// Get permission from Server
    // Init
    unsigned short port = atoi(argv[1]);
        // unsigned short port = 8100;
    const char* addr = "127.0.0.1";
    MemoClient client(port, addr);
    bool startFlag = false;

    // Ready
    std::cout << "[Client] I'm ready!" << std::endl;
    client.Send(READY);

    while(true)
    {
        char* recv = client.Read();
        std::cout << "[Client] Recv ["<< recv <<"] from Server."<< std::endl;
        if(!strcmp(recv, START))
        {
            startFlag = true;
            std::cout << "[Server] Let's Start!" << std::endl;
            break;
        }
    }
// ~Get permission from Server
/* ============================================================== */
// Start muscle control
    int index = 0;
    while(startFlag)
    {// mina loop
        if(index == size) break;

        std::cout <<"["<< index <<"] ";
        state1[index] = StateForce();
        adj1[index] = pidc.run(ref1[index], state1[index]);
        motor1.SetVelocity(adj1[index]);


        ++index;
    }
    client.Send(END);

    while(true)
    {
        char* recvEnd = client.Read();
        std::cout << "[Client] Recv ["<< recvEnd <<"] from Server."<< std::endl;
        if(!strcmp(recvEnd, END))
        {
            std::cout << "[Server] That's it." << std::endl;
            break;
        }
    }

// ~Start muscle control
/* ============================================================== */
// Make log
    std::ofstream fout1(OFILE1);
    fout1 << "ref,adj,state" << std::endl;
    for(int i=0; i < size; ++i)
    {// log loop
        fout1 << ref1[i] <<","<< adj1[i] <<","<< state1[i] << std::endl;
    }
    fout1.close();
    std::cout << "[Client] That's it." << std::endl;
    return 0;
}

float StateForce()
{
    float stForce = 0.0;
    // run code


    // ~run code
    return stForce;
}