
#include <random>
#include  <iostream>

#include "SensorSimulators.hpp"
#include "diagnostics.hpp"
#include "SpeedSensor.hpp"

Diagnostics diagnostics; 
Speed_Sensor & speed_Sensor = Speed_Sensor::Get_SpeedSensor_Instance();

Scenarios_Flags &scenarios_Flags = Simulate_Sensor::Get_Scenarios_Flags_Instance();

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

#define SPEED_DOWN_DECELERATION 7   // Average Decelartion on normal force braking is from 7-8
#define STOPPING_DECELERATION   9  // Average Decelartion on high force braking is from 9-10

#define TOTAL_STOP 0 
#define SLOW_DOWN_SPEED 50 

#define HOLD_TIME 5

bool TempFlag = true;



void Simulate_Sensor::decelerate(float &speed,const int &Deceleration)
{ 
    const int timeStep = 1; // Time step for simulation (seconds)
    while (speed > TOTAL_STOP)
    {
        speed -= Deceleration * timeStep ;
      //  ACC_speed_Sensor.Set_SensorData(speed); // update new value in the class 

        if(Deceleration == SPEED_DOWN_DECELERATION)
        {
            if(speed < 50)
            {
            speed = 50;
            break;
            }
            std::cout << "Decelerating... Current speed: " << speed << " km/h" << std::endl;
        }

        else if(Deceleration == STOPPING_DECELERATION)
        {
            if(speed < TOTAL_STOP)
            {
            speed = TOTAL_STOP;
            std::cout << "Car Stopped" << std::endl;
            break;
            }
            std::cout << "Stopping... Current speed: " << speed << " km/h" << std::endl;
        }
        else
        {
           break;
        }

    }
}

float Vehcile_speed_GF_U32 = 0;  // Initial speed

float Simulate_Sensor::Simulate_SpeedSensor(int maxSpeed, int holdTime) 
{
   if(scenarios_Flags.Scenario_Speed_Sesnor_Flag_LDB == true)
   {
        static int counter = holdTime;
        // Set up random number generation
        std::random_device rd;   // Seed source
        std::mt19937 gen(rd());  // Mersenne Twister engine
        std::uniform_int_distribution<> speedIncreaseDist(1, 20);  // Speed increase by 1-10 units
        std::uniform_int_distribution<> speedDecreaseDist(1, 20);  // Speed decrease by 1-10 units

        // Speed increase
        std::cout << "Flag State: " << diagnostics.diagnostics_Flags.ObstacleFound_Is_High_GDB << std::endl;
        if ((Vehcile_speed_GF_U32 < VEHICLE_MAX_SPEED)  && (diagnostics.diagnostics_Flags.ObstacleFound_Is_High_GDB == false))
        {
            Vehcile_speed_GF_U32 += speedIncreaseDist(gen);  // Increase speed randomly
            if (Vehcile_speed_GF_U32 > VEHICLE_MAX_SPEED)
            {
                Vehcile_speed_GF_U32 = VEHICLE_MAX_SPEED;  // Cap at max speed
            }
            speed_Sensor.Set_SensorData(Vehcile_speed_GF_U32);
        }
        else
        {

        }
   } 
   return Vehcile_speed_GF_U32; // TODO: we need to remove or remove Set_SensorData() 

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
void Simulate_Sensor::Simulate_Scenario_1() 
{
    scenarios_Flags.Scenario_Battery_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Fuel_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Temperature_Sesnor_Flag_LDB = false;

    scenarios_Flags.Scenario_Speed_Sesnor_Flag_LDB = true;
    scenarios_Flags.Scenario_Radar_Sesnor_Flag_LDB = true;
}

/**
 * brief : increase speed to 120 km/h and while and then increase motor temperature above normal so car must stop
 *
 */
// float Simulate_Sensor::Simulate_Scenario_2(float &speed,float &temperature)
// {
//     static int Scenario2_Counter = 5;
//     bool Temperature_Rise_GDB = false;
//     // Set up random number generation
//     std::random_device rd; // Seed source
//     std::mt19937 gen(rd()); // Mersenne Twister engine
//     std::uniform_int_distribution<> speedIncreaseDist(1, 10); // temp increase by 1-10 units
//     // Speed increase
//     if ((speed < 120) &&(Simulate_Sensor::Obstacle_SpeedFlag_GDB == false)) // if there is obstaaacle we don't want to increas speed 
//     {
//         speed += speedIncreaseDist(gen); // Increase speed randomly
//         if (speed > 120)
//         {
//             speed = 120; // Cap at 120 km/h
//         }
//     }

//     if((Scenario2_Counter > 0) && (speed == 120))
//     {
//         Scenario2_Counter--;
//     }
//     else if((Scenario2_Counter == 0) && (speed == 120))
//     {
//           Temperature_Rise_GDB = true;
//     }
//     if(Temperature_Rise_GDB)
//     {
//        temperature = Simulate_Sensor::Simulate_TemperatureSensor();
//     }

//     return temperature;
// }

Scenarios_Flags &Simulate_Sensor::Get_Scenarios_Flags_Instance(void)
{
    static Scenarios_Flags scenarios_Flags;
    return scenarios_Flags;
}