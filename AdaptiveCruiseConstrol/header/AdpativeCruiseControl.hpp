#ifndef __ADPATIVECRUISECONTROL__H__
#define __ADPATIVECRUISECONTROL__H__

#include "UpdateSesnors.hpp"
#include "SensorSimulators.hpp"
#include "diagnostics.hpp"
#include "SpeedSensor.hpp"

#define  NORMAL_BRAKING_DECELRATION  7 
#define  FULL_BRAKING_DECELRATION  9 

#define  SPEED_M_S  25  // 90km/h for testing is 25m/s 

#define  DISTANCE_TO_SLOW_DOWN  55 //45 +10(Safety Margin) 

#define  DISTANCE_TO_STOP  35

struct ACC_ConditionsFlags
{
  static bool ACC_Slow_Down_Flag ;
  static bool ACC_Stopping_Flag ;
};


class AdaptiveCruiseControl 
{
    protected: 
      Simulate_Sensor simulate_sensor;
      Update_Sensors update_Sensor; // has-a Compistion is better as i just want to access data from this class not all data 
      Speed_Sensor ACC_speed_Sensor = Speed_Sensor::Get_SpeedSensor_Instance();
      Diagnostics diagnostics; 
      

    public:

     void Speed_Control(void);
     void MotorTemperature_Check(void);

     void AdpativeCruiseControl_Manager(void);

     static ACC_ConditionsFlags & Get_ACC_FlagInstance(void); 
};


#endif  //!__ADPATIVECRUISECONTROL__H__
