#include "../header/SpeedSensor.hpp"


/*  Speed Sensor */
float Speed_Sensor::Get_SensorData(void)
{
   return Vehicle_Speed_LF_U32_; 
 
}

void Speed_Sensor::Set_SensorData(float Speed_InputData)
{
    Vehicle_Speed_LF_U32_ =  20 + (rand() % 11); // 11 gives numbers from 0 to 10;

}
