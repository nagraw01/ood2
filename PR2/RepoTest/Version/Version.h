#pragma once
/////////////////////////////////////////////////////////////////////////////////
// Version.h - Manages version numbering for all files held in the Repository. //                                                //
// ver 1.0                                                                     //
// -----------------------------------------------------------------------     //
// copyright © Nishant Agrawal, 2018                                          //
// Source: Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018           //                                                                   //
// -----------------------------------------------------------------------     //
// Language:    Visual C++, Visual Studio 2017                                //
// Platform:    Windows 7                                                      //
// Application: Spring Project,CSE 687,2018                                   //
// Author:      Nishant Agrawal, Syracuse University                           //
//              SUID: 595031520, nagraw01@syr.edu                              //
/////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides one class:
* - Manages version numbering for all files held in the Repository.

Public Interface :
== == == == == == == == =
Version Class:
	void setFileVersion(std::string, std::string, std::string);
	void removeFileVersion(std::string, std::string, std::string);
//Function Prologues
/* prologues written next to functions

Build commands
== == == ==  == == == == ==
- devenv NoSqlDb.sln

* Required Files:
* ---------------
* FileSystem.h, FileSystem.cpp

* Maintenance History:
* --------------------
* ver 1.0 : 8 Mar 2018
* - first release
*/

#include "../NoSqlDb_1/DbCore/DbCore.h"
#include "../FileSystemDemo/FileSystem.h"

using namespace FileSystem;
namespace Repo
{
	class Version
	{
	public:
		static void setFileVersion(std::string packagePath, std::string filePath, std::string ver);
		static void removeFileVersion(std::string, std::string, std::string);
	};

	//function to set the file version during the check-in process
	void Version::setFileVersion(std::string packagePath, std::string filePath, std::string ver)
	{
		std::cout << "\n In Version package, the files are copied to repository and versions are set:  \n";
		std::cout << packagePath << std::endl;
		FileSystem::Directory::create(packagePath);

		std::vector<std::string> cppfiles = FileSystem::Directory::getFiles(filePath, "*.cpp");
		std::vector<std::string> hfiles = FileSystem::Directory::getFiles(filePath, "*.h");
		
		for (std::string file : cppfiles) {
			std::string nfilePath = FileSystem::Path::fileSpec(filePath, file);

			file = file + ver;
			std::string cppPath = FileSystem::Path::fileSpec(packagePath, file);
			FileSystem::File::copy(nfilePath, cppPath);
		}

		for (std::string file : hfiles) {
			std::string nfilePath = FileSystem::Path::fileSpec(filePath, file);
			
			file = file + ver;
			std::string hPath = FileSystem::Path::fileSpec(packagePath, file);
			FileSystem::File::copy(nfilePath, hPath);
		}
	}

	//function to remove the file version during the check-out process
	void Version::removeFileVersion(std::string repoPath, std::string destPath, std::string packageName)
	{
		std::cout << "\nFile versions are removed in Version package for files in repository and copied to the CheckedOut directory \n";
		std::string filePath = FileSystem::Path::fileSpec(repoPath, packageName);

		size_t lastindex = packageName.find_last_of(".");
		std::string rawname = packageName.substr(0, lastindex);
		std::string newPath = FileSystem::Path::fileSpec(destPath, rawname);
		FileSystem::Directory::create(newPath);

		std::vector<std::string> cppfiles = FileSystem::Directory::getFiles(filePath, "*.cpp.*");
		std::vector<std::string> hfiles = FileSystem::Directory::getFiles(filePath, "*.h.*");

		for (std::string file : cppfiles) {
			
			size_t lindex = file.find_last_of(".");

			std::string fname = file.substr(0, lindex);
			std::cout << fname << " " << std::endl;

			std::string nfilePath = FileSystem::Path::fileSpec(filePath, file);
			std::string cppPath = FileSystem::Path::fileSpec(newPath, fname);
			FileSystem::File::copy(nfilePath, cppPath);
		}

		for (std::string file : hfiles) {
			
			size_t lindex = file.find_last_of(".");
			std::string fname = file.substr(0, lindex);
			std::cout << fname << " " << std::endl;
			std::string nfilePath = FileSystem::Path::fileSpec(filePath, file);
			std::string hPath = FileSystem::Path::fileSpec(newPath, fname);
			FileSystem::File::copy(nfilePath, hPath);
		}
	}
}



