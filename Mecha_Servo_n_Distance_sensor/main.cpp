#include "mbed.h"
#include "DistanceSensor.h"
#include "Plotting.h"
#include "Motor.h"
#include "Servo.h"
#include "LaneSensor.h"

DistanceSensor pir (p20);
Servo servo (p10);
Motor motor(p23,p24,p25,p26);
Plotting plot;

//Interrupt is generated every 1ms and degree is increased by 1
unsigned int uiFlag_50ms = 0;

//To plot with usb, set as below.
Serial pc(USBTX,USBRX); // Tx, Rx Pin

//Set each gpio to see the output of the hall sensor as a led
LaneSensor laneSensor(p11,p12,p13,p14,p15,p16,p17);

    
void counter_1ms ()
{
    uiFlag_50ms++;
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
    
    //Servo reset
    float degree = 0.0;
    //pc.printf("Waiting Request\n");        
    
    //servo.update (17.2); //1m 반경 
    while(1) {
        // Every 50 ms,
        if(uiFlag_50ms>=50) {
            uiFlag_50ms=0;
            
           // // clear plotting buffer
//            plot.reset();
//            
//            // put data to buffer
//            plot.put(pir.getDistance_cm(),0);
//            
//            // send buffer
//            plot.send(&pc);
//            pc.printf ("Distance %f\r\n", pir.getDistance_cm());
        }  
        
        //AEB
        if(pir.getDistance_cm() <= 40)
            motor.setSpeed_percent(0, BACKWARD);
        else 
            motor.setSpeed_percent(20.0,FORWARD);
            
       servo.update(laneSensor.getError()/1.3);
    }
}

 //Servo control   
      //  char c = pc.getc();
//        
//        if (c == 'u') degree += 0.1;
//        else if (c == 'd') degree -= 0.1;
//            
//        servo.update (degree);
//        degree = servo.getDegree();
//            
//        pc.printf("Degree: %f\n", servo.getDegree());