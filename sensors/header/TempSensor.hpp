#ifndef TEMPERTURE_SENSOR
#define TEMPERTURE_SENSOR

#include "../header/Sensor.hpp"
#include "../header/SensorSimulators.hpp"

class Temperature_Sensor : public Sensor<float>, public Simulate_Sensor
{
    private: 
        float Temperature_LF_U32_;
        Simulate_Sensor *simulate_sensor;  // compistion


    public:
       
        float Get_SensorData(void) override; 

        void Set_SensorData(float value) override;

        static Temperature_Sensor Get_TemperatureSensor_Instance(void); 
};


#endif