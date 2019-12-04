#include "LaneSensor.h"

LaneSensor::LaneSensor(PinName lll,PinName ll,PinName l,PinName m,PinName r,PinName rr,PinName rrr)
    : sensorsIn_(lll,ll,l,m,r,rr,rrr)
{
    error_=0.0;
    prevError_=0.0;
    //sensorsIn_.mode(PullNode);
}
float LaneSensor::getError()
{
    bool lll=false;
    bool ll=false;
    bool l=false;
    bool m=false;
    bool r=false;
    bool rr=false;
    bool rrr=false;

    float errorSum=0; //최종 각도
    int errorCount=0;
    float errorConstant =22.86; // 서보 회전 각도 반경

    int sensorIn=sensorsIn_ & sensorsIn_.mask();
    if((sensorIn&0x1)==0x0) {
        lll=true;
        errorSum+=errorConstant*1.8;//3.0; //68.58
        errorCount++;
    }

    if((sensorIn&0x1)==0x0 && (sensorIn&0x2)==0x0) {
        lll=true;
        ll = true;
        errorSum+=errorConstant*0.2;//3.0; //68.58
        errorCount++;
    }


    if((sensorIn&0x2)==0x0) {
        ll=true;
        errorSum+=errorConstant*0.05;//2.0; //45.72
        errorCount++;
    }

    if((sensorIn&0x2)==0x0 && (sensorIn&0x4)==0x0) {
        ll=true;
        l =true;
        errorSum+=errorConstant*0.0;//2.0; //45.72
        errorCount++;
    }
    if((sensorIn&0x4)==0x0) {
        l=true;
        errorSum+=errorConstant*0.0;//0.7; //16.002
        errorCount++;
    }
    if((sensorIn&0x8)==0x0) {
        m=true;
        errorSum+=0.0;
        errorCount++;
    }

    if((sensorIn&0x10)==0x0) {
        r=true;
        errorSum+=errorConstant*-0.0;//-0.7; //-16.002
        errorCount++;
    }

    if((sensorIn&0x10)==0x0 && (sensorIn&0x20)==0x0) {
        r=true;
        rr = true;
        errorSum+=errorConstant*-0.0;//-0.7; //-16.002
        errorCount++;
    }
    if((sensorIn&0x20)==0x0) {
        rr=true;
        errorSum+=errorConstant*-0.05;//-2.0; //-45.72
        errorCount++;
    }

    if((sensorIn&0x20)==0x0 && (sensorIn&0x40)==0x0) {
        rrr=true;
        rr = true;
        errorSum+=errorConstant*-0.2;//-3.0; //-68.58
        errorCount++;
    }

    if((sensorIn&0x40)==0x0) {
        rrr=true;
        errorSum+=errorConstant*-1.8;//-3.0; //-68.58
        errorCount++;
    }

    // 이전 각도 유지를 위한 count
    // count 가 들어오지 않으면 이전 값 유지
    if(errorCount==0) {
        error_=prevError_;
    } else {
        error_=errorSum/((float)errorCount);
    }
    prevError_=error_;

    return error_;
}

int LaneSensor::getData()
{
//실제 핀에 연결된 버스 핀의 이진 마스크   (NC 핀 아님) 버스 핀이 NC 상태에 있으면 해당 비트가 지워지고 (0으로 설정) 그렇지 않으면 비트가 1로 설정됩니다.
    return sensorsIn_ & sensorsIn_.mask();;
}
