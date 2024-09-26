#include <iostream>

#include "AdpativeCruiseControl.hpp"


#define SPEED_DOWN_DECELERATION 7   // Average Decelartion on normal force braking is from 7-8
#define STOPPING_DECELERATION   9  // Average Decelartion on high force braking is from 9-10
#define TOTAL_STOP 0 
#define SLOW_DOWN_SPEED 50 

#define MAX_MOTOR_TEMPERATURE 110 


Sensors_data_t& Sensors_data = Update_Sensors::GetSensorData();

Diagnostics_Flags ACC_diagnostics_flags = Diagnostics::Get_FlagsState();


void AdaptiveCruiseControl::decelerate(float &speed,const int &Deceleration,const float &Required_Speed)
{ 
    const int timeStep = 1; // Time step for simulation (seconds)
    while (speed > TOTAL_STOP)
    {
        speed -= Deceleration * timeStep ;
        ACC_speed_Sensor.Set_SensorData(speed); // update new value in the class 

        if(Deceleration == SPEED_DOWN_DECELERATION)
        {
            if(speed < Required_Speed)
            {
            speed = Required_Speed;
            break;
            }
            std::cout << "Decelerating... Current speed: " << speed << " km/h" << std::endl;
        }

        else if(Deceleration == STOPPING_DECELERATION)
        {
            if(speed < TOTAL_STOP)
            {
            speed = TOTAL_STOP;
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
    std::cout << "sensor data : " << Sensors_data.RadarSensor_data << " , DISTANCE_TO_SLOW_DOWN: " << DISTANCE_TO_SLOW_DOWN << " , DISTANCE_TO_STOP: " << DISTANCE_TO_STOP << std::endl;
    if((Sensors_data.RadarSensor_data < DISTANCE_TO_SLOW_DOWN) && ((Sensors_data.RadarSensor_data > DISTANCE_TO_STOP)))
    {
         AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,SPEED_DOWN_DECELERATION,SLOW_DOWN_SPEED);
    }
    else if(Sensors_data.RadarSensor_data < DISTANCE_TO_STOP)
    {
          AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,STOPPING_DECELERATION,TOTAL_STOP);
    }

}


/**
* @brief 
* 
*/
void AdaptiveCruiseControl::MotorTemperature_Check(void)
{
// bool &flag = diagnostics.Get_MotorTemp_Flag();
// if(flag == true)
// {
// std::cout << "Temp data : " << Sensors_data.TemperatureSensor_data << std::endl;
// if(Sensors_data.TemperatureSensor_data > MAX_MOTOR_TEMPERATURE)
// {
// AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,SPEED_DOWN_DECELERATION,TOTAL_STOP);
// }

// } 
}
void AdaptiveCruiseControl::AdpativeCruiseControl_Manager(void)
{
    if (ACC_diagnostics_flags.ObstacleFound_Is_High_GDB == true)
    {
        AdaptiveCruiseControl::Speed_Control();
    }
    // else if (diagnostics_flags.Motor_Temperature_Is_High_GDB == true)
    // {
    // AdaptiveCruiseControl::MotorTemperature_Check();
    // }
}