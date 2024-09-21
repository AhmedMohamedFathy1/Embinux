#ifndef SPEED_SESNSOR
#define SPEED_SESNSOR

#include "../header/Sensor.hpp"

class Speed_Sensor : public Sensor<float>
{
    private: 
        float Vehicle_Speed_LF_U32_;

    public:
       
        float Get_SensorData(void) override; 

        void Set_SensorData(float Speed_InputData) override;

};


#endif