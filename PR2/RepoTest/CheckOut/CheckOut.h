#pragma once
/////////////////////////////////////////////////////////////////////////////////
// CheckOut.h - retrieves package files, removing version information from their 
//              filenames. Retrieved files will be copied to a specified directory.
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
* - CheckOut provides mechanism to retrieves package files, removing version information from their filenames. 
   also retrieved files will be copied to a specified directory.

Public Interface :
== == == == == == == == =
CheckOut Class:
       void intialize(NoSqlDb::DbCore<T>, FilePath, FilePath);
       void recurse(NoSqlDb::DbCore<T>, FilePath);

//Function Prologues
/* prologues written next to functions

Build commands
== == == ==  == == == == ==
- devenv RepoTest.sln

* Required Files:
* ---------------
* DbCore.h, DbCore.cpp
* DateTime.h, DateTime.cpp
* Version.h, Version.cpp
* Query.h, Query.cpp

* Maintenance History:
* --------------------
* ver 1.0 : 8 Mar 2018
* - first release
*/

#include "../NoSqlDb_1/DbCore/DbCore.h"
#include "../NoSqlDb_1/Query/Query.h"
#include "../Version/Version.h"

namespace Repo
{
	using FilePath = std::string;

	template<typename T>
	class CheckOut
	{
	public:
		void intialize(NoSqlDb::DbCore<T> &db_, FilePath destPath, FilePath packageList);
		void recurse(NoSqlDb::DbCore<T> &db_, FilePath packageName);

	private:
		FilePath repoAdd = "../RepoFolder";
		std::vector<std::string> outList;
	};

	//function to initialize the checkout process package by package along-with all dependencies
	template<typename T>
	void CheckOut<T>::intialize(NoSqlDb::DbCore<T> &db, FilePath destPath, FilePath packageName)
	{
		recurse(db, packageName);

		for (Key k : outList) 
		{
			if (db.contains(k)) 
			{
				std::cout << "\nPackage Name: " << k;
				Version::removeFileVersion(repoAdd, destPath, k);
			}			
		}
	}

	//function to recurse over the package children to find all the dependencies
	template<typename T>
	void CheckOut<T>::recurse(NoSqlDb::DbCore<T> &db, FilePath packageName)
	{
		if (!(std::find(outList.begin(), outList.end(), packageName) != outList.end()))
		{
			outList.push_back(packageName);
		}
		std::string packPath = FileSystem::Path::fileSpec(repoAdd, packageName);
		Query<NoSqlDb::Package> query;
		Keys keys = query.getChildrenByKey(db, packageName);
		for (Key k : keys) {
			k = k + "." + packageName.back();
			recurse(db, k);
		}
	}
}




