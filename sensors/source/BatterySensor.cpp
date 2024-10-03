#include "../header/BatterySensor.hpp"
#include "BatterySensor.hpp"


/*  Batterynsor */
float Battery_Sensor::Get_SensorData(void)
{
   return Battery_Voltage_LF_U32_; 
 
}

void Battery_Sensor::Set_SensorData(void)
{
    Battery_Voltage_LF_U32_ =  simulate_sensor->Simulate_BatterySensor();; // 11 gives numbers from 0 to 10;

}

Battery_Sensor &Battery_Sensor::Get_BatterySensor_Instance(void)
{
    static Battery_Sensor battery_Sensor_Instance;
    return battery_Sensor_Instance ;   
}
