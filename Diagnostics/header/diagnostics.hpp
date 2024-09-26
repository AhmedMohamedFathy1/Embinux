#ifndef __DIAGNOSTICS__H__
#define __DIAGNOSTICS__H__

#include "UpdateSesnors.hpp"

struct Diagnostics_Flags 
{
  static bool ObstacleFound_Is_High_GDB;

  static bool Motor_Temperature_Is_High_GDB;
};


class Diagnostics: public Update_Sensors
{
    private:
    public:
      static Diagnostics_Flags diagnostics_Flags;

      Sensors_data_t &Sensors_data = Update_Sensors::GetSensorData();

      void Run_Diagnostics(void);

      void ExcesiveSpeed_Check(void);

      void RadarDistance_Check(void);

      void Temperature_Check(void);

      void Battery_Check(void);

      void LowFuel_Check(void);

      static Diagnostics_Flags& Get_FlagsState(void);

};

#endif  //!__DIAGNOSTICS__H__
