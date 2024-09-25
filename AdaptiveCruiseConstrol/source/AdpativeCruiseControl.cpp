#include <iostream>

#include "AdpativeCruiseControl.hpp"



Sensors_data_t& Sensors_data = Update_Sensors::GetSensorData();

void AdaptiveCruiseControl::decelerate(float &speed,const int &Deceleration)
{   
    // static int intenalSpeed = speed;
    const int Braking_Decleration = Deceleration; 
    const int timeStep = 1;  // Time step for simulation (seconds)
    while (speed > 0)
    {
        speed -= Braking_Decleration * timeStep ;

        if(Braking_Decleration == 7)
        {
            std::cout << "Decelerating... Current speed: " << speed << " km/h" << std::endl;
            if(speed <  50)
            {
                speed = 50;
                break;
            }
        }
        else if(Braking_Decleration == 9)
        {
            std::cout << "Stopping... Current speed: " << speed << " km/h" << std::endl;

            if(speed < 0)
            {
                speed = 0;
                std::cout << "Car Stopped" << std::endl;
                break;
            }
        }
        else
        {
            break;
        }

    }
}
void AdaptiveCruiseControl::Speed_Control()
{

    // bool & FlagState =  simulate_sensor.GetFlagState();
    // std::cout << "ACC flag " <<  simulate_sensor.GetFlagState()  << std::endl;
    
    // if(FlagState == true)
    // {
        std::cout << "ACC: " << Sensors_data.RadarSensor_data << std::endl;
        if((Sensors_data.RadarSensor_data < DISTANCE_TO_SLOW_DOWN) && ((Sensors_data.RadarSensor_data > DISTANCE_TO_STOP)))
        {
            AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,7);
        }
        else if(Sensors_data.RadarSensor_data < DISTANCE_TO_STOP)
        {
            AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,9);
        }
    //  }
}

void AdaptiveCruiseControl::AdpativeCruiseControl_Check(void)
{
     AdaptiveCruiseControl::Speed_Control();
}
