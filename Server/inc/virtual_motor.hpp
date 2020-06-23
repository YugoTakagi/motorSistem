#include "../inc/i2c.hpp"
#include <iostream>

#define VELOCITY_MAX 100.0
#define VELOCITY_MIN -100.0

class Virtual_motor
{
private:

public:
    Virtual_motor(/* args */);
    ~Virtual_motor();

    bool SetVelocity(float velocity);
    bool SetDuty(int duty);
};

Virtual_motor::Virtual_motor(/* args */)
{
}

Virtual_motor::~Virtual_motor()
{
}

bool Virtual_motor::SetVelocity(float velocity)
{
    if (velocity < VELOCITY_MIN || VELOCITY_MAX < velocity)
    {
        return false;
    }
    else{
        std::cout << "motor velocity: " << velocity << std::endl;
        return true;
    }
    
}
