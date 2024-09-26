#ifndef SESNSOR
#define SESNSOR

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

template <typename T>
class Sensor
{
        public:
            virtual T Get_SensorData(void)=0; 
            virtual void Set_SensorData(T value)=0; 

            virtual ~Sensor(){}

};




#endif