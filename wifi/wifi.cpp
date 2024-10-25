#include "wifi.hpp"
#include <cstdlib>
#include <iostream>

void Wifi_TurnOn(void)
{
    // Execute command to turn on WiFi
    std::cout << "****************  Turning WiFi on... ****************" << std::endl;
    system("nmcli radio wifi on");
}

void Wifi_TurnOff(void)
{
    // Execute command to turn off WiFi
    std::cout << "**************** Turning WiFi off... ****************" << std::endl;
    system("nmcli radio wifi off");
}

void Wifi_ShowStatus(void)
{
    // Execute command to show WiFi status 
    std::cout << "**************** Wifi Status ****************" << std::endl;
    system("nmcli d");
    
}
