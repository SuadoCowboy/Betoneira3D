#pragma once

#include <fstream>
#include <string>

namespace Betoneira::FileSystem
{
    typedef std::ios_base::openmode openMode;
    static const openMode FILE_BINARY = (openMode)4;
    static const openMode FILE_READ = (openMode)8;
    static const openMode FILE_WRITE = (openMode)16;

    // returns 1 if failed
    bool getFileContent(const std::string& path, std::string& content, openMode mode=FILE_READ);

    class FileHandler
    {
    public:
        FileHandler(std::string path);
        FileHandler();
        ~FileHandler();
        
        // return 1 if error
        bool open(openMode mode);
        
        // return 1 if error
        bool open(std::string path, openMode mode);
        
        // return 1 if open
        inline bool isOpen();
        
        // return 1 if error
        bool close();
        
        std::string getPath();

        // return 1 if error
        virtual bool write(const char* content);

        // if you wrote something to it then close and open again to read the updated file
        std::string read();

        FileHandler& operator<<(const char* content);
    
    private:
        std::fstream file;
        std::string path{};
    };
}