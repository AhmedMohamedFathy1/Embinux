#include "../header/BatterySensor.hpp"


/*  Batterynsor */
float Battery_Sensor::Get_SensorData(void)
{
   return Battery_Voltage_LF_U32_; 
 
}

void Battery_Sensor::Set_SensorData(void)
{
    Battery_Voltage_LF_U32_ =  simulate_sensor->Simulate_BatterySensor();; // 11 gives numbers from 0 to 10;

}
