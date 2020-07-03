#include "../inc/muscle.hpp"

Muscle::Muscle(const float dt, const float p_gain, const float i_gain, const float d_gain)
:_pid(dt)
{
    _pid.SetGain(p_gain, i_gain, d_gain);
    _force = 0.0;
}

Muscle::~Muscle()
{
}

float Muscle::Stretch(float ref, float state)
{
    _force = _pid.run(ref, state);
    _motor.SetVelocity(_force);
    return _force;
}

