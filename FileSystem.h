#pragma once
#include <iostream>
#include "Directory.h"


class FileSystem
{
public:
	FileSystem();
	void ProcessUserInput(const std::string& input);
	void cd(const std::string& directoryName);
	void mkdir(const std::string& directoryName);
	void mkfile(const std::string& fileName, size_t fileSize);
	void del(const std::string& name);
	void exit();
	void listCurrentDirectory();
	void Dir();
	bool CheckIfDirectoryExists(const std::string& directoryName) const;
	static size_t generateRandomFileSize();
	~FileSystem() {};
protected:

private:
	std::unique_ptr<Directory> rootDirectory;
	Directory* currentDirectory;


};