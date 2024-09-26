#ifndef __SENSORSIMULATORS__H__
#define __SENSORSIMULATORS__H__

class Simulate_Sensor
{
    protected:
     
    public: 
      static bool Obstacle_SpeedFlag_GDB;

      
      float Simulate_SpeedSensor(int maxSpeed, int holdTime);
      int Simulate_TemperatureSensor(void);
      float Simulate_BatterySensor(void);
      int Simulate_FuelSensor(void);
      float Simulate_RadarSensor(void);
      float Simulate_Scenario_1(float &speed);

      static bool& Get_ObstacleFlag(void);
};



#endif  //!__SENSORSIMULATORS__H__

