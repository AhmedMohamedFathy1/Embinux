#ifndef __FILEHANDLER__H__
#define __FILEHANDLER__H__

#include <map>
#include <string>

class FileHandler
{
    private:

    public:
        void SaveFile(std::map<std::string, std::string>& myMap, const std::string& filename);
};

#endif  //!__FILEHANDLER__H__