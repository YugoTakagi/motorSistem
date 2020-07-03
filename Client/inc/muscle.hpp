#ifndef MUSCLE
#define MUSCLE

#include "pid.hpp"
#include "virtualMotor.hpp"

class Muscle
{
private:
    PidControler _pid;
    VirtualMotor _motor;
    
    float _force;
public:
    Muscle(const float dt, const float p_gain, const float i_gain, const float d_gain);
    ~Muscle();

    float Stretch(float ref, float state);
};

#endif//MUSCLE