#include "../header/BatterySensor.hpp"


/*  Batterynsor */
float Battery_Sensor::Get_SensorData(void)
{
   return Battery_Voltage_LF_U32_; 
 
}

void Battery_Sensor::Set_SensorData(float Battery_InputData)
{
    Battery_Voltage_LF_U32_ =  (rand() % 11); // 11 gives numbers from 0 to 10;

}
