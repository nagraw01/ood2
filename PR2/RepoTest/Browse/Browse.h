#pragma once
/////////////////////////////////////////////////////////////////////////////////
// Browse.h - Provides the capability to locate files and view their contents.
//                                                          //
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
* - Browse provides the capability to locate files and view their content
  - It also provides functionality for graphwalk which is used for browsing

Public Interface :
== == == == == == == == =
Browse Class:
	std::vector<std::string> intialize(NoSqlDb::DbCore<T> &db, std::string);
	void display(NoSqlDb::DbCore<T> &db, std::string);
	void graphWalk(NoSqlDb::DbCore<T> &db, std::string key);
	bool getMark(Key key)
	void setMark(Key key)

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
	class Browse
	{
	public:
		std::vector<std::string> intialize(NoSqlDb::DbCore<T> &db, std::string);
		void display(NoSqlDb::DbCore<T> &db, std::string);

		void graphWalk(NoSqlDb::DbCore<T> &db, std::string key);
		//function to get the visited status of the graph node
		bool getMark(Key key) { return mark[key]; }
		//function to set the visited status of the graph node
		void setMark(Key key) { mark[key] = true; }

	private:
		FilePath repoAdd = "../RepoFolder";
		std::unordered_map<Key, bool> mark;
		std::vector<std::string> v;
	};


	//method to start the browsing process, by calling the graphwalk method after applying the query based on pattern provided
	template<typename T>
	std::vector<std::string> Browse<T>::intialize(NoSqlDb::DbCore<T> &db, std::string vec)
	{
		std::cout << "Browsing by key pattern query on NoSqlDb:";
		Query<T> query;

		Keys keys = query.getKeysByKeyPattern(db, vec);
		for (Key k : keys)
		{
			graphWalk(db, k);
		}

		return v;
	}

	//specialized initialize function for package class
	template<>
	std::vector<std::string> Browse<NoSqlDb::Package>::intialize(NoSqlDb::DbCore<NoSqlDb::Package> &db, std::string vec)
	{
		std::cout << "Browsing by key pattern query on NoSqlDb:";
		Query<NoSqlDb::Package> query;

		Keys keys = query.getKeysByKeyPattern(db, vec);
		for (Key k : keys)
		{
			graphWalk(db, k);
		}

		for (Key key : v)
		{
			DbElement<NoSqlDb::Package> el = db[key];
			std::cout << "\nPackage: " << key << std::endl;
			std::cout << "Author name:" << el.descrip() << std::endl;
			std::cout << "Package Description:" << el.descrip() << std::endl;
		}

		return v;
	}

	//function to display contents of the files in the package
	template<typename T>
	void Browse<T>::display(NoSqlDb::DbCore<T> &db, std::string vec)
	{
		T payL = db[vec].payLoad();
	}

	//specialized display function for package class
	template<>
	void Browse<NoSqlDb::Package>::display(NoSqlDb::DbCore<NoSqlDb::Package> &db, std::string vec)
	{		
		
		std::string strPath = db[vec].payLoad().FilePath();

		std::vector<std::string> cppfiles = FileSystem::Directory::getFiles(strPath, "*.cpp*");
		std::vector<std::string> hfiles = FileSystem::Directory::getFiles(strPath, "*.h*");
			
		for (std::string file : cppfiles) 
		{
			std::string filePath = FileSystem::Path::fileSpec(strPath, file);

			FileSystem::File testAll(filePath);
			testAll.open(FileSystem::File::in);
			if (testAll.isGood())
			{
				std::cout << "\n\n\n";
				std::string all = testAll.readAll();
				std::cout << all << "\n\n\n\n";
			}
			testAll.close();
		}

		for (std::string file : hfiles)
		{
			std::string filePath = FileSystem::Path::fileSpec(strPath, file);
			FileSystem::File testAll(filePath);
			testAll.open(FileSystem::File::in);
			if (testAll.isGood())
			{
				std::cout << "\n\n\n";
				std::string all = testAll.readAll();
				std::cout << all << "\n\n\n\n";
			}
			testAll.close();
		}			
	}

	//recursive function for graphwalk
	template<typename T>
	void Browse<T>::graphWalk(NoSqlDb::DbCore<T> &db, std::string key)
	{
		DbElement<T> el = db[key];
		if (mark[key] == true)
			return;
		setMark(key);
		
		v.push_back(key);
		for (auto pChild : el.children())
			graphWalk(db, pChild);

		mark.clear();
	}

}





