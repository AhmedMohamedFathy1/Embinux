
#include <random>
#include  <iostream>

#include "../header/SensorSimulators.hpp"

#define VEHICLE_MAX_SPEED 180  

bool SpeedFlag = true;

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
        // std::this_thread::sleep_for(std::chrono::seconds(1));  // Hold for 1 second
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