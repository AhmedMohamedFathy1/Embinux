#include "../header/SpeedSensor.hpp"
#include "../header/SensorSimulators.hpp"

#include "UpdateSesnors.hpp"
#include <iostream>
#include "SpeedSensor.hpp"

Sensors_data_t& sensors_data = Update_Sensors::GetSensorData();

/*  Speed Sensor */
float Speed_Sensor::Get_SensorData(void)
{
    std::cout << "get :" << Speed_Sensor::Vehicle_Speed_LF_U32_ << std::endl;

   return Speed_Sensor::Vehicle_Speed_LF_U32_; 
 
}


void Speed_Sensor::Set_SensorData(float value)
{
    Vehicle_Speed_LF_U32_ = simulate_sensor.Simulate_SpeedSensor(120,5); 
    // std::cout << "Trial " << value << std::endl;
    // Speed_Sensor::Vehicle_Speed_LF_U32_ = value;   
    // std::cout << "Trial 2 " << Vehicle_Speed_LF_U32_ << std::endl;
}


Speed_Sensor& Speed_Sensor::Get_SpeedSensor_Instance(void)
{
    static Speed_Sensor speedSensor_Instance;
    return speedSensor_Instance;
}