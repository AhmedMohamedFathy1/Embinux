#ifndef BATTERY_SESNSOR
#define BATTERY_SESNSOR

#include "../header/Sensor.hpp"
#include "../header/SensorSimulators.hpp"

class Battery_Sensor : public Sensor<float>
{
    private: 
        float Battery_Voltage_LF_U32_;
        Simulate_Sensor *simulate_sensor;  // compistion

    public:
       
        float Get_SensorData(void) override; 

        void Set_SensorData(float value) override;

        static Battery_Sensor Get_BatterySensor_Instance(void);


};


#endif