#include <iostream>

#include "AdpativeCruiseControl.hpp"


#define MAX_MOTOR_TEMPERATURE 110 
ACC_ConditionsFlags AdaptiveCruiseControl::ACC_conditionsflags_PDB;

Sensors_data_t& Sensors_data = Update_Sensors::GetSensorData();

Diagnostics_Flags ACC_diagnostics_flags = Diagnostics::Get_FlagsState();


void AdaptiveCruiseControl::Speed_Control()
{
    std::cout << "sensor data : " << Sensors_data.RadarSensor_data << " , DISTANCE_TO_SLOW_DOWN: " << DISTANCE_TO_SLOW_DOWN << " , DISTANCE_TO_STOP: " << DISTANCE_TO_STOP << std::endl;
    if((Sensors_data.RadarSensor_data < DISTANCE_TO_SLOW_DOWN) && ((Sensors_data.RadarSensor_data > DISTANCE_TO_STOP)))
    {
        ACC_conditionsflags_PDB.ACC_Stopping_Flag = false;
        ACC_conditionsflags_PDB.ACC_Slow_Down_Flag = true;
        std::cout << "declerate in slown down " << AdaptiveCruiseControl::ACC_conditionsflags_PDB.ACC_Slow_Down_Flag << std::endl;   
        //  AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,SPEED_DOWN_DECELERATION,SLOW_DOWN_SPEED);
    }
    else if(Sensors_data.RadarSensor_data < DISTANCE_TO_STOP)
    {
        ACC_conditionsflags_PDB.ACC_Slow_Down_Flag = false;
        ACC_conditionsflags_PDB.ACC_Stopping_Flag = true;

        std::cout << "declerate in stopping " << AdaptiveCruiseControl::ACC_conditionsflags_PDB.ACC_Stopping_Flag << std::endl;   
        //   AdaptiveCruiseControl::decelerate(Sensors_data.SpeedSensor_data,STOPPING_DECELERATION,TOTAL_STOP);
    }
    // else
    // {
    //     ACC_conditionsFlags.ACC_Slow_Down_Flag = false;
    //     ACC_conditionsFlags.ACC_Stopping_Flag = false;
    // }

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

ACC_ConditionsFlags &AdaptiveCruiseControl::Get_ACC_FlagInstance(void)
{
    return ACC_conditionsflags_PDB;
}
