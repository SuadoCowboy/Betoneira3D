#pragma once

#include "Status.h"

#include <fstream>
#include <string>

namespace Betoneira::FileSystem
{
    static const std::ios_base::openmode& FILE_WRITE = std::ios::out; // open for writing
    static const std::ios_base::openmode& FILE_READ = std::ios::in; // open for reading
    static const std::ios_base::openmode& FILE_ATE = std::ios::ate; // seek to the end of stream immediately after open
    static const std::ios_base::openmode& FILE_APPEND = std::ios::app; // seek to the end of stream before each write
    static const std::ios_base::openmode& FILE_TRUNC = std::ios::trunc; // discard the contents of the stream when opening
    static const std::ios_base::openmode& FILE_BINARY = std::ios::binary; // open in binary mode

    // returns 1 if failed
    Betoneira::Status getFileContent(const std::string& path, std::string& content, std::ios_base::openmode mode = FILE_READ);

    class FileHandler
    {
    public:
        FileHandler(std::string path);
        FileHandler();
        ~FileHandler();

        Betoneira::Status open(std::ios_base::openmode mode);

        Betoneira::Status open(std::string path, std::ios_base::openmode mode);

        // returns 1 if open
        inline bool isOpen();

        Betoneira::Status close();

        std::string getPath();

        virtual Betoneira::Status write(const char* content);

        // if you wrote something to it, close and open again to read the updated file
        Betoneira::Status read(std::string& out);

        FileHandler& operator<<(const char* content);

    private:
        std::fstream file;
        std::string path{};
    };
}