#include <iostream>
#include "wifi.hpp"
#include "ControlManager.hpp"
#include "FileHandler.hpp"


using namespace  std;


int main()
{

    Wifi wifi;
    
    wifi.Wifi_ConnectToNetwork();

    //Main_StateMachine();    
}