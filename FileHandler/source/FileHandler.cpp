#include "FileHandler.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

void FileHandler::SaveFile(std::map<std::string, std::string> &myMap, const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        // Write the header with WiFi name and encrypted password
        file << "WiFi Name:     " ;
        file << "Encrypted Password: " << "\n\n"; // Extra newline for spacing
        
        for (const auto& pair : myMap) 
        {
            std::string encrypted_password = cryptoHandler.encrypt(pair.second);
            file << pair.first << ",     " << encrypted_password << "\n";
        }
        file.close();
        std::cout << "Map saved successfully to " << filename << std::endl;
    } 
    else 
    {
        std::cerr << "Could not open file for writing." << std::endl;
    }
}
