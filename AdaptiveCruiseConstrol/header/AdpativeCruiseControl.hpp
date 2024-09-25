#ifndef __ADPATIVECRUISECONTROL__H__
#define __ADPATIVECRUISECONTROL__H__

#include "UpdateSesnors.hpp"
#include "SensorSimulators.hpp"


#define  NORMAL_BRAKING_DECELRATION  7 
#define  FULL_BRAKING_DECELRATION  9 

#define  SPEED_M_S  25  // 90km/h for testing is 25m/s 


// The braking distance is calculated using the formula:
// Braking Distance=Speed^2×Deceleration


// 1. Normal Braking (7 m/s²):
// Braking Distance=25^ / 2×7 ≈ 44.64 meters

// 2. Full-Force Braking (9 m/s²):
// Braking Distance=25^2 / 2×9≈ 34.72 meters
#define  DISTANCE_TO_SLOW_DOWN  55 //45 +10(Safety Margin) 

#define  DISTANCE_TO_STOP  35

class AdaptiveCruiseControl 
{
    protected: 
      Simulate_Sensor simulate_sensor;
      Update_Sensors update_Sensor; // has-a Compistion is better as i just want to access data from this class not all data 
      Speed_Sensor speed_Sensor;
      
    public:
     void Speed_Control(void);
     void decelerate(float &speed,const int &Deceleration);
  

    void AdpativeCruiseControl_Check(void);
};


#endif  //!__ADPATIVECRUISECONTROL__H__