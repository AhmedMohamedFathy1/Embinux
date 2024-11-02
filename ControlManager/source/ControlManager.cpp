#include "ControlManager.hpp"
#include <iostream>
#include "wifi.hpp"
#include <limits> // Include this for std::numeric_limits

#define  WIFI       1
#define  BLUETOOTH  2
#define  EXIT       3

void Main_StateMachine(void)
{
    int UserInput_GD_U8 = 0;
    std::cout << "1- Wifi" << std::endl;
    std::cout << "2- Bluetooth" << std::endl;
    std::cout << "3- Exit" << std::endl;
    std::cout << "Please Enter Value "<< std::endl;
    std::cin >> UserInput_GD_U8;

    switch (uint8_t(UserInput_GD_U8))
    {
    case WIFI:
        std::cout << "wifi" << std::endl;

        /* code */
        break;
    case BLUETOOTH:
    /* code */
    break;  

    case EXIT:
    /* code */
    break;  

    default:
        break;
    }
}

