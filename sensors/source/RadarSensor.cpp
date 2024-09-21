#include "../header/RadarSensor.hpp"

/*  Radar Sensor */

float Radar_Sensor::Get_SensorData(void)
{
   return Radar_Distance_LF_U32_; 
 
}

void Radar_Sensor::Set_SensorData(float Radar_InputData)
{
    Radar_Distance_LF_U32_ = 50 + (rand() % 22);;

}
