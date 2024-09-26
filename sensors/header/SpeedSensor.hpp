#ifndef SPEED_SESNSOR
#define SPEED_SESNSOR

#include "../header/Sensor.hpp"
#include "../header/SensorSimulators.hpp"

class Speed_Sensor : public Sensor<float>
 {
    private: 
        float Vehicle_Speed_LF_U32_;
        Simulate_Sensor simulate_sensor;

    public:
       
        float Get_SensorData(void) override; 

        void Set_SensorData(float value) override;

};


#endif