#include "FileHandler.hpp"

#include <iostream>
#include <fstream>
#include <sstream>


void FileHandler::SaveFile(std::map<std::string, std::string> &myMap, const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        for (const auto& pair : myMap) 
        {
            file << pair.first << "," << pair.second << "\n";
        }
        file.close();
        std::cout << "Map saved successfully to " << filename << std::endl;
    } 
    else 
    {
        std::cerr << "Could not open file for writing." << std::endl;
    }
}
