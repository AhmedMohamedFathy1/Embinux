#include <iostream>

#include "AdpativeCruiseControl.hpp"


#define SPEED_DOWN_DECELERATION 7   // Average Decelartion on normal force braking is from 7-8
#define STOPPING_DECELERATION   9  // Average Decelartion on high force braking is from 9-10


Sensors_data_t& Sensors_data = Update_Sensors::GetSensorData();

void AdaptiveCruiseControl::decelerate(float &speed,const int &Deceleration)
{   
    // static int intenalSpeed = speed;
    const int timeStep = 1;  // Time step for simulation (seconds)
    while (speed > 0)
    {
        speed -= Deceleration * timeStep ;

        if(Deceleration == 7)
        {
            if(speed <  50)
            {
                speed = 50;
                break;
            }
            std::cout << "Decelerating... Current speed: " << speed << " km/h" << std::endl;

        }
        else if(Deceleration == 9)
        {
            if(speed < 0)
            {
                speed = 0;
                std::cout << "Car Stopped" << std::endl;
                break;
            }
            std::cout << "Stopping... Current speed: " << speed << " km/h" << std::endl;

        }
        else
        {
            break;
        }

    }
}
void AdaptiveCruiseControl::Speed_Control()
{
    bool &flag = simulate_sensor.Get_ObstacleFlag();

    std::cout << "ACC flag " << flag << std::endl;
    
    if(flag == true)
    {
        std::cout << "ACC: " << Sensors_data.RadarSensor_data << std::endl;
        if((Sensors_data.RadarSensor_data < DISTANCE_TO_SLOW_DOWN) && ((Sensors_data.RadarSensor_data > DISTANCE_TO_STOP)))
        {
            AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,SPEED_DOWN_DECELERATION);
        }
        else if(Sensors_data.RadarSensor_data < DISTANCE_TO_STOP)
        {
            AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,STOPPING_DECELERATION);
        }
     }
}

void AdaptiveCruiseControl::AdpativeCruiseControl_Check(void)
{
     AdaptiveCruiseControl::Speed_Control();
}
