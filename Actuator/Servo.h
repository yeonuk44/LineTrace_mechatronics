#ifndef MBED_SERVO_H
#define MBED_SERVO_H

#include "mbed.h"
// 정방향 기준 왼쪽 회전 최대 각 : 0.001415
// 정방향 기준 오른쪽 회전 최대각 : 0.00172
#define MAX 20.0
#define MID 0.00159

class Servo
{
private:
    DigitalOut m_PWM;
    Ticker m_period_ticker;
    Timeout m_width_timeout;
    float m_degree;
    float m_width;
    
    void setPeriod();
    void setWidth();
public:
    Servo(PinName IN);
    void update(float degree);
    float getDegree();
};

#endif
