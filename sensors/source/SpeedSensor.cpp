#include "../header/SpeedSensor.hpp"
#include "../header/SensorSimulators.hpp"

#include "UpdateSesnors.hpp"

Sensors_data_t& sensors_data = Update_Sensors::GetSensorData();

/*  Speed Sensor */
float Speed_Sensor::Get_SensorData(void)
{
   return Vehicle_Speed_LF_U32_; 
 
}


void Speed_Sensor::Set_SensorData(float value)
{
    Vehicle_Speed_LF_U32_ = simulate_sensor.Simulate_Scenario_1(sensors_data.SpeedSensor_data); // 11 gives numbers from 0 to 10;

}