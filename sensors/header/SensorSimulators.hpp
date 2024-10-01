#ifndef __SENSORSIMULATORS__H__
#define __SENSORSIMULATORS__H__

enum class VehicleState
{
    NormalDriving,
    SlowingDown,
    Stopping
};

struct Scenarios_Flags
{
  bool Scenario_Speed_Sesnor_Flag_LDB = false;
  bool Scenario_Radar_Sesnor_Flag_LDB = false;
  bool Scenario_Temperature_Sesnor_Flag_LDB = false;
  bool Scenario_Fuel_Sesnor_Flag_LDB = false;
  bool Scenario_Battery_Sesnor_Flag_LDB = false;

};

class Simulate_Sensor
{
    protected: 
    public:     
      float Simulate_SpeedSensor(int maxSpeed, int holdTime);
      int Simulate_TemperatureSensor(void);
      float Simulate_BatterySensor(void);
      int Simulate_FuelSensor(void);
      float Simulate_RadarSensor(void);

      void Simulate_Scenario_1(void);
      // float Simulate_Scenario_2(float &speed,float &temperature);

      static Scenarios_Flags &Get_Scenarios_Flags_Instance(void);


      float decelerate(float &speed,const int &Deceleration);


};

#endif  //!__SENSORSIMULATORS__H__

