#pragma once
#include <iostream>
#include <string>
#include "FileSystemEntity.h"

class File : public FileSystemEntity {
public:
    File(const std::string& fileName, size_t fileSize, const std::string& fileTimeStamp);
    size_t GetFileSize() const { return fileSize; }
    virtual void Display() const override; // inherits and overides virtual function in filesystementity class

private:
    size_t fileSize;
};
