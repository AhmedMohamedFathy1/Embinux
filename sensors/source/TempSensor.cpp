#include "../header/TempSensor.hpp"

/*  Temperature Sensor */
float Temperature_Sensor::Get_SensorData(void)
{
   return Temperature_LF_U32_; 
 
}

void Temperature_Sensor::Set_SensorData(float Temperature_InputData)
{
    Temperature_LF_U32_ =  20 + (rand() % 11); // 11 gives numbers from 0 to 10;

}
