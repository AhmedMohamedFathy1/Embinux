#include "../header/UpdateSesnors.hpp"

void Update_Sensors::Update_AllSesnors(void)
{   
     speed_sensor.Set_SensorData();
     radar_sensor.Set_SensorData();
     temperature_sensor.Set_SensorData();
     battery_sensor.Set_SensorData();

     Sensors_data.SpeedSensor_data = speed_sensor.Get_SensorData();
     Sensors_data.RadarSensor_data = radar_sensor.Get_SensorData();
     Sensors_data.TemperatureSensor_data = temperature_sensor.Get_SensorData();
     Sensors_data.BatterySensor_data = battery_sensor.Get_SensorData();

}
Sensors_data_t Update_Sensors::GetSensorData(void) 
{
    return Sensors_data;
}

