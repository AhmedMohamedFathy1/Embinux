#ifndef __FUELSENSOR__H__
#define __FUELSENSOR__H__

#include "../header/Sensor.hpp"
#include "../header/SensorSimulators.hpp"

class Fuel_Sensor : public Sensor<int>
{
    private: 
        int Fuel_Capacity_LI_U32_;
        Simulate_Sensor *simulate_sensor;  // compistion

    public:
       
        int Get_SensorData(void) override; 

        void Set_SensorData(void) override;

};

#endif  //!__FUELSENSOR__H__