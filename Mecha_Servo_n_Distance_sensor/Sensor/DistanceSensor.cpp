#include "DistanceSensor.h"

#define MAX_DISTANCE (-1.0)

DistanceSensor::DistanceSensor(PinName a): m_analogIn(a)
{
    m_distance = MAX_DISTANCE;
}
float DistanceSensor::getDistance_cm()
{
     double m_DIS, m_vol; 
     
     m_vol = m_analogIn*3.3;
    
    if(m_vol < 0.4)
        m_DIS = 80;
    else
        m_DIS = 28.162 * powf(m_vol, (-1.122));
        
    return m_DIS;
    
    //return m_analogIn*3.3;
}