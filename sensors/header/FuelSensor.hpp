#ifndef __FUELSENSOR__H__
#define __FUELSENSOR__H__

#include "../header/Sensor.hpp"
#include "../header/SensorSimulators.hpp"

class Fuel_Sensor : public Sensor<float>
{
    private: 
        float Fuel_Capacity_LI_U32_;
        Simulate_Sensor *simulate_sensor;  // compistion

    public:
       
        float Get_SensorData(void) override; 

        void Set_SensorData(float value) override;

};

#endif  //!__FUELSENSOR__H__