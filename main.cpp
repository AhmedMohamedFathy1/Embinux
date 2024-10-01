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
    
    while(1)
    {
        simulate_Sensor.Simulate_Scenario_1();
        diagnostics.Run_Diagnostics();

        ACC.AdpativeCruiseControl_Manager();


       std::this_thread::sleep_for(std::chrono::seconds(1));
    }
      return 0;
}