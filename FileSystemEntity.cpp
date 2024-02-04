#include "FileSystemEntity.h"

//operator overloading of <<
std::ostream& operator<<(std::ostream& os, const FileSystemEntity& obj) 
{ 
    os << "Name: " << obj.name << ", Creation Date: " << obj.creationDate;
    return os;
}