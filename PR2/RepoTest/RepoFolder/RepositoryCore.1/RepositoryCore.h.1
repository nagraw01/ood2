#pragma once
/////////////////////////////////////////////////////////////////////////////////
// RepositoryCore.h - Provides means to check-in, version, browse, and check-out 
//                    source code packages
//                                                                             //
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
* - RepositoryCore Provides means to check-in, version, browse, and check-out 
                source code packages

Public Interface :
== == == == == == == == =
RepositoryCore Class:
		void startCheckIn(FilePath, std::string);
		void startCheckOut(FilePath, std::vector<FilePath>)
		std::vector<std::string> startBrowse(std::string)
		void displayBrowseText(std::string)

//Function Prologues
/* prologues written next to functions

Build commands
== == == ==  == == == == ==
- devenv RepoTest.sln

* Required Files:
* ---------------
* DbCore.h, DbCore.cpp
* CheckIn.h, CheckIn.cpp
* CheckOut.h, CheckOut.cpp
* Browse.h, Browse.cpp

* Maintenance History:
* --------------------
* ver 1.0 : 8 Mar 2018
* - first release
*/

#include "../CheckIn/CheckIn.h"
#include "../CheckOut/CheckOut.h"
#include "../Browse/Browse.h"
#include <vector>
#include <thread>
#include <future>

namespace Repo
{
	using FilePath = std::string;
	
	template<typename T>
	class RepositoryCore
	{
	public:
		void startCheckIn(FilePath filePath, std::string);
		void startCheckOut(FilePath destPath, std::vector<FilePath> packageList);
		std::vector<std::string> startBrowse(std::string);
		void displayBrowseText(std::string vec);

	private:
		FilePath repoAdd = "../RepoFolder";
		DbCore<T> db_;
	};
	
	//function to start checkin process and setting the version by using the CheckIn class methods
	template<typename T>
	void RepositoryCore<T>::startCheckIn(FilePath filePath, std::string authorName)
	{
		std::cout << "\n All the packages are identified in the source directory, as listed down and then all files for each package is checked in:\n";
		FileSystem::DirecHelper dh;
		std::vector<std::thread> threads;

		std::vector<FilePath> packageList = dh.recurseDirec(filePath);
		for (std::string packagePath : packageList)
		{
			std::string packageName = FileSystem::Path::getName(packagePath);
			std::cout << "\n packname:\n" << packageName;
			CheckIn<T> checkin;
			checkin.intialize(db_, packagePath, authorName);
		}

		for (std::string packagePath : packageList)
		{
			std::string packageName = FileSystem::Path::getName(packagePath);
			CheckIn<T> checkin;
			threads.push_back(std::thread(&CheckIn<T>::close, checkin, std::ref(db_), packageName));
		}
		for (auto& th : threads) 
		{
			th.join();
		}
		
		std::cout << "\n After setting the version, copying files in repository and setting contents in the NoSqlDb, the contents of NoSqlDb looks like below.:";
		NoSqlDb::showDb(db_);			
	}

	//function to start the browsing by calling initialize method of the browse class
	template<typename T>
	std::vector<std::string> RepositoryCore<T>::startBrowse(std::string vec)
	{
		Browse<T> b;
		return b.intialize(db_, vec);
	}

	//function to display package text by calling display method of the browse class
	template<typename T>
	void RepositoryCore<T>::displayBrowseText(std::string vec)
	{
		std::cout << "\nOn demand from the executive, full package text is displayed:" << std::endl;
		Browse<T> b;
		b.display(db_, vec);
	}

	//function to start the check out process
	template<typename T>
	void RepositoryCore<T>::startCheckOut(FilePath destPath, std::vector<FilePath> packageList)
	{
		
		for (std::string package : packageList)
		{
			CheckOut<T> checkOut;
			checkOut.intialize(db_, destPath, package);
		}
	}
}



