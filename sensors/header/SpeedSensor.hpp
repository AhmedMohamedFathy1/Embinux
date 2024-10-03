#ifndef SPEED_SESNSOR
#define SPEED_SESNSOR

#include "Sensor.hpp"
#include "SensorSimulators.hpp"

class Speed_Sensor : public Sensor<float>
 {
    private: 
        float Vehicle_Speed_LF_U32_;
        Simulate_Sensor simulate_sensor;

    public:
       
        float Get_SensorData(void) override; 

        void Set_SensorData(void) override;
        
        static Speed_Sensor& Get_SpeedSensor_Instance(void);
};


#endif