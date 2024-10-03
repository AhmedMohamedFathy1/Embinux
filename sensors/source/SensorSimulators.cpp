
#include <random>
#include  <iostream>

#include "SensorSimulators.hpp"
#include "diagnostics.hpp"
#include "SpeedSensor.hpp"
#include "AdpativeCruiseControl.hpp"
#include "Logger.hpp"
#include "QtApp.hpp"

QtFlags &SS_Qt_Flags = VehicleApp::Get_Qt_FlagInstance();


Diagnostics diagnostics; 

Speed_Sensor & speed_Sensor = Speed_Sensor::Get_SpeedSensor_Instance();

Scenarios_Flags &scenarios_Flags = Simulate_Sensor::Get_Scenarios_Flags_Instance();

ACC_ConditionsFlags Diagnostics_conditionsFlags = AdaptiveCruiseControl::Get_ACC_FlagInstance();

Sensors_data_t& SS_sensors_data = Update_Sensors::GetSensorData();

ScenarioStates State = ScenarioStates::Scenario1;

VehicleLogger& SS_logger = VehicleLogger::Logger_GetInstance("vehicle_log.txt");


 /* Vehcile Speed */
#define VEHICLE_MAX_SPEED 180  

/* Motor Temperature  Voltage*/

#define MAX_ALLOWED_MOTOR_TEMPERATURE 130 // celisus // Max allowed is 110,  i let space to test over heating 
#define NORAML_OPERATING_MOTOR_TEMPERATURE 105 // celisus // Max allowed is 110,  i let space to test over heating 

/* Battery Voltage*/
#define MIN_VOLTAGE 11.5f  // Min Battery Voltage 
#define MAX_VOLTAGE 13.0f  //Max Battery Voltage 

/* Battery Voltage*/
#define MIN_FUEl  6  // Min Fuel to fire Alaram
#define MAX_FUEL  37  //Max Fuel Tank capacity 

/* Radar Distance in meter*/
#define MIN_RADAR_DISTANCE  25  // Min Fuel to fire Alaram
#define MAX_RADAR_DISTANCE  350  // Max Fuel to fire Alaram

#define SS_SPEED_DOWN_DECELERATION 7   // Average Decelartion on normal force braking is from 7-8
#define SS_STOPPING_DECELERATION   9  // Average Decelartion on high force braking is from 9-10

#define SS_TOTAL_STOP 0 
#define SS_SLOW_DOWN_SPEED 50 

#define HOLD_TIME 5

bool InitFlag_GDB = false;


/**
 * @brief Decelerate the speed according to full stop or slow down flags
 * 
 * @param speed 
 * @param Deceleration 
 * @return float 
 */

float Simulate_Sensor::decelerate(float &speed,const int &Deceleration)
{ 
    if(scenarios_Flags.Scenario_Speed_Sesnor_Flag_LDB == true)
    {
        const int timeStep = 1; // Time step for simulation (seconds)
        while (speed > SS_TOTAL_STOP)
        {
            speed -= Deceleration * timeStep;
        //  ACC_speed_Sensor.Set_SensorData(speed); // update new value in the class 

            if(Deceleration == SS_SPEED_DOWN_DECELERATION)
            {
                if(speed < 50)
                {
                    speed = 50;
                    break;
                }
                SS_logger.logData("Decelerating...");
                std::cout << "Decelerating..." << std::endl;
                return speed;
            }

            else if(Deceleration == SS_STOPPING_DECELERATION)
            {
                if(static_cast<int>(speed) <= SS_TOTAL_STOP)
                {
                    speed = SS_TOTAL_STOP;
                    SS_logger.logData("Car Stoped");
                    std::cout << "Car Stoped" << std::endl;
                    if (diagnostics.diagnostics_Flags.ObstacleFound_Is_High_GDB == true) 
                    {
                        InitFlag_GDB = false;
                        State = ScenarioStates::Scenario2;  
                    } 
                    else if(diagnostics.diagnostics_Flags.Motor_Temperature_Is_High_GDB == true) 
                    {
                        InitFlag_GDB = false;
                        State = ScenarioStates::Scenario3;  
                    }
                    break;
                }
                SS_logger.logData("Stopping...");

                std::cout << "Stopping..." << std::endl;
                return speed;

            }
            else
            {
            break;
            }
        }
    }
    return speed;

}

float Vehcile_speed_GF_U32 = 0;  // Initial speed
/**
 * @brief Simulate spped sensor by increasing or decreasing value when flag is set 
 * 
 * @return float 
 */

float Simulate_Sensor::Simulate_SpeedSensor(void) 
{
   if(scenarios_Flags.Scenario_Speed_Sesnor_Flag_LDB == true)
   {
        // Set up random number generation
        std::random_device rd;   // Seed source
        std::mt19937 gen(rd());  // Mersenne Twister engine
        std::uniform_int_distribution<> speedIncreaseDist(1, 15);  // Speed increase by 1-10 units
        std::uniform_int_distribution<> speedDecreaseDist(1, 15);  // Speed decrease by 1-10 units

        if((diagnostics.diagnostics_Flags.ObstacleFound_Is_High_GDB == true) || (diagnostics.diagnostics_Flags.Motor_Temperature_Is_High_GDB == true))
        {
            if(Diagnostics_conditionsFlags.ACC_Slow_Down_Flag == true)
            {
                Vehcile_speed_GF_U32 = decelerate(SS_sensors_data.SpeedSensor_data,SS_SPEED_DOWN_DECELERATION);
            }
            else if(Diagnostics_conditionsFlags.ACC_Stopping_Flag == true)
            {
                Vehcile_speed_GF_U32 = decelerate(SS_sensors_data.SpeedSensor_data,SS_STOPPING_DECELERATION);
            }
        }
        if ((Vehcile_speed_GF_U32 < VEHICLE_MAX_SPEED)  && (diagnostics.diagnostics_Flags.Vehcile_Stop_Speed_Up_Is_High_GDB == false))
        {
            Vehcile_speed_GF_U32 += speedIncreaseDist(gen);  // Increase speed randomly
            if (Vehcile_speed_GF_U32 > VEHICLE_MAX_SPEED)
            {
                Vehcile_speed_GF_U32 = VEHICLE_MAX_SPEED;  // Cap at max speed
            }
        }
        else
        {

        }
   } 
   return Vehcile_speed_GF_U32; 
}

/**
 * @brief Simulate Radar sensor by decreasing value when flag is set 
 * 
 * @return float 
 */
float Simulate_Sensor::Simulate_RadarSensor(void) 
{        
    static float RadarDistance = 100;  // Initial Distance in m 

    if(scenarios_Flags.Scenario_Radar_Sesnor_Flag_LDB == true)
    {
        static int RadarCounter = 3;
        // Set up random number generation
        std::random_device rd;   // Seed source
        std::mt19937 gen(rd());  // Mersenne Twister engine

        std::uniform_real_distribution<float> RadarIncreaseDist(1, 5);
        std::uniform_real_distribution<float> RadarDecreaseDist(1, 5);

        // Radar increase
        if (RadarDistance <= MAX_RADAR_DISTANCE) 
        {
            RadarDistance -= RadarDecreaseDist(gen);  // Decrease Distance randomly
            if (RadarDistance < MIN_RADAR_DISTANCE) 
            {
                RadarDistance = MIN_RADAR_DISTANCE;  
            }
        }
        // Hold at max RadarDistance
        else if(RadarCounter>0)
        {
            RadarCounter--;
        }

        // Radar Distance decrease
        else if (RadarDistance >= MIN_RADAR_DISTANCE)
        {
            RadarDistance += RadarIncreaseDist(gen);  // Decrease speed randomly
            if (RadarDistance  > MAX_RADAR_DISTANCE) 
            {
                RadarDistance = MAX_RADAR_DISTANCE;  // Ensure speed doesn't go below 0
            }
        }
    }
    return RadarDistance;
}
/**
 * @brief Simulate Temperature sensor by increasing value when flag is set 
 * 
 * @return int 
 */

int Simulate_Sensor::Simulate_TemperatureSensor(void) 
{
    static float Motor_Temperature = 70;  // Initial temp

    if(scenarios_Flags.Scenario_Temperature_Sesnor_Flag_LDB == true)
    {
        // Set up random number generation
        std::random_device rd;   // Seed source
        std::mt19937 gen(rd());  // Mersenne Twister engine
        std::uniform_int_distribution<> TempertureIncreaseDist(1, 10);  // temp increase by 1-10 units
        std::uniform_int_distribution<> TempertureDecreaseDist(1, 10);  // temp decrease by 1-10 units

        if(diagnostics.diagnostics_Flags.ObstacleFound_Is_High_GDB == true)
        {
            if(Diagnostics_conditionsFlags.ACC_Stopping_Flag == true)
            {
                Vehcile_speed_GF_U32 = decelerate(SS_sensors_data.SpeedSensor_data,SS_STOPPING_DECELERATION);
            }
        }
        // temp increase
        if ((Motor_Temperature < MAX_ALLOWED_MOTOR_TEMPERATURE) && (diagnostics.diagnostics_Flags.Motor_Temperature_Is_High_GDB == false))
        {
            Motor_Temperature += TempertureIncreaseDist(gen);  // Increase temp randomly
            if (Motor_Temperature > MAX_ALLOWED_MOTOR_TEMPERATURE)
            {
                Motor_Temperature = MAX_ALLOWED_MOTOR_TEMPERATURE;
            }
        }
    }
    return Motor_Temperature;

}
/**
 * @brief Simulate battery sensor by decreasding value when flag is set 
 * 
 * @return float 
 */
float Simulate_Sensor::Simulate_BatterySensor(void) 
{
    static float Battery_Voltage = 12.9f;  // Initial speed

    if(scenarios_Flags.Scenario_Battery_Sesnor_Flag_LDB == true)
    {
        static int counter = 4;
        // Set up random number generation
        std::random_device rd;   // Seed source
        std::mt19937 gen(rd());  // Mersenne Twister engine
        std::uniform_real_distribution<float> BatteryVoltageDecreaseDist(0.05, 0.1);

        // Voltage decrease
        if (Battery_Voltage <= MAX_VOLTAGE) 
        {
            Battery_Voltage -= BatteryVoltageDecreaseDist(gen);  // Decrease speed randomly
            if ((Battery_Voltage < MIN_VOLTAGE) && (counter > 0))
            {
                Battery_Voltage = MIN_VOLTAGE;  // Ensure Voltage doesn't go below 11.5f
                counter--;
            }
        }
        if(counter == 0)
        {
            InitFlag_GDB = false;
            State = ScenarioStates::Scenario5;  
        }
    }
    return Battery_Voltage;

}

bool FuelFlag = false;

/**
 * @brief Simulate fuel sensor by decreasding value when flag is set 
 * 
 * @return int 
 */
int Simulate_Sensor::Simulate_FuelSensor(void) 
{
   static int Fuel_Tank = 37;  // Max Tank Start 

   if(scenarios_Flags.Scenario_Fuel_Sesnor_Flag_LDB == true)
   {
        static int FuelCounter = 3;

        std::random_device rd; 
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> FuelDecreaseDis(1,5);

        // fuel decrease
        if ((Fuel_Tank <= MAX_FUEL) && (FuelFlag == false)) // 4 as now we will refuel 
        {
            Fuel_Tank -= FuelDecreaseDis(gen);  // Decrease fuel randomly
            if (Fuel_Tank < MIN_FUEl) 
            {
                Fuel_Tank = MIN_FUEl;  // Ensure fuel doesn't go below 4
                FuelFlag = true;
            }
        }

        // Hold at MAX_FUEL
        else if((Fuel_Tank <= MIN_FUEl )&& (FuelCounter>0))
        {
            FuelCounter--;
        }
        if(FuelCounter == 0 )
        {
            InitFlag_GDB = false;
            State = ScenarioStates::Scenario4;  
        }
   }
    return Fuel_Tank;

}


/**
 * @brief : Move in const speed and obstacle found (1 - speed down  - 2 - Stop)
 * 
 */
void Simulate_Sensor::Simulate_Scenario_1() 
{
    scenarios_Flags.Scenario_Battery_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Fuel_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Temperature_Sesnor_Flag_LDB = false;

    scenarios_Flags.Scenario_Speed_Sesnor_Flag_LDB = true;
    scenarios_Flags.Scenario_Radar_Sesnor_Flag_LDB = true;
}

/**
 * @brief:  increase speed to 120 km/h and while and then increase motor temperature above normal so car must stop
 * 
 */

void Simulate_Sensor::Simulate_Scenario_2(void)
{
    scenarios_Flags.Scenario_Battery_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Fuel_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Radar_Sesnor_Flag_LDB = false;

    scenarios_Flags.Scenario_Temperature_Sesnor_Flag_LDB = true;
    scenarios_Flags.Scenario_Speed_Sesnor_Flag_LDB = true;
}

/**
 * @brief  Run Sceanrio to check on Low Fuel
 * 
 */
void Simulate_Sensor::Simulate_Scenario_3(void)
{
    scenarios_Flags.Scenario_Battery_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Radar_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Temperature_Sesnor_Flag_LDB = false;

    scenarios_Flags.Scenario_Fuel_Sesnor_Flag_LDB = true;
    scenarios_Flags.Scenario_Speed_Sesnor_Flag_LDB = true;
}

/**
 * @brief  Run Sceanrio to check on Low Battery
 * 
 */
void Simulate_Sensor::Simulate_Scenario_4(void)
{
    scenarios_Flags.Scenario_Fuel_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Radar_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Temperature_Sesnor_Flag_LDB = false;

    scenarios_Flags.Scenario_Battery_Sesnor_Flag_LDB = true;
    scenarios_Flags.Scenario_Speed_Sesnor_Flag_LDB = true;
}

/**
 * @brief Run Sceanrio to check on excessive speed 
 * 
 */
void Simulate_Sensor::Simulate_Scenario_5(void)
{
    scenarios_Flags.Scenario_Fuel_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Radar_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Temperature_Sesnor_Flag_LDB = false;
    scenarios_Flags.Scenario_Battery_Sesnor_Flag_LDB = false;

    scenarios_Flags.Scenario_Speed_Sesnor_Flag_LDB = true;
}

/**
 * @brief Init System inly after scenario finished 
 * 
 */
void Simulate_Sensor::Scenario_Init_state(void)
{
    // std::cout << "check system Init " << std::endl;

    if (InitFlag_GDB == false)
    {
        switch (State)
        {
        case ScenarioStates::Scenario1:
            SS_logger.logData("***************************  Scenario 1 ***************************");
            std::cout << " ***************************  Scenario 1 ***************************" << std::endl;
            break;

        case ScenarioStates::Scenario2:
            SS_logger.logData("***************************  Scenario 2 ***************************");

            std::cout << " ***************************  Scenario 2 ***************************" << std::endl;
            break;

        case ScenarioStates::Scenario3:
            SS_logger.logData("***************************  Scenario 3 ***************************");

            std::cout << " ***************************  Scenario 3 ***************************" << std::endl;
            break;

        case ScenarioStates::Scenario4:
            SS_logger.logData("***************************  Scenario 4 ***************************");

            std::cout << " ***************************  Scenario 4 ***************************" << std::endl;
            break;
        case ScenarioStates::Scenario5:
            SS_logger.logData("***************************  Scenario 5 ***************************");

            std::cout << " ***************************  Scenario 5 ***************************" << std::endl;
            break;
        default:
            SS_logger.logData(" ***************************  Simulation Finished ***************************");

            std::cout << " ***************************  Simulation Finished ***************************" << std::endl;
            break;
        }
        Vehcile_speed_GF_U32 = 0;
        diagnostics.diagnostics_Flags.ObstacleFound_Is_High_GDB = false;
        diagnostics.diagnostics_Flags.Motor_Temperature_Is_High_GDB = false;
        diagnostics.diagnostics_Flags.Vehcile_Stop_Speed_Up_Is_High_GDB = false;

        Diagnostics_conditionsFlags.ACC_Slow_Down_Flag = false;
        Diagnostics_conditionsFlags.ACC_Stopping_Flag = false;

        scenarios_Flags.Scenario_Battery_Sesnor_Flag_LDB = false;
        scenarios_Flags.Scenario_Fuel_Sesnor_Flag_LDB = false;
        scenarios_Flags.Scenario_Radar_Sesnor_Flag_LDB = false;
        scenarios_Flags.Scenario_Temperature_Sesnor_Flag_LDB = false;
        scenarios_Flags.Scenario_Speed_Sesnor_Flag_LDB = false;
        
        SS_Qt_Flags.Qt_Obstacle_Flag_GDB = false;
        SS_Qt_Flags.Qt_Temperature_Flag_GDB = false;
        SS_Qt_Flags.Qt_Fuel_Flag_GDB = false;
        SS_Qt_Flags.Qt_Battery_Flag_GDB = false;
        SS_Qt_Flags.Qt_speed_Flag_GDB = false;

        InitFlag_GDB = true;
    }
}

/**
 * @brief Control Which Scenario to start 
 * 
 */

void Simulate_Sensor::Scenario_Handler(void)
{
    Simulate_Sensor::Scenario_Init_state();
    switch (State)
    {
    case ScenarioStates::Scenario1:
        Simulate_Sensor::Simulate_Scenario_1();
        break;

    case ScenarioStates::Scenario2:
        Simulate_Sensor::Simulate_Scenario_2();
    /* code */
    break;

    case ScenarioStates::Scenario3:
        Simulate_Sensor::Simulate_Scenario_3();
        break;

    case ScenarioStates::Scenario4:
        Simulate_Sensor::Simulate_Scenario_4();
        break;

    case ScenarioStates::Scenario5:
        Simulate_Sensor::Simulate_Scenario_5();
        break;

    default:
        break;
    }
}

/**
 * @brief  singleton design by only return one instance fromthe struct all over the project

 * 
 * @return Scenarios_Flags& 
 */
Scenarios_Flags &Simulate_Sensor::Get_Scenarios_Flags_Instance(void)
{
    static Scenarios_Flags scenarios_Flags;
    return scenarios_Flags;
}