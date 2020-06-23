#include "../inc/i2c.hpp"
#include <iostream>

class Virtual_motor
{
private:
    float velocity_max = 100.0;
    float velocity_min = -100.0;
    /* data */
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
    if (velocity < velocity_min || velocity_max < velocity)
    {
        return false;
    }
    else{
        std::cout << "motor velocity: " << velocity << std::endl;
        return true;
    }
    
}
