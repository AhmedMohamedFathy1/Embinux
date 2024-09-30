#include "../header/TempSensor.hpp"
#include "TempSensor.hpp"

/*  Temperature Sensor */
float Temperature_Sensor::Get_SensorData(void)
{
   return Temperature_LF_U32_; 
 
}

void Temperature_Sensor::Set_SensorData(float value)
{
    Temperature_LF_U32_ =  simulate_sensor->Simulate_TemperatureSensor(); // 11 gives numbers from 0 to 10;

}

Temperature_Sensor Temperature_Sensor::Get_TemperatureSensor_Instance(void)
{
    static Temperature_Sensor temperatureSensor_Instance;
    return temperatureSensor_Instance ;
}
