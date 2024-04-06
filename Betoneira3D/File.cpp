#include "File.h"

#include "System.h"

#include <iostream>
#include <sstream>

Betoneira::FileSystem::FileHandler::FileHandler(std::string _path) : path(_path) {};

Betoneira::FileSystem::FileHandler::FileHandler() : path("") {}
Betoneira::FileSystem::FileHandler::~FileHandler() {}

bool Betoneira::FileSystem::FileHandler::isOpen()
{
    return file.is_open();
}

Betoneira::Status Betoneira::FileSystem::FileHandler::open(std::ios_base::openmode mode)
{
    close();

    // creates file if it does not exists
    if (!System::pathExists(path))
    {
        if (mode & Betoneira::FileSystem::FILE_WRITE)
        {
            std::ofstream f(path);
            f << "";
            f.close();
        }
        else {
            if (!System::isFile(path))
                return Betoneira::Status::NOT_A_FILE;
            return Betoneira::Status::DOES_NOT_EXIST;
        }
    }

    file.open(path.c_str(), mode);

    return isOpen() ? Betoneira::Status::OK : Betoneira::Status::SOMETHING_WRONG;
}

Betoneira::Status Betoneira::FileSystem::FileHandler::open(std::string newPath, std::ios_base::openmode mode)
{
    path = newPath;
    return open(mode);
}

Betoneira::Status Betoneira::FileSystem::FileHandler::close()
{
    file.close();
    return !isOpen() ? Betoneira::Status::OK : Betoneira::Status::SOMETHING_WRONG;
}

Betoneira::Status Betoneira::FileSystem::FileHandler::write(const char* content)
{
    if (!isOpen())
        return Betoneira::Status::FILE_CLOSED;

    file << content;

    return Betoneira::Status::OK;
}

Betoneira::Status Betoneira::FileSystem::FileHandler::read(std::string& out)
{
    if (!isOpen())
    {
        return Betoneira::Status::FILE_CLOSED;
    }

    std::stringstream buf;
    buf << file.rdbuf();

    out = buf.str();

    return Betoneira::Status::OK;
}

std::string Betoneira::FileSystem::FileHandler::getPath()
{
    return path;
}

Betoneira::FileSystem::FileHandler& Betoneira::FileSystem::FileHandler::operator<<(const char* content)
{
    write(content);
    return *this;
}

Betoneira::Status Betoneira::FileSystem::getFileContent(const std::string& path, std::string& content, std::ios_base::openmode mode)
{
    if (!Betoneira::System::isDirectory(path))
        return Betoneira::Status::DOES_NOT_EXIST;

    if (!Betoneira::System::isFile(path))
        return Betoneira::Status::NOT_A_FILE;

    Betoneira::FileSystem::FileHandler file{ path };
    
    file.open(mode);

    Betoneira::Status readStatus = file.read(content);

    file.close();

    return readStatus;
}