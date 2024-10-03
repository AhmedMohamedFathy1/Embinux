#ifndef __SENSORSIMULATORS__H__
#define __SENSORSIMULATORS__H__


/**
 * @brief enum hold scanrio for switch case 
 * 
 */
enum class ScenarioStates
{
    None,
    Scenario1,
    Scenario2,
    Scenario3,
    Scenario4,
    Scenario5
};


/**
 * @brief struct that hold flags for each scenario which to run and check this in Sesnor simulator file
 * 
 */
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
      float Simulate_SpeedSensor(void);
      int Simulate_TemperatureSensor(void);
      float Simulate_BatterySensor(void);
      int Simulate_FuelSensor(void);
      float Simulate_RadarSensor(void);

      void Simulate_Scenario_1(void);
      void Simulate_Scenario_2(void);
      void Simulate_Scenario_3(void);
      void Simulate_Scenario_4(void);
      void Simulate_Scenario_5(void);

      void Scenario_Init_state(void);

      static Scenarios_Flags &Get_Scenarios_Flags_Instance(void);

      float decelerate(float &speed,const int &Deceleration);

      void Scenario_Handler(void);

};

#endif  //!__SENSORSIMULATORS__H__

