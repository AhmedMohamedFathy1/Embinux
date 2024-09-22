#include <iostream>

#include "diagnostics.hpp"

#define MAX_ALLOWED_SPEED 120

// #define MINIUM_DISTANCE_TO_SPEED_DOWN 

// #define MINIUM_TIME_TO_BRAKE 

 
#define MAX_MOTOR_TEMPERATURE 110 // celisus 

/**
 * @brief Check if speed increase over speed limit  
 * 
 */

void Diagnostics::ExcesiveSpeed_Check(void)
{
    if(Sensors_data.SpeedSensor_data > MAX_ALLOWED_SPEED)
    {
        std::cout << "Max Speed is :" << MAX_ALLOWED_SPEED << " km/h" << "\nCar Current Speed: " << Sensors_data.SpeedSensor_data << " km/h"<< std::endl;
    }
    else
    {
        std::cout << "Main Speed: " << Sensors_data.SpeedSensor_data << "km/h"<< std::endl ;
    }
}

void Diagnostics::RadarDistance_Check(void)
{
    
}

void Diagnostics::Temperature_Check(void)
{
    if(Sensors_data.TemperatureSensor_data > MAX_MOTOR_TEMPERATURE)
    {
        std::cout << "Car is Overhrating " << "\n Motor Temperature is: " << Sensors_data.TemperatureSensor_data  << " °C:" << std::endl;
    }
    else
    {
        std::cout << "Normal Temperature: " << Sensors_data.TemperatureSensor_data << "°C"<< std::endl ;
    }
}

void Diagnostics::Battery_Check(void)
{

}

void Diagnostics::Run_Diagnostics(void)
{
    // Update all sensors Value
    Update_Sensors::Update_AllSesnors();

    Diagnostics::ExcesiveSpeed_Check();

    Diagnostics::Temperature_Check();
}