#include "Directory.h"
#include "File.h"
#include <iostream>
#include <chrono>
#include<algorithm>

Directory::Directory(const std::string& name, const std::string& creationDate):FileSystemEntity(name, creationDate), parentDirectory(nullptr){}


//I used Michael's provided code in main.cpp and documentation for converting time into string, link : https://www.ibm.com/docs/en/i/7.1?topic=functions-ctime-convert-time-character-string
std::string Directory::GetCurrentDateTime() 
{
    auto currentTime = std::chrono::system_clock::now();
    std::time_t creationTime = std::chrono::system_clock::to_time_t(currentTime);

    char timeString[26];
    ctime_s(timeString, sizeof(timeString), &creationTime);

    
    timeString[24] = '\0';  

    return std::string(timeString);
}


// Adds Files in Vector 
void Directory::AddFile(const std::string& fileName, size_t fileSize, const std::string& FileDate)
{
    // checks if new file with the same name already exists in the directory
    for (const auto& entity : directoryContents) 
    {
        if (entity->GetName() == fileName) {
            std::cerr << "File \"" << fileName << "\" already exists in the directory." << std::endl;
            return;
        }
    }
    // creates creation date variable to use when adding file directory using GetCurrentDateTime method
    std::string creationDate = GetCurrentDateTime();

    // Create a new file and add it to the vector
    directoryContents.push_back(std::make_unique<File>(fileName, fileSize, creationDate));
}



// Adds directory in Vector
void Directory::AddDirectory(const std::string& directoryName, const std::string& directoryDateCreated)
{
    //Check if Directory exists 
    for (const auto& entity : directoryContents)
    {
        if (entity->GetName() == directoryName)
        {
            std::cerr << "Directory \"" << directoryName << "\" already exists." << std::endl;
            return;
        }
    }


    std::string creationDate = GetCurrentDateTime();

    auto newDirectory = std::make_unique<Directory>(directoryName, creationDate);
    newDirectory->parentDirectory = this; // Set the parent directory
    directoryContents.push_back(std::move(newDirectory));

}


void Directory::DeleteFile(const std::string& fileName)
{ // Checks if Files exists in vector and deletes

    for (auto i = directoryContents.begin(); i != directoryContents.end(); ++i)
    {
        if ((*i)->GetName() == fileName && dynamic_cast<File*>(i->get()) != nullptr) 
        {
            directoryContents.erase(i);
            return;
        }

    }
    std::cerr << "File \"" << fileName << "\" not found in the directory." << std::endl;
}


void Directory::DeleteDirectory(const std::string& directoryName)
{
    // Checks if directory exists in vector and deletes
    for (auto i = directoryContents.begin(); i != directoryContents.end(); ++i) 
    {
        if ((*i)->GetName() == directoryName && dynamic_cast<Directory*>(i->get()) != nullptr) 
        {
            // If found, erase the directory from the vector and return
            directoryContents.erase(i);
            return;
        }
    }

    std::cerr << "Directory \"" << directoryName << "\" not found in the directory." << std::endl;
}



void Directory::ListContents() const
{
    //uses dynamic casting (runtime type operators) to check whether each FileSystemEntity in directoryContents is actually a Directory or a File.
    for (const auto& entity : directoryContents) {
        auto dir = dynamic_cast<Directory*>(entity.get());
        auto file = dynamic_cast<File*>(entity.get());
        
        //Iterate through directory contents and display information for each item.

        std::cout << entity->GetCreationDate() << "\t";
        if (dir) {
            std::cout << "<DIR>\t\t" << dir->GetName() << std::endl;
        }
        else if (file) {
            std::cout << "\t" << file->GetFileSize() << " bytes\t" << file->GetName() << std::endl;
        }
    }

    std::cout << "\t" << GetTotalFilesCount() << " File(s)\t"
        << GetTotalFilesSize() << " total bytes" << std::endl;
    std::cout << "\t" << GetTotalDirectoriesCount() << " Dir(s)" << std::endl;
}

//Sorts Directory by file size and keeps Sub-Directories top of the list
void Directory::SortBySize()
{
    std::sort(directoryContents.begin(), directoryContents.end(),
        [](const std::unique_ptr<FileSystemEntity>& a, const std::unique_ptr<FileSystemEntity>& b) 
        {
            // Prioritize directories over files
            auto aIsDir = dynamic_cast<Directory*>(a.get()) != nullptr;
            auto bIsDir = dynamic_cast<Directory*>(b.get()) != nullptr;
            if (aIsDir && !bIsDir) return true;
            if (!aIsDir && bIsDir) return false;

            // If both are files, sort by size
            if (!aIsDir && !bIsDir) {
                auto aFile = dynamic_cast<File*>(a.get());
                auto bFile = dynamic_cast<File*>(b.get());
                return aFile->GetFileSize() < bFile->GetFileSize();
            }

            // If both are directories, they are considered equal in size
            return false;
        }
    );
}


//Sorts Directory in lexographically order
void Directory::SortByName()
{
    std::sort(directoryContents.begin(), directoryContents.end(),
        [](const std::unique_ptr<FileSystemEntity>& a, const std::unique_ptr<FileSystemEntity>& b) {
            return a->GetName() < b->GetName();
        });
}


//Calculates Total size for files in directory
size_t Directory::GetTotalFilesSize() const
{
    size_t FilesTotalSize = 0;
    for (const auto& entity : directoryContents) {
        auto file = dynamic_cast<File*>(entity.get());
        if (file) {
            FilesTotalSize += file->GetFileSize();
        }
    }
    return FilesTotalSize;
}

// Calculates TotalFiles in Directory
size_t Directory::GetTotalFilesCount() const
{
    size_t fileCount = 0;
    for (const auto& entity : directoryContents) {
        if (dynamic_cast<File*>(entity.get())) {
            ++fileCount;
        }
    }
    return fileCount;

}

// Calculates SubDirectories
size_t Directory::GetTotalDirectoriesCount() const
{
    size_t dirCount = 0;
    for (const auto& entity : directoryContents) {
        if (dynamic_cast<Directory*>(entity.get())) {
            ++dirCount;
        }
    }
    return dirCount;
}




//Find subdirectory of current directory
Directory* Directory::getSubdirectory(const std::string& directoryName) const {
    for (const auto& entity : directoryContents) {
        auto dir = dynamic_cast<Directory*>(entity.get());
        if (dir && dir->GetName() == directoryName) {
            return dir;
        }
    }
    return nullptr; // Return nullptr if the directory is not found
}

// Gets parent Directory of current Directory 
Directory* Directory::getParentDirectory() const {
    return parentDirectory;
}



// Checks if a subdirectory exists within the current directory.
bool Directory::hasSubdirectory(const std::string& directoryName) const {
    for (const auto& entity : directoryContents) {
        auto dir = dynamic_cast<Directory*>(entity.get());
        if (dir && dir->GetName() == directoryName) {
            return true;
        }
    }
    return false;
}

// Checks if a File exists within the current directory.
bool Directory::hasFile(const std::string& fileName) const {
    for (const auto& entity : directoryContents) {
        auto file = dynamic_cast<File*>(entity.get());
        if (file && file->GetName() == fileName) {
            return true;
        }
    }
    return false;
}




//Displays Current Directory Information ( inheriting from abstract class FileSystemEntity) 
void Directory::Display() const 
{
    for (const auto& entity : directoryContents) {
        std::cout << entity->GetCreationDate() << "\t";

        auto dir = dynamic_cast<Directory*>(entity.get());
        auto file = dynamic_cast<File*>(entity.get());
        if (dir) {
            std::cout << "<DIR>\t\t" << dir->GetName() << std::endl;
        }
        else if (file) {
            std::cout << "\t" << file->GetFileSize() << "\t" << file->GetName() << std::endl;
        }
    }

    std::cout << "\t" << GetTotalFilesCount() << " File(s)\t"
        << GetTotalFilesSize() << " total bytes" << std::endl;
    std::cout << "\t" << GetTotalDirectoriesCount() << " Dir(s)" << std::endl;
}
