#include "../header/RadarSensor.hpp"
#include "../header/SensorSimulators.hpp"

/*  Radar Sensor */
float Radar_Sensor::Get_SensorData(void)
{
   return Radar_Distance_LF_U32_; 
 
}

void Radar_Sensor::Set_SensorData(void)
{
    Radar_Distance_LF_U32_ = simulate_sensor->Simulate_RadarSensor();
}
