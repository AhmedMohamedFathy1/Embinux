#include "../header/FuelSensor.hpp"
#include "FuelSensor.hpp"


float Fuel_Sensor::Get_SensorData(void)
{
    return Fuel_Capacity_LI_U32_;
}

void Fuel_Sensor::Set_SensorData(void)
{
     Fuel_Capacity_LI_U32_ =  simulate_sensor->Simulate_FuelSensor();
}

Fuel_Sensor &Fuel_Sensor::Get_FuelSensor_Instance(void)
{
    static Fuel_Sensor fuel_Sensor_Instance;
    return fuel_Sensor_Instance ;     
}
