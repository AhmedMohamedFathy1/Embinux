#ifndef __WIFI__H__
#define __WIFI__H__

#include <map>
#include <string>
class Wifi
{
  private:  

    void Wifi_TurnOn(void);
    void Wifi_TurnOff(void);
    void Wifi_ShowStatus(void);  
    void Wifi_SaveNetwork(const std::string& SSID_WifiName, const std::string &SSID_Password);  


    std::map<std::string , std::string> wifiCredentials; // A map to store SSIDs and their corresponding passwords 

  public:
    void Wifi_StateMachine(void);
    void Wifi_ConnectToNetwork(void);  
    void connectToWifi(std::string_view WifiName, std::string_view Password);
};





#endif  //!__WIFI__H__