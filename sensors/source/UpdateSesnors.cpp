#include "../header/UpdateSesnors.hpp"
#include  <iostream>

Sensors_data_t Update_Sensors::Sensors_data;


/**
 * @brief function get all sensor value and set them on struct 
 * 
 */
void Update_Sensors::Update_AllSesnors(void)
{   
     // set all data and update on its members 
     speed_sensor.Set_SensorData();
     radar_sensor.Set_SensorData();
     temperature_sensor.Set_SensorData();
     battery_sensor.Set_SensorData();
     fuel_sensor.Set_SensorData();

// get value of each sensor in the struct 
     Sensors_data.SpeedSensor_data = speed_sensor.Get_SensorData();
     Sensors_data.RadarSensor_data = radar_sensor.Get_SensorData();
     Sensors_data.TemperatureSensor_data = temperature_sensor.Get_SensorData();
     Sensors_data.BatterySensor_data = battery_sensor.Get_SensorData();
     Sensors_data.FuelCapacity = fuel_sensor.Get_SensorData();

}

/**
 * @brief singleton design by only return one instance fromthe struct all over the project
 * 
 * @return Sensors_data_t& 
 */
Sensors_data_t& Update_Sensors::GetSensorData(void) 
{
     return Sensors_data;
}

