#include <iostream>
#include "wifi.hpp"

using namespace  std;
int main()
{

    Wifi_ShowStatus();
    Wifi_TurnOff();
    Wifi_ShowStatus();
    Wifi_TurnOn();
    // Wifi_ShowStatus();
}