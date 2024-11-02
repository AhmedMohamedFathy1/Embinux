#include "wifi.hpp"
#include "FileHandler.hpp"

#include <cstdlib>
#include <iostream>

#include <string_view>

#include <termios.h>
#include <unistd.h>
#include <limits>

FileHandler fileHandler;

void Wifi::Wifi_TurnOn(void)
{
    // Execute command to turn on WiFi
    std::cout << "****************  Turning WiFi on... ****************" << std::endl;
    system("nmcli radio wifi on");
}

void Wifi::Wifi_TurnOff(void)
{
    // Execute command to turn off WiFi
    std::cout << "**************** Turning WiFi off... ****************" << std::endl;
    system("nmcli radio wifi off");
}

void Wifi::Wifi_ShowStatus(void)
{
    // Execute command to show WiFi status 
    std::cout << "**************** Wifi Status ****************" << std::endl;
    system("nmcli d");
}

void Wifi::Wifi::Wifi_SaveNetwork(const std::string& SSID_WifiName, const std::string &SSID_Password)
{
    Wifi::wifiCredentials[SSID_WifiName] = SSID_Password;
}

std::string password;
std::string& getPassword()
 {
    termios oldt, newt;
    
    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO); // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::cout << "Please enter Wifi Password" << std::endl;
    std::cin >> password; 

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl; // Move to the next line after input

    return password;
}

void Wifi::connectToWifi(std::string_view WifiName, std::string_view Password)
{
    std::cout << "Connecting to " << WifiName << "..." << std::endl;

    // Create the command using string concatenation
    std::string command = "nmcli d wifi connect \"" + std::string(WifiName) + "\" password \"" + std::string(Password) + "\"";

    // Execute the command
    int status = std::system(command.c_str());

    if(status == 0)
    {
        Wifi::Wifi_SaveNetwork(std::string(WifiName),std::string(Password));
        fileHandler.SaveFile(Wifi::wifiCredentials,"wifiCredentialsFile.txt");
    }
    else
    {
    }
}

void Wifi::Wifi_ConnectToNetwork(void)
{
    std::cout << "**************** Wifi Connecct ****************" << std::endl;
    std::string WifiName;
    std::string WifiPassword;
    // check first if wifi is on 
    system("nmcli r wifi on");
    //list the available WiFi networks:
    system("nmcli d wifi list");
    std::cout << "Please enter Wifi Name" << std::endl;
    // std::cin >> WifiName; 
    std::getline(std::cin, WifiName);

    WifiPassword = getPassword(); 
    connectToWifi(WifiName,WifiPassword);
}

void Wifi::Wifi_StateMachine(void)
{
}


