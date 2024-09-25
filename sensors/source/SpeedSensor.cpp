#include "../header/SpeedSensor.hpp"
#include "../header/SensorSimulators.hpp"


/*  Speed Sensor */
float Speed_Sensor::Get_SensorData(void)
{
   return Vehicle_Speed_LF_U32_; 
 
}


void Speed_Sensor::Set_SensorData(void)
{
    Vehicle_Speed_LF_U32_ = simulate_sensor.Simulate_Scenario_1(25); // 11 gives numbers from 0 to 10;

}