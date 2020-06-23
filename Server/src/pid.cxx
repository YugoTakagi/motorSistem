#include "../inc/pid.hpp"

PidControler::PidControler(float p_gain, float i_gain, float d_gain, float dt)
: _p_gain(p_gain), _i_gain(i_gain), _d_gain(d_gain), _dt(dt)
{
    _adjustment = 0.0;
    _integral = 0.0;
    _diff[2] = {0.0};
}

PidControler::~PidControler()
{
}

float PidControler::run(float ref, float state){
    _diff[0] = _diff[1];
    _diff[1] = ref - state;
    _integral += ((_diff[1] + _diff[0]) / 2)*_dt;
    _adjustment = _p_gain*_diff[1] + _i_gain*_integral + _d_gain*(_diff[1] - _diff[0]) / _dt;

    return _adjustment;
}