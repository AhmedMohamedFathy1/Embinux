#include <iostream>

#include "AdpativeCruiseControl.hpp"




#define MAX_MOTOR_TEMPERATURE 110 


Sensors_data_t& Sensors_data = Update_Sensors::GetSensorData();

Diagnostics_Flags ACC_diagnostics_flags = Diagnostics::Get_FlagsState();

void AdaptiveCruiseControl::Speed_Control()
{
    std::cout << "sensor data : " << Sensors_data.RadarSensor_data << " , DISTANCE_TO_SLOW_DOWN: " << DISTANCE_TO_SLOW_DOWN << " , DISTANCE_TO_STOP: " << DISTANCE_TO_STOP << std::endl;
    if((Sensors_data.RadarSensor_data < DISTANCE_TO_SLOW_DOWN) && ((Sensors_data.RadarSensor_data > DISTANCE_TO_STOP)))
    {
        //  AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,SPEED_DOWN_DECELERATION,SLOW_DOWN_SPEED);
    }
    else if(Sensors_data.RadarSensor_data < DISTANCE_TO_STOP)
    {
        //   AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,STOPPING_DECELERATION,TOTAL_STOP);
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