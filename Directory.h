#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "FileSystemEntity.h"

class Directory : public FileSystemEntity {
public:
    Directory(const std::string& name, const std::string& creationDate);

    void AddFile(const std::string& fileName, size_t fileSize , const std::string& FileDate);
    void AddDirectory(const std::string& directoryName, const std::string& directoryDateCreated);
    void DeleteFile(const std::string& fileName);
    void DeleteDirectory(const std::string& directoryName);
    void SortBySize();
    void SortByName();
    void Display() const override;
    bool hasSubdirectory(const std::string& directoryName)const;
    bool hasFile(const std::string& fileName)const;
    size_t GetTotalFilesSize() const;
    size_t GetTotalFilesCount() const;
    size_t GetTotalDirectoriesCount() const;
    Directory* getSubdirectory(const std::string& directoryName) const;
    Directory* getParentDirectory() const;
    static std::string GetCurrentDateTime();
    void ListContents() const;


private:
    Directory* parentDirectory;
    std::vector<std::unique_ptr<FileSystemEntity>> directoryContents; // Contents of the directory, holding files and subdirectories
};
