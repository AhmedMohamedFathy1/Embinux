
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

// template <typename... Args>
// inline void VehicleLogger::logData(Args... args)
// {
//     if (logfile.is_open())
//     {
//         auto now = std::chrono::system_clock::now();
//         std::time_t current_time = std::chrono::system_clock::to_time_t(now);
//         logfile << "Timestamp: " << std::put_time(std::localtime(&current_time), "%Y-%m-%d %H:%M:%S") << std::endl;

//         // Create a string stream to format the arguments
//         std::ostringstream oss;
//         formatArguments(oss, args...);
//         logfile << oss.str() << std::endl; // Log formatted arguments

//         std::cout << "Data logged successfully.\n";
//     }
//     else 
//     {
//         std::cerr << "Unable to log data, file is not open.\n";
//     }
// }

// template <typename T>
// void VehicleLogger::formatArguments(std::ostringstream &oss, T arg)
// {
//     oss << arg; // Base case for recursion
// }

// template <typename T, typename... Args>
// void VehicleLogger::formatArguments(std::ostringstream &oss, T arg, Args... args)
// {
//     oss << arg << ", "; // Format current argument
//     formatArguments(oss, args...); // Recursive call for remaining arguments
// }
