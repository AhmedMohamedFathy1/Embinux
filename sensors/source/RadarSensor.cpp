#include "../header/RadarSensor.hpp"
#include "../header/SensorSimulators.hpp"
#include "RadarSensor.hpp"

/*  Radar Sensor */
float Radar_Sensor::Get_SensorData(void)
{
   return Radar_Distance_LF_U32_; 
 
}

void Radar_Sensor::Set_SensorData(void)
{
    Radar_Distance_LF_U32_ = simulate_sensor->Simulate_RadarSensor();
}

Radar_Sensor &Radar_Sensor::Get_RadarSensor_Instance(void)
{
    static Radar_Sensor radar_Sensor_Instance;
    return radar_Sensor_Instance;
}
