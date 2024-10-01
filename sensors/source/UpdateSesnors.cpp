#include "../header/UpdateSesnors.hpp"
#include  <iostream>

Sensors_data_t Update_Sensors::Sensors_data;

void Update_Sensors::Update_AllSesnors(void)
{   

     speed_sensor.Set_SensorData(25);
     radar_sensor.Set_SensorData(1);
     temperature_sensor.Set_SensorData(1);
     battery_sensor.Set_SensorData(1);
     fuel_sensor.Set_SensorData(1);

     Sensors_data.SpeedSensor_data = speed_sensor.Get_SensorData();
     Sensors_data.RadarSensor_data = radar_sensor.Get_SensorData();
     Sensors_data.TemperatureSensor_data = temperature_sensor.Get_SensorData();
     Sensors_data.BatterySensor_data = battery_sensor.Get_SensorData();
     Sensors_data.FuelCapacity = fuel_sensor.Get_SensorData();
   //  std::cout << "speed: " << Sensors_data.SpeedSensor_data << std::endl;

}
Sensors_data_t& Update_Sensors::GetSensorData(void) 
{
     return Sensors_data;
}

