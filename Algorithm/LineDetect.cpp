#include "LineDetect.h"

#define LLL 0
#define LL  1
#define L   2
#define S   3
#define R   4
#define RR  5
#define RRR 6


Servo servo (p10);
LaneSensor laneSensor(p11,p12,p13,p14,p15,p16,p17);

char linestate, beforestate;
int laneData;
float degree;

void LineDetect::Lineinit(){
    servo.update(0.0);
}

void LineDetect::LineDetect_run(){
    laneData = laneSensor.getData();
    if( laneData == 0x7e )      linestate = LLL;
    else if( laneData == 0x7d ) linestate = LL;
    else if( laneData == 0x7b ) linestate = L;
    else if( laneData == 0x77 ) linestate = S;
    else if( laneData == 0x6f ) linestate = R;
    else if( laneData == 0x5f ) linestate = RR;
    else if( laneData == 0x3f ) linestate = RRR;
    else linestate = beforestate;
}

void LineDetect::LineTrace_run(){
    if( linestate == LLL )          degree = -16.5;
    else if( linestate == LL )      degree = -10.0;
    else if ( linestate == L )      degree = -4.0;
    else if ( linestate == S )      degree = 0.0;
    else if ( linestate == R )      degree = 6.0;
    else if ( linestate == RR )     degree = 12.0;
    else if ( linestate == RRR )    degree = 18.0;

    servo.update(degree);
    beforestate = linestate;
}
