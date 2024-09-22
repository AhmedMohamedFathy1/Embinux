#ifndef TEMPERTURE_SENSOR
#define TEMPERTURE_SENSOR

#include "../header/Sensor.hpp"

class Temperature_Sensor : public Sensor<float>
{
    private: 
        float Temperature_LF_U32_;

    public:
       
        float Get_SensorData(void) override; 

        void Set_SensorData(void) override;

};


#endif