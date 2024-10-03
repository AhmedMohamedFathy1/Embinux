
#include <Logger.hpp>
  

VehicleLogger::VehicleLogger(const std::string &filename): logFilename(filename) // Initialize logFilename
{
    logfile.open(logFilename, std::ios::app);
    if (!logfile.is_open()) 
    {
        std::cerr << "Unable to open file for logging.\n";
    }
}

VehicleLogger::~VehicleLogger()
{
    if (logfile.is_open()) 
    {
        logfile.close();
    }
}

VehicleLogger & VehicleLogger::Logger_GetInstance(const std::string& filename)
{
    static VehicleLogger instance(filename); // Create a static instance
    return instance;
}
