#ifndef __SENSORSIMULATORS__H__
#define __SENSORSIMULATORS__H__

class Simulate_Sensor
{
    private:
    
    public:
      float Simulate_SpeedSensor(int maxSpeed, int holdTime);
      int Simulate_TemperatureSensor(void);
      float Simulate_BatterySensor(void);
      int Simulate_FuelSensor(void);
};
// void Simulate_RadarSensor(int maxSpeed, int holdTime);



#endif  //!__SENSORSIMULATORS__H__

