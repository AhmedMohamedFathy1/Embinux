#include <iostream>
#include <chrono>  // For std::chrono
#include <thread>  // For std::this_thread::sleep_for

#include "diagnostics.hpp"
#include "AdpativeCruiseControl.hpp"
#include "SensorSimulators.hpp"

using namespace std;
int main()
{
  //  Sensors_data_t &Sensors_data = Update_Sensors::GetSensorData();
    Diagnostics diagnostics;
    AdaptiveCruiseControl ACC;
    Simulate_Sensor simulate_Sensor;
    float MainSpeed = 0;
    while(1)
    {

        MainSpeed = simulate_Sensor.Simulate_SpeedSensor(120,5);

        diagnostics.Run_Diagnostics(MainSpeed);

        ACC.AdpativeCruiseControl_Manager();


       std::this_thread::sleep_for(std::chrono::seconds(1));
    }
      return 0;
}