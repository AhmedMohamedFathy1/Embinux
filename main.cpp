#include <iostream>
#include <chrono>  // For std::chrono
#include <thread>  // For std::this_thread::sleep_for


#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

#include "diagnostics.hpp"


using namespace std;
int main()
{
    Sensors_data_t sen_data;
    Diagnostics diagnostics;
    srand(time(0));


    while(1)
    {
        diagnostics.ExcesiveSpeed_Check();
        // update_sensors.Update_AllSesnors();

        // sen_data = update_sensors.GetSensorData();  

        // cout << "Main Speed: " << sen_data.SpeedSensor_data << endl ; 
        // cout << sen_data.RadarSensor_data << endl ; 
        // cout << sen_data.TemperatureSensor_data << endl ; 
        // cout << sen_data.BatterySensor_data << endl ; 

       std::this_thread::sleep_for(std::chrono::seconds(1));
    }
      return 0;
}