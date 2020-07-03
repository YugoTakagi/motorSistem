#include "../inc/pid.hpp"

PidControler::PidControler(float dt)
: _dt(dt)
{
    _adjustment = 0.0;
    _integral = 0.0;
    _diff[0] = 0.0;
    _diff[1] = 0.0;

    _gainCeck = false;
}

PidControler::~PidControler()
{
}

void PidControler::SetGain(float p_gain, float i_gain, float d_gain)
{
    _p_gain = p_gain;
    _i_gain = i_gain;
    _d_gain = d_gain;

    _gainCeck = true;
}

float PidControler::run(float ref, float state){
    if(_gainCeck){
        _diff[0] = _diff[1];
        _diff[1] = ref - state;
        _integral += ((_diff[1] + _diff[0]) / 2)*_dt;
        _adjustment = _p_gain*_diff[1] + _i_gain*_integral + _d_gain*(_diff[1] - _diff[0]) / _dt;

        return _adjustment;
    }
    else{
        std::cout << "Please gain set." << std::endl;
    }
}