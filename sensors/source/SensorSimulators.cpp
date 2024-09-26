
#include <random>
#include  <iostream>

#include "../header/SensorSimulators.hpp"
#include "SensorSimulators.hpp"
 /* Vehcile Speed */
#define VEHICLE_MAX_SPEED 180  

/* Motor Temperature  Voltage*/

#define MAX_ALLOWED_MOTOR_TEMPERATURE 130 // celisus // Max allowed is 110,  i let space to test over heating 
#define NORAML_OPERATING_MOTOR_TEMPERATURE 105 // celisus // Max allowed is 110,  i let space to test over heating 

/* Battery Voltage*/
#define MIN_VOLTAGE 11.5f  // Min Battery Voltage 
#define MAX_VOLTAGE 13.0f  //Max Battery Voltage 

/* Battery Voltage*/
#define MIN_FUEl  9  // Min Fuel to fire Alaram
#define MAX_FUEL  37  //Max Fuel Tank capacity 

/* Radar Distance in meter*/
#define MIN_RADAR_DISTANCE  25  // Min Fuel to fire Alaram
#define MAX_RADAR_DISTANCE  350  // Min Fuel to fire Alaram


#define HOLD_TIME 5

bool SpeedFlag = true;
bool TempFlag = true;

bool Simulate_Sensor::Obstacle_SpeedFlag_GDB = false;

float Simulate_Sensor::Simulate_SpeedSensor(int maxSpeed, int holdTime) 
{
    static int counter = holdTime;
    // Set up random number generation
    std::random_device rd;   // Seed source
    std::mt19937 gen(rd());  // Mersenne Twister engine
    std::uniform_int_distribution<> speedIncreaseDist(1, 20);  // Speed increase by 1-10 units
    std::uniform_int_distribution<> speedDecreaseDist(1, 20);  // Speed decrease by 1-10 units

    static float speed = 0;  // Initial speed
    // Speed increase
    if ((speed < VEHICLE_MAX_SPEED)  && (SpeedFlag == true))
    {
        speed += speedIncreaseDist(gen);  // Increase speed randomly
        if (speed > VEHICLE_MAX_SPEED)
        {
            SpeedFlag = false;
            speed = VEHICLE_MAX_SPEED;  // Cap at max speed
        }
    }

    // Hold at max speed
    else if((speed >= VEHICLE_MAX_SPEED )&& (counter>0))
    {
        counter--;
    }

    // Speed decrease
    else if ((speed <= VEHICLE_MAX_SPEED) && (speed > 0)) 
    {
        speed -= speedDecreaseDist(gen);  // Decrease speed randomly
        if (speed < 0) 
        {
            speed = 0;  // Ensure speed doesn't go below 0
        }
    }
    return speed;
}


int Simulate_Sensor::Simulate_TemperatureSensor(void) 
{

    static int TempCounter = 5;
    // Set up random number generation
    std::random_device rd;   // Seed source
    std::mt19937 gen(rd());  // Mersenne Twister engine
    std::uniform_int_distribution<> TempertureIncreaseDist(1, 10);  // temp increase by 1-10 units
    std::uniform_int_distribution<> TempertureDecreaseDist(1, 10);  // temp decrease by 1-10 units

    static float Motor_Temperature = 70;  // Initial temp
    // temp increase
    if ((Motor_Temperature < MAX_ALLOWED_MOTOR_TEMPERATURE)  && (TempFlag == true))
    {
        Motor_Temperature += TempertureIncreaseDist(gen);  // Increase temp randomly
        if (Motor_Temperature > MAX_ALLOWED_MOTOR_TEMPERATURE)
        {
            Motor_Temperature = MAX_ALLOWED_MOTOR_TEMPERATURE;
            TempFlag = false;
        }
    }

    // Hold at max MAX_ALLOWED_MOTOR_TEMPERATURE
    else if((Motor_Temperature >= MAX_ALLOWED_MOTOR_TEMPERATURE )&& (TempCounter>0))
    {
        TempCounter--;
    }

    // temp decrease
    else if ((Motor_Temperature <= MAX_ALLOWED_MOTOR_TEMPERATURE) && (Motor_Temperature > 0)) 
    {
        Motor_Temperature -= TempertureDecreaseDist(gen);  // Decrease temp randomly
        if (Motor_Temperature < NORAML_OPERATING_MOTOR_TEMPERATURE) 
        {
            Motor_Temperature = NORAML_OPERATING_MOTOR_TEMPERATURE;  // Ensure temp doesn't go below 0
        }
    }
    return Motor_Temperature;
}

float Simulate_Sensor::Simulate_BatterySensor(void) 
{
    static int counter = 3;
    // Set up random number generation
    std::random_device rd;   // Seed source
    std::mt19937 gen(rd());  // Mersenne Twister engine
    std::uniform_real_distribution<float> BatteryVoltageDecreaseDist(0.05, 0.1);

    static float Battery_Voltage = 12.9f;  // Initial speed
    // Battery_Voltage increase
    // Hold at max Battery_Voltage
    if(counter>0)
    {
        counter--;
    }

    // Speed decrease
    else if (Battery_Voltage <= MAX_VOLTAGE) 
    {
        Battery_Voltage -= BatteryVoltageDecreaseDist(gen);  // Decrease speed randomly
        if (Battery_Voltage < MIN_VOLTAGE) 
        {
            Battery_Voltage = MIN_VOLTAGE;  // Ensure speed doesn't go below 0
        }
        counter = 2;

    }
    return Battery_Voltage;
}

bool FuelFlag = false;


int Simulate_Sensor::Simulate_FuelSensor(void) 
{
    static int FuelCounter = 3;

    std::random_device rd; 
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> FuelIncreaseDis(1,3);
    std::uniform_real_distribution<float> FuelDecreaseDis(1,3);

    static int Fuel_Tank = 37;  // Max Tank Start 
    // fuel decrease
    if ((Fuel_Tank <= MAX_FUEL) && (FuelFlag == false)) // 4 as now we will refuel 
    {
        Fuel_Tank -= FuelDecreaseDis(gen);  // Decrease fuel randomly
        if (Fuel_Tank < 4) 
        {
            Fuel_Tank = 4;  // Ensure fuel doesn't go below 4
            FuelFlag = true;
        }
    }

    // Hold at MAX_FUEL
    else if((Fuel_Tank >= MAX_FUEL )&& (FuelCounter>0))
    {
        FuelCounter--;
    }
    // fuel increase
    else if ((Fuel_Tank < MAX_FUEL)  && (FuelFlag == true))
    {
        Fuel_Tank += FuelIncreaseDis(gen);  // Increase fuel randomly
        if (Fuel_Tank > MAX_FUEL)
        {
            Fuel_Tank = MAX_FUEL;
        }
    }
    return Fuel_Tank;
}
bool RadarFlag = false;

float Simulate_Sensor::Simulate_RadarSensor(void) 
{
    static int RadarCounter = 3;
    // Set up random number generation
    std::random_device rd;   // Seed source
    std::mt19937 gen(rd());  // Mersenne Twister engine

    std::uniform_real_distribution<float> RadarIncreaseDist(1, 5);
    std::uniform_real_distribution<float> RadarDecreaseDist(1, 5);

    static float RadarDistance = 155;  // Initial Distance in m 
    // Battery_Voltage increase
    if (RadarDistance <= MAX_RADAR_DISTANCE) 
    {
        RadarDistance -= RadarDecreaseDist(gen);  // Decrease Distance randomly
        if (RadarDistance < MIN_RADAR_DISTANCE) 
        {
            RadarDistance = MIN_RADAR_DISTANCE;  
            TempFlag = true;
        }
    }
    // Hold at max RadarDistance
    else if(RadarCounter>0)
    {
        RadarCounter--;
    }

    // Radar Distance decrease
    else if ((RadarDistance >= MIN_RADAR_DISTANCE)  && (TempFlag == true))
    {
        RadarDistance += RadarIncreaseDist(gen);  // Decrease speed randomly
        if (RadarDistance  > MAX_RADAR_DISTANCE) 
        {
            RadarDistance = MAX_RADAR_DISTANCE;  // Ensure speed doesn't go below 0
        }
    }
    return RadarDistance;
}

// Scenario 1 : Move in const speed and obstacle found (1 - speed down  - 2 - Stop)



float Simulate_Sensor::Simulate_Scenario_1(float &speed) 
{
    static int counter=5;
    // Set up random number generation
    std::random_device rd;   // Seed source
    std::mt19937 gen(rd());  // Mersenne Twister engine
    std::uniform_int_distribution<> speedIncreaseDist(1, 10);  // temp increase by 1-10 units
    // Speed increase
    if ((speed < 90) &&(Simulate_Sensor::Obstacle_SpeedFlag_GDB == false)) // if there is obstaaacle we don't want to increas speed 
    {
        speed += speedIncreaseDist(gen);  // Increase speed randomly
        if (speed > 90)
        {
            std::cout << "Speed is 90" <<std::endl;
            speed = 90;  // Cap at 90 km/h
        }
    }
    if((counter > 0) && (speed == 90))
    {
        counter--;
    }
    else if((counter == 0) && (speed == 90))
    {
        Simulate_Sensor::Obstacle_SpeedFlag_GDB = true;
        std::cout <<"entered: "<< Simulate_Sensor::Obstacle_SpeedFlag_GDB << std::endl;
    }


    std::cout << "Current speed: " << speed << " km/h" << std::endl;


    return speed;
}

bool &Simulate_Sensor::Get_ObstacleFlag(void)
{
    return Obstacle_SpeedFlag_GDB;
}
