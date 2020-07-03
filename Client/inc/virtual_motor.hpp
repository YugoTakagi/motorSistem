#include "../inc/i2c.hpp"
#include <iostream>

#define VELOCITY_MAX 100.0
#define VELOCITY_MIN -100.0

class VirtualMotor
{
private:

public:
    VirtualMotor(/* args */);
    ~VirtualMotor();

    bool SetVelocity(float velocity);
    bool SetDuty(int duty);
};

VirtualMotor::VirtualMotor(/* args */)
{
}

VirtualMotor::~VirtualMotor()
{
}

bool VirtualMotor::SetVelocity(float velocity)
{
    if (velocity < VELOCITY_MIN || VELOCITY_MAX < velocity)
    {
        if(velocity < VELOCITY_MIN)
        {
            std::cout << "motor velocity: " << VELOCITY_MIN << std::endl;
        }
        if(VELOCITY_MAX < velocity)
        {
            std::cout << "motor velocity: " << VELOCITY_MAX << std::endl;
        }
        return false;
    }
    else{
        std::cout << "motor velocity: " << velocity << std::endl;
        return true;
    }
    
}
