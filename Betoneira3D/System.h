#pragma once

#include <string>

namespace Betoneira::System
{
    bool pathExists(const std::string& path);
    bool isDirectory(const std::string& path);
    bool isFile(const std::string& path);
    std::string baseName(const std::string& path);
    std::string fileExtension(const std::string& path);
}