#ifndef __DIAGNOSTICS__H__
#define __DIAGNOSTICS__H__

#include "UpdateSesnors.hpp"


class Diagnostics: public Update_Sensors
{
    private:
    public:
      Sensors_data_t &Sensors_data = Update_Sensors::GetSensorData();
      void Run_Diagnostics(void);

      void ExcesiveSpeed_Check(void);

      void RadarDistance_Check(void);

      void Temperature_Check(void);

      void Battery_Check(void);

      void LowFuel_Check(void);


};


#endif  //!__DIAGNOSTICS__H__