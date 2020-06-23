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
public:
    PidControler(float p_gain, float i_gain, float d_gain, float dt);
    ~PidControler();

    float run(float ref, float state);
};
