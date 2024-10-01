#include <iostream>

#include "diagnostics.hpp"
#include "SensorSimulators.hpp"

Scenarios_Flags &diagnostics_Scenarios_Flags = Simulate_Sensor::Get_Scenarios_Flags_Instance();

#define MAX_ALLOWED_SPEED 180

// #define MINIUM_DISTANCE_TO_SPEED_DOWN 

// #define MINIUM_TIME_TO_BRAKE 

 
 /* Motor Temp in celisus */
#define MAX_MOTOR_TEMPERATURE 110   

/* Battery Voltage */
#define BATTERY_FULLY_CHARGED 12.6 
#define BATTERY_PARTIALLY_CHARGED 12.4
#define BATTERY_LOW_CHARGE_CHARGED 12.2 
#define BATTERY_DISCHARGED_CHARGED 12.2
#define BATTERY_DEAD_CHARGED 11.8


/* Fuel Capacity in liter */
#define MIN_FUEL_CAPACITY 9   

/* Radar Distance in meter*/
#define DISTACNE_TO_SPEED_DOWM  100  // Min Fuel to fire Alaram
#define DISTACNE_TO_BRAKE  50  //Max Fuel Tank capacity 
#define VEHICLE_BRAKING_DECELERATION  7 // assume Vehicle Braking deceleration is 7m/s^2



Diagnostics_Flags Diagnostics::diagnostics_Flags;

// Initialize the static members of Diagnostics_Flags
bool Diagnostics_Flags::ObstacleFound_Is_High_GDB = false;
bool Diagnostics_Flags::Motor_Temperature_Is_High_GDB = false;


Diagnostics_Flags  & FlagState = Diagnostics::Get_FlagsState();

/**
 * @brief Check if speed increase over speed limit  
 * 
 */


void Diagnostics::ExcesiveSpeed_Check(void)
{
    if(Sensors_data.SpeedSensor_data > MAX_ALLOWED_SPEED)
    {
        std::cout << "Max Speed is :" << MAX_ALLOWED_SPEED << " km/h" << "\nCar Current Speed: " << static_cast<int>(Sensors_data.SpeedSensor_data) << " km/h"<< std::endl;
    }
    else
    {
        std::cout << "Vehicle Speed: " <<static_cast<int>(Sensors_data.SpeedSensor_data)<< " km/h"<< std::endl ;
    }
}

void Diagnostics::RadarDistance_Check(void)
{
    if(diagnostics_Scenarios_Flags.Scenario_Radar_Sesnor_Flag_LDB == true)
    {
        //  std::cout <<Sensors_data.RadarSensor_data << " m" << std::endl;
        float SpeedValue_m_s = (Sensors_data.SpeedSensor_data * 5 /18);
        SpeedValue_m_s *=SpeedValue_m_s;
        //  std::cout <<(SpeedValue_m_s / 7 )  << " m" << std::endl;

        if(((SpeedValue_m_s / 7)+10) > Sensors_data.RadarSensor_data)
        {
            //   Diagnostics_Flags::ObstacleFound_Is_High_GDB = true;
            FlagState.ObstacleFound_Is_High_GDB = true;
            
            std::cout << "Obstacle Found " << std::endl;
        }
    }
}

void Diagnostics::Temperature_Check(void)
{
    if(diagnostics_Scenarios_Flags.Scenario_Temperature_Sesnor_Flag_LDB== true)
    {
        if(Sensors_data.TemperatureSensor_data > MAX_MOTOR_TEMPERATURE)
        {
            FlagState.Motor_Temperature_Is_High_GDB = true;
            std::cout << "Car is Overhrating " << "\nMotor Temperature is: " << Sensors_data.TemperatureSensor_data  << " °C:" << std::endl;
        }

    }
}

void Diagnostics::Battery_Check(void)
{
    if(diagnostics_Scenarios_Flags.Scenario_Battery_Sesnor_Flag_LDB == true)
    {
        std::cout <<Sensors_data.BatterySensor_data << " v" << std::endl;
    
        // if(Sensors_data.BatterySensor_data > BATTERY_FULLY_CHARGED)
        // {
        //     std::cout <<"Battery is fully charged " << std::endl;
        // }
        if((Sensors_data.BatterySensor_data <= BATTERY_FULLY_CHARGED) && (Sensors_data.BatterySensor_data >= BATTERY_PARTIALLY_CHARGED))
        {
            std::cout <<"Battery is Partially charged " << std::endl;
        }
        else if((Sensors_data.BatterySensor_data <= BATTERY_PARTIALLY_CHARGED) && (Sensors_data.BatterySensor_data >= BATTERY_LOW_CHARGE_CHARGED))
        {
            std::cout <<"Battery is Low Charge " << std::endl;
        }
        else if((Sensors_data.BatterySensor_data <= BATTERY_LOW_CHARGE_CHARGED) && (Sensors_data.BatterySensor_data >= BATTERY_DEAD_CHARGED))
        {
            std::cout <<"Battery is Discharged " << std::endl;
        }
        else if(Sensors_data.BatterySensor_data < BATTERY_DEAD_CHARGED)
        {
            std::cout <<"Battery is Dead " << std::endl;
        }
    }
}
/**
 * @brief Check if fuel is below 9 liter 
 * 
 * @return int 
 */
void Diagnostics::LowFuel_Check(void)
{
    if(diagnostics_Scenarios_Flags.Scenario_Fuel_Sesnor_Flag_LDB == true)
    {
        // std::cout <<Sensors_data.FuelCapacity << " L" << std::endl;
        
        if(Sensors_data.FuelCapacity < MIN_FUEL_CAPACITY)
        {
            std::cout <<"Low Fuel" << std::endl;
        }
    }
}

Diagnostics_Flags &Diagnostics::Get_FlagsState(void)
{
    return diagnostics_Flags;
}


void Diagnostics::Run_Diagnostics(void)
{
        // Update all sensors Value
    Update_Sensors::Update_AllSesnors();

    Diagnostics::ExcesiveSpeed_Check();

    Diagnostics::Temperature_Check();

    Diagnostics::Battery_Check();

    Diagnostics::LowFuel_Check();

    Diagnostics::RadarDistance_Check();  

    std::cout << std::endl;
}


