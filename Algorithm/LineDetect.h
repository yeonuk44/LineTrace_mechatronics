#ifndef LINEDETECT_H
#define LINEDETECT_H

#include "mbed.h"
#include "Servo.h"
#include "LaneSensor.h"

class LineDetect{
    public:
        void LineDetect_run();
        void LineTrace_run();
        void Lineinit();
    protected:
        int laneData;
        float degree;
        char linestate, beforestate;
};

#endif