#include <iostream>

#include "AdpativeCruiseControl.hpp"



Sensors_data_t& sensors_data = Update_Sensors::GetSensorData();

void AdaptiveCruiseControl::decelerate(const int &speed,const int &Deceleration)
{   
    static int intenalSpeed = speed;
    const int Braking_Decleration = Deceleration; 
    const int timeStep = 1;  // Time step for simulation (seconds)
    while (intenalSpeed > 0)
    {
        intenalSpeed -= Braking_Decleration * timeStep ;

        if(Braking_Decleration == 7)
        {
            std::cout << "Decelerating... Current speed: " << intenalSpeed << " km/h" << std::endl;
            if(intenalSpeed> 50)
            {
                intenalSpeed = 50;
                break;
            }
        }
        else if(Braking_Decleration == 9)
        {
            std::cout << "Stopping... Current speed: " << intenalSpeed << " km/h" << std::endl;

            if(intenalSpeed> 0)
            {
                intenalSpeed = 0;
                std::cout << "Car Stopped" << std::endl;
                break;
            }
        }
        else{}

 
    }
}
void AdaptiveCruiseControl::Speed_Control()
{

    // bool & FlagState =  simulate_sensor.GetFlagState();
    // std::cout << "ACC flag " <<  simulate_sensor.GetFlagState()  << std::endl;
    
    // if(FlagState == true)
    // {
        std::cout << "ACC: " << sensors_data.RadarSensor_data << std::endl;
        // if((update_Sensor.Sensors_data.RadarSensor_data < DISTANCE_TO_SLOW_DOWN) && ((update_Sensor.Sensors_data.RadarSensor_data > DISTANCE_TO_STOP)))
        // {
        //     AdaptiveCruiseControl::decelerate(update_Sensor.Sensors_data.SpeedSensor_data,7);
        // }
        // else if(update_Sensor.Sensors_data.RadarSensor_data < DISTANCE_TO_STOP)
        // {
        //    AdaptiveCruiseControl::decelerate(update_Sensor.Sensors_data.SpeedSensor_data,9);
        // }
    //  }
}

void AdaptiveCruiseControl::AdpativeCruiseControl_Check(void)
{
     AdaptiveCruiseControl::Speed_Control();
}
