#ifndef __LOGGER__H__
#define __LOGGER__H__

#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>

class VehicleLogger {

    private:
        std::ofstream logfile;
        std::string logFilename;

        // Deleted copy constructor and assignment operator
        VehicleLogger(const VehicleLogger&) = delete;
        VehicleLogger& operator=(const VehicleLogger&) = delete;

        // Helper function to format the arguments
        template <typename T>
        void formatArguments(std::ostringstream &oss, T arg)
        {
            oss << arg; // Base case for recursion
        }

        template <typename T, typename... Args>
        void formatArguments(std::ostringstream &oss, T arg, Args... args)
        {
            oss << arg << ", "; // Format current argument
            formatArguments(oss, args...); // Recursive call for remaining arguments
        }
    public:
        VehicleLogger(const std::string &filename);

        ~VehicleLogger();

        static VehicleLogger & Logger_GetInstance(const std::string& filename = "vehicle_log.txt");

        // Variadic template function to log data
        template <typename... Args>
        inline void logData(Args... args)
        {
            if (logfile.is_open())
            {
                auto now = std::chrono::system_clock::now();
                std::time_t current_time = std::chrono::system_clock::to_time_t(now);
                logfile << "Timestamp: " << std::put_time(std::localtime(&current_time), "%Y-%m-%d %H:%M:%S") << std::endl;

                std::ostringstream oss;
                formatArguments(oss, args...);
                logfile << oss.str() << std::endl;

                // std::cout << "Data logged successfully.\n";
            }
            else 
            {
                std::cerr << "Unable to log data, file is not open.\n";
            }
        }

};


#endif  //!__LOGGER__H__
