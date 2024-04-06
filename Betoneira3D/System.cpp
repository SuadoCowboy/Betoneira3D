#include "System.h"

#include <filesystem>

using namespace Betoneira;

bool System::pathExists(const std::string& name) {
    return std::filesystem::exists(name);
}

bool System::isDirectory(const std::string& path)
{
    return std::filesystem::is_directory(path);
}

bool System::isFile(const std::string& path)
{
    return std::filesystem::is_regular_file(path);
}

std::string System::baseName(const std::string& _path)
{
    std::filesystem::path p{ _path };
    return p.stem().string();
}

std::string System::fileExtension(const std::string& _path)
{
    std::filesystem::path p{ _path };
    return p.extension().string().substr(1);
}