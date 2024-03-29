#pragma once

#include <string>

namespace Betoneira::System
{
    bool pathExists(std::string path);
    bool isDirectory(std::string path);
    bool isFile(std::string path);
    std::string baseName(std::string path);
    std::string fileExtension(std::string path);
}