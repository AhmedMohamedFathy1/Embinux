#include <iostream>

#include "diagnostics.hpp"

#define MAX_ALLOWED_SPEED 120


/**
 * @brief Check if speed increase over speed limit  
 * 
 */
void Diagnostics::ExcesiveSpeed_Check(void)
{
    Update_Sensors::Update_AllSesnors();
    if(Sensors_data.SpeedSensor_data > MAX_ALLOWED_SPEED)
    {
        std::cout << "Max Speed is :" << MAX_ALLOWED_SPEED << " km/h" << "\nCar Current Speed: " << Sensors_data.SpeedSensor_data << " km/h"<< std::endl;
    }
    else
    {
        std::cout << "Main Speed: " << Sensors_data.SpeedSensor_data << "km/h"<< std::endl ;
    }
}
