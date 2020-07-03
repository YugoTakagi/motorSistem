#include <iostream>

class PidControler
{
private:
    float _p_gain;
    float _i_gain;
    float _d_gain;

    float _dt;
    float _adjustment;
    float _diff[2];
    float _integral;

    bool _gainCeck;
public:
    PidControler(float dt);
    ~PidControler();

    void SetGain(float p_gain, float i_gain, float d_gain);
    float run(float ref, float state);
};
