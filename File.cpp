#include "File.h"
#include "FileSystemEntity.h"
#include <iostream>

//Constrctor
File::File(const std::string& fileName, size_t fileSize, const std::string& fileTimeStamp):FileSystemEntity(std::move(fileName), std::move(fileTimeStamp)), fileSize(fileSize) {}


void File::Display() const {
	std::cout << GetCreationDate() << "\t" << GetFileSize() << " bytes\t" << GetName() << std::endl;
}



