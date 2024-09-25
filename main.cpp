#include <iostream>
#include <chrono>  // For std::chrono
#include <thread>  // For std::this_thread::sleep_for

#include "diagnostics.hpp"
#include "AdpativeCruiseControl.hpp"

using namespace std;
int main()
{
  //  Sensors_data_t &Sensors_data = Update_Sensors::GetSensorData();
    Diagnostics diagnostics;
    AdaptiveCruiseControl ACC;

    while(1)
    {
        diagnostics.Run_Diagnostics();
        //std::cout << "Radar in main" << Sensors_data.RadarSensor_data << std::endl;

        ACC.AdpativeCruiseControl_Check();

       std::this_thread::sleep_for(std::chrono::seconds(1));
    }
      return 0;
}