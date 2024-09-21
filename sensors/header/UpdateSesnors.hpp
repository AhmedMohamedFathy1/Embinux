#ifndef UPDATE_SENSOR
#define UPDATE_SENSOR

#include "SpeedSensor.hpp"
#include "RadarSensor.hpp"
#include "TempSensor.hpp"
#include "BatterySensor.hpp"

typedef struct 
{
    float SpeedSensor_data ;
    float RadarSensor_data ;
    float TemperatureSensor_data ;
    float BatterySensor_data ;
}Sensors_data_t;

// Composition
class Update_Sensors
{
        private:
            Speed_Sensor speed_sensor; 
            Radar_Sensor radar_sensor; 
            Temperature_Sensor temperature_sensor; 
            Battery_Sensor battery_sensor; 

            Sensors_data_t Sensors_data;

        public:
            void Update_AllSesnors(void);

            Sensors_data_t GetSensorData(void);

            virtual ~Update_Sensors(){}

};


#endif