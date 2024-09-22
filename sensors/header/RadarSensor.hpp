#ifndef RADAR_SESNSOR
#define RADAR_SESNSOR

#include "../header/Sensor.hpp"

class Radar_Sensor : public Sensor<float>
{
    private: 
        float Radar_Distance_LF_U32_;

    public:
       
        float Get_SensorData(void) override; 

        void Set_SensorData(void) override;

};

#endif