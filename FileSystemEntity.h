#pragma once
#include <iostream>
#include <string>
class FileSystemEntity {     // Virtual class for file and Directory to inherit  from
public:
    virtual void Display() const = 0;  // virtual function to be overidden
    virtual ~FileSystemEntity() {};   
    friend std::ostream& operator<<(std::ostream& os, const FileSystemEntity& obj); // operator overloading for the << operator
    std::string GetName() const { return name; }    // method to be overidden by file and direcotries class             
    void SetName(const std::string& newName) { name = newName; }
    std::string GetCreationDate() const { return creationDate; }

protected:
    FileSystemEntity(const std::string& name, const std::string& creationDate)   //constructor 
        : name(name), creationDate(creationDate) {}

private:
    std::string name;
    std::string creationDate;
};
