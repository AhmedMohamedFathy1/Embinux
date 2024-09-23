#include "../header/FuelSensor.hpp"


int Fuel_Sensor::Get_SensorData(void)
{
    return Fuel_Capacity_LI_U32_;
}

void Fuel_Sensor::Set_SensorData(void)
{
     Fuel_Capacity_LI_U32_ =  simulate_sensor->Simulate_FuelSensor();
}
