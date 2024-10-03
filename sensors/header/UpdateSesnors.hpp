#ifndef UPDATE_SENSOR
#define UPDATE_SENSOR

#include "SpeedSensor.hpp"
#include "RadarSensor.hpp"
#include "TempSensor.hpp"
#include "BatterySensor.hpp"
#include "FuelSensor.hpp"

typedef struct 
{
    float SpeedSensor_data ;
    float RadarSensor_data ;
    float TemperatureSensor_data ;
    float BatterySensor_data ;
    int FuelCapacity;
    
}Sensors_data_t;

// Composition
class Update_Sensors
{
        private:

// proteceted as i want to inherit from this class 
        protected:   
            Speed_Sensor & speed_sensor = Speed_Sensor::Get_SpeedSensor_Instance(); 
            Radar_Sensor &radar_sensor = Radar_Sensor::Get_RadarSensor_Instance(); 
            Temperature_Sensor &temperature_sensor= Temperature_Sensor::Get_TemperatureSensor_Instance(); 
            Battery_Sensor &battery_sensor= Battery_Sensor::Get_BatterySensor_Instance(); 
            Fuel_Sensor &fuel_sensor= Fuel_Sensor::Get_FuelSensor_Instance();

            static Sensors_data_t Sensors_data;

        public:
            static Sensors_data_t& GetSensorData(void);

            void Update_AllSesnors(void);

            virtual ~Update_Sensors(){}

};


#endif