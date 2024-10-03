#include <iostream>

#include "AdpativeCruiseControl.hpp"

#include "Logger.hpp"


VehicleLogger& ACC_logger = VehicleLogger::Logger_GetInstance("vehicle_log.txt");


#define MAX_MOTOR_TEMPERATURE 110 
// ACC_ConditionsFlags AdaptiveCruiseControl::ACC_conditionsflags_PDB;
bool ACC_ConditionsFlags::ACC_Slow_Down_Flag = false;
bool ACC_ConditionsFlags::ACC_Stopping_Flag = false;

Sensors_data_t& Sensors_data = Update_Sensors::GetSensorData();

Diagnostics_Flags ACC_diagnostics_flags = Diagnostics::Get_FlagsState();

ACC_ConditionsFlags ACC_conditionsFlags = AdaptiveCruiseControl::Get_ACC_FlagInstance();

/**
 * @brief if there is obstacle set to slow down or to stop
 * 
 */
void AdaptiveCruiseControl::Speed_Control()
{
    ACC_logger.logData("Sensor data : " + std::to_string( Sensors_data.RadarSensor_data) + " m , DISTANCE_TO_SLOW_DOWN:" + "55" +  " , DISTANCE_TO_STOP: " + "35" + " m");
    
    std::cout << "Sensor data : " << Sensors_data.RadarSensor_data <<" m , DISTANCE_TO_SLOW_DOWN: " << DISTANCE_TO_SLOW_DOWN << " m , DISTANCE_TO_STOP: " << DISTANCE_TO_STOP <<" m" << std::endl;
    if((Sensors_data.RadarSensor_data < DISTANCE_TO_SLOW_DOWN) && ((Sensors_data.RadarSensor_data > DISTANCE_TO_STOP)))
    {
        ACC_conditionsFlags.ACC_Stopping_Flag = false;
        ACC_conditionsFlags.ACC_Slow_Down_Flag = true;
    }
    else if(Sensors_data.RadarSensor_data < DISTANCE_TO_STOP)
    {
        ACC_conditionsFlags.ACC_Slow_Down_Flag = false;
        ACC_conditionsFlags.ACC_Stopping_Flag = true;
    }
}


/**
* @brief check of motor temp increase set flag to stop car 
* 
*/
void AdaptiveCruiseControl::MotorTemperature_Check(void)
{
    //std::cout << "Temp data : " << Sensors_data.TemperatureSensor_data << std::endl;
    if(Sensors_data.TemperatureSensor_data > MAX_MOTOR_TEMPERATURE)
    {
        ACC_conditionsFlags.ACC_Stopping_Flag = true;
    }
}
void AdaptiveCruiseControl::AdpativeCruiseControl_Manager(void)
{
    // priority 
    if (ACC_diagnostics_flags.ObstacleFound_Is_High_GDB == true)
    {
        AdaptiveCruiseControl::Speed_Control();
    }
    else if (ACC_diagnostics_flags.Motor_Temperature_Is_High_GDB == true)
    {
    AdaptiveCruiseControl::MotorTemperature_Check();
    }
}
/**
 * @brief  singleton design by only return one instance from the class all over the project
 * 
 * @return ACC_ConditionsFlags& 
 */
ACC_ConditionsFlags &AdaptiveCruiseControl::Get_ACC_FlagInstance(void)
{
    static ACC_ConditionsFlags ACC_conditionsflags_PDB;

    return ACC_conditionsflags_PDB;
}
