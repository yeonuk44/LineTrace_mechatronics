#include "mbed.h"
#include "HallSensor.h"
#include "DistanceSensor.h"
#include "Plotting.h"
#include "Motor.h"
#include "Servo.h"
#include "LineDetect.h"

LineDetect linedetect;
DistanceSensor pir(p20);
//Servo servo (p10);
HallSensor hall (p28);
Motor motor (p23, p24, p25, p26);
//LaneSensor laneSensor(p11,p12,p13,p14,p15,p16,p17);
Serial pc (USBTX, USBRX); // tx, rx
Plotting plot;

//Interrupt is generated every 1ms and degree is increased by 1
unsigned int uiFlag_1ms = 0;
unsigned int uiFlag_10ms = 0;
    
void counter_1ms ()
{
    uiFlag_1ms++;
    uiFlag_10ms++;
}


// Plot distance sensor
int main()
{
    wait(1);

    //Set the 1ms thicker.
    Ticker ticker_1ms;
    ticker_1ms.attach(&counter_1ms,0.001);

    Timer time;
    time.start();
    
//    float degree = 14.1;
//    servo.update (0.0);
    linedetect.Lineinit();
    
    float dis = 0.0;
    float goal_speed = 10.0;
    
    while(1) {
        // Every 1 ms,
        if(uiFlag_1ms >= 1) {
            uiFlag_1ms = 0;
            
            //Set the motor to 10%.
            motor.setSpeed_percent(goal_speed, BACKWARD);
            
//            servo.update(degree);
            
            dis = pir.getDistance_cm();
            if(dis>6 && dis<30) goal_speed = 0.0;
        }
                
        // Every 10 ms,
        if(uiFlag_10ms>=10) {
            linedetect.LineDetect_run();
            linedetect.LineTrace_run();
        }
    }
}
