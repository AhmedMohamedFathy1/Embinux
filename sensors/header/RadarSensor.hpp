#ifndef RADAR_SESNSOR
#define RADAR_SESNSOR

#include "../header/Sensor.hpp"
#include "../header/SensorSimulators.hpp"

class Radar_Sensor : public Sensor<float>
{
    private: 
        float Radar_Distance_LF_U32_;
        Simulate_Sensor *simulate_sensor;
    protected:
        bool ObstacleGlag_PBD = false;

    public:
       
        float Get_SensorData(void) override; 

        void Set_SensorData(float value) override;

};

#endif