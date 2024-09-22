
#include <random>
#include  <iostream>

#include "../header/SensorSimulators.hpp"

float Simulate_Sensor::Simulate_SpeedSensor(int maxSpeed, int holdTime) 
{
    static int counter = holdTime;
    // Set up random number generation
    std::random_device rd;   // Seed source
    std::mt19937 gen(rd());  // Mersenne Twister engine
    std::uniform_int_distribution<> speedIncreaseDist(1, 20);  // Speed increase by 1-10 units
    std::uniform_int_distribution<> speedDecreaseDist(1, 10);  // Speed decrease by 1-10 units

    static float speed = 0;  // Initial speed

    // Speed increase
    // std::cout << "Increasing speed..." << std::endl;
    if (speed < maxSpeed) 
    {
        speed += speedIncreaseDist(gen);  // Increase speed randomly
        if (speed > maxSpeed) 
        {
            speed = maxSpeed;  // Cap at max speed
        }
        // std::cout << "Speed: " << speed << " km/h" << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Wait for 0.5 seconds
    }

    // Hold at max speed
    if((speed >= maxSpeed )&& (counter>0))
    {
        counter--;
        std::cout << "Holding speed..." << std::endl;
        std::cout << "counter: " << counter << std::endl;
       // std::this_thread::sleep_for(std::chrono::seconds(1));  // Hold for 1 second
    }

    // Speed decrease
    // std::cout << "Decreasing speed..." << std::endl;
    else if ((speed >= maxSpeed) && (speed > 0)) 
    {
        speed -= speedDecreaseDist(gen);  // Decrease speed randomly
        if (speed < 0) 
        {
            speed = 0;  // Ensure speed doesn't go below 0
        }
        // std::cout << "Speed: " << speed << " km/h" << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Wait for 0.5 seconds
    }
    return speed;
}