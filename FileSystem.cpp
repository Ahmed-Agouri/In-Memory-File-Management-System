#pragma once    
#include "FileSystem.h"
#include "Directory.h"
#include "iostream"
#include <sstream> 
#include <ctime> 
#include <cstdlib>

FileSystem::FileSystem() {
    rootDirectory = std::make_unique<Directory>("root", "creation_date");
    currentDirectory = rootDirectory.get();



    // Create initial directories and files 
    rootDirectory->AddDirectory("Directory", Directory::GetCurrentDateTime());
    rootDirectory->AddFile("File1.txt", generateRandomFileSize(), Directory::GetCurrentDateTime());
    rootDirectory->AddFile("File21.txt", generateRandomFileSize(), Directory::GetCurrentDateTime());
    rootDirectory->AddFile("MyFile12.txt", generateRandomFileSize(), Directory::GetCurrentDateTime());
    rootDirectory->AddDirectory("Directory1", Directory::GetCurrentDateTime());
    rootDirectory->AddDirectory("Directory2", Directory::GetCurrentDateTime());
}

void FileSystem::ProcessUserInput(const std::string & input) 
{   
    std::istringstream iss(input);
    std::string command;
    iss >> command;

    if (command == "cd") {
        std::string directoryName;
        iss >> directoryName;
        cd(directoryName);
    }
    else if (command == "mkdir") {
        std::string directoryName;
        iss >> directoryName;
        mkdir(directoryName);
    }
    else if (command == "mkfile") {
        std::string fileName;
        size_t fileSize = 0; 
        iss >> fileName >> fileSize;
        mkfile(fileName, fileSize);

    }
    else if (command == "del") {
        std::string name;
        iss >> name;
        del(name);
    }
    else if(command=="Dir")
    {
        Dir();

    }
    else if (command == "sortsize") {
        currentDirectory->SortBySize();
        std::cout << "Directory sorted by size." << std::endl;
    }
    else if (command == "sortname") {
        currentDirectory->SortByName();
        std::cout << "Directory sorted by name." << std::endl;
    }
    else if (command == "exit") {
        exit();
    }
    else {
        std::cerr << "Unknown command: " << command << std::endl;
    }
}


// creates Random number between 100 and 1000 to be used for file sizes
size_t FileSystem::generateRandomFileSize()
{
    return 100 + (rand() % 901);
}



//Uses method in Directory class to check if directory class exists
bool FileSystem::CheckIfDirectoryExists(const std::string& directoryName) const
{
    return currentDirectory->hasSubdirectory(directoryName);
}


void FileSystem::cd(const std::string& directoryName) 
{
    if (directoryName == "..") {
        // Move back up to the parent directory,
        if (currentDirectory != rootDirectory.get()) {
            currentDirectory = currentDirectory->getParentDirectory();
            std::cout << "Moved back to previous directory \n" ;
        }
    }
    else {
        //checks for subdirectory using method desgined in directory class
        if (currentDirectory->hasSubdirectory(directoryName)) {
            
            currentDirectory = currentDirectory->getSubdirectory(directoryName);
           
            std::cout << "Changed to directory: " << *currentDirectory << std::endl;

        }
        else {
            std::cerr << "Directory '" << directoryName << "' does not exist." << std::endl;
        }
    }

}

void FileSystem::Dir()
{
    // checks if directory user asked for exists or not
    if (currentDirectory == nullptr) {
        std::cerr << "No current directory selected." << std::endl;
        return;
    }


    std::cout << "Contents of directory \"" << currentDirectory->GetName() << "\":" << std::endl;
    
    //lists directory contents
    currentDirectory->ListContents();
}

void FileSystem::mkdir(const std::string& directoryName)
{
    //checks if directory user trying to create already exists or not
    if (currentDirectory->hasSubdirectory(directoryName)) {
        std::cerr << "Directory '" << directoryName << "' already exists in the current directory." << std::endl;
        return;
    }
    std::string directoryTimeStamp = Directory::GetCurrentDateTime();

    currentDirectory->AddDirectory(directoryName, directoryTimeStamp);
    std::cout << *currentDirectory->getSubdirectory(directoryName) << " created successfully.\n";
}

void FileSystem::mkfile(const std::string& fileName, size_t fileSize) 
{
   
    if (fileSize == 0) {
        fileSize = generateRandomFileSize(); // Generate a random size if not specified i.e in the main.cpp files have set sizes
    }

    //checks if file exists
    if (currentDirectory->hasFile(fileName)) {
        std::cerr << "File '" << fileName << "' already exists in the current directory." << std::endl;
        return;
    }    
    std::string CreationDate = Directory::GetCurrentDateTime();

    currentDirectory->AddFile(fileName, fileSize, CreationDate);
    std::cout << fileName << " Created Sucessfully \n" ;
}


void FileSystem::del(const std::string& name)
{
    // deletes direcotry or file if they exist.

    if (currentDirectory->hasFile(name)) {
        currentDirectory->DeleteFile(name);
        std::cout << name <<" "<< "has been deleted \n";
    }
    else if (currentDirectory->hasSubdirectory(name)) {
        currentDirectory->DeleteDirectory(name);
    }
    else {
        std::cerr << "No file or directory named '" << name << "' found." << std::endl;
    }
}

// lists directory contents using display method in directory which is inherited from filesystementity.
void FileSystem ::listCurrentDirectory()
{
    if (currentDirectory) {
        currentDirectory->Display();
    }
    else {
        std::cerr << "No current directory selected." << std::endl;
    }
}

void FileSystem::exit()
{
    std::cout << "Exiting the file system application." << std::endl;
    std::exit(0);
}