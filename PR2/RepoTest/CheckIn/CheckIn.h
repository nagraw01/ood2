#pragma once
/////////////////////////////////////////////////////////////////////////////////
// CheckIn.h - Provides the functionality to start a new package version by accepting files, 
//             appending version numbers to their filenames, providing dependency 
//               and category information, creating metadata, and storing the files 
//             in a designated location. 
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
* - CheckIn provides methods to initialize and close check-in process
* - In close method checkIn status is updated using loop in a separate thread

Public Interface :
== == == == == == == == =
CheckIn Class:
      void intialize(NoSqlDb::DbCore<T>, FilePath, std::string)
	  void close(DbCore<T>&, std::string)

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
#include <thread>

namespace Repo
{
	using FilePath = std::string;

	template<typename T>
	class CheckIn
	{
	public:
		void intialize(NoSqlDb::DbCore<T> &db_, FilePath filePath, std::string authorName);
		void close(DbCore<T>& db, std::string pack);

		void addDependency(DbCore<T>& db, std::string, std::string);
		void addDependency1(DbCore<T>& db, std::string);
		void addDependency2(DbCore<T>& db, std::string);
		void addDependency3(DbCore<T>& db, std::string);
		void addDependency4(DbCore<T>& db, std::string);
		void addDependency5(DbCore<T>& db, std::string);
		void addDependency6(DbCore<T>& db, std::string);

	private:
		FilePath repoAdd = "../RepoFolder";
	};

	//function to take one package and check it by checking against its author, previous version and copying files and creating db entries for the repository
	template<typename T>
	void CheckIn<T>::intialize(NoSqlDb::DbCore<T> &db, FilePath filePath, std::string authorName)
	{
		FileSystem::Directory pack = FileSystem::Path::getName(filePath);
		Query<T> query;
		Keys keys = query.getKeysByNamePattern(db, pack);

		if (keys.size() != 0 && db[keys[0]].name().compare(authorName) != 0)
		{
			std::cout << "\n This is not this package's author, checkin for package " << pack << " failed\n";
		}
	}

	//specialized function to start the checkin process for package class
	template<>
	void CheckIn<NoSqlDb::Package>::intialize(NoSqlDb::DbCore<NoSqlDb::Package> &db, FilePath packagePath, std::string authorName)
	{
			std::string pack = FileSystem::Path::getName(packagePath);
			Query<NoSqlDb::Package> query;
			Keys keys = query.getKeysByNamePattern(db, pack);  

			int maxVersion = 0;
			int checkinstat = 1;
			if (keys.size() != 0 && db[keys[0]].descrip().compare(authorName) != 0)
			{
				std::cout << "\n This is not this package's author, checkin for package " << pack << " failed\n";
				return;
			}
			
			for (size_t i = 0; i < keys.size(); i++) {
				if (db[keys[i]].payLoad().PackVersion() > maxVersion) {
					maxVersion = db[keys[i]].payLoad().PackVersion();
					checkinstat = db[keys[i]].payLoad().CheckInStatus();
				}
			}
			if (checkinstat == 1)
			{
				//copy the contents with new version
				std::string ver = "." + std::to_string(maxVersion + 1);
				std::string newP = pack + ver;
				std::string newPath = FileSystem::Path::fileSpec(repoAdd, newP);
				Version::setFileVersion(newPath, packagePath, ver);

				//creating the db entry
				DbElement<NoSqlDb::Package> demoElem;
				NoSqlDb::Package demoLoad;
				demoLoad.PackVersion(maxVersion + 1);
				demoLoad.CheckInStatus(0);
				demoLoad.FilePath(newPath);

				demoElem.name(pack);
				demoElem.descrip(authorName);
				demoElem.dateTime(DateTime().now());
				demoElem.payLoad(demoLoad);

				std::string newPack = FileSystem::Path::getName(newPath);
				db[newPack] = demoElem;
				addDependency(db, pack, newPack);
			}
	}

	//function that is started as a thread process to update the checkin status and close the checkin process 
	template<typename T>
	void CheckIn<T>::close(DbCore<T> &db, std::string pack)
	{
		std::cout << "hello from unspecialized close: ";
	}

	//specialized function to close the checkin process for package class
	template<>
	void CheckIn<NoSqlDb::Package>::close(DbCore<NoSqlDb::Package> &db, std::string pack)
	{
		int loopCount = 0;
		Query<NoSqlDb::Package> q1;
		Keys keys = q1.getKeysByNamePattern(db, pack);
		int maxVersion = 0;
		int checkinstat = 0;
		Key keyUse;
		for (size_t i = 0; i < keys.size(); i++) {
			if (db[keys[i]].payLoad().PackVersion() > maxVersion) {
				maxVersion = db[keys[i]].payLoad().PackVersion();
				keyUse = keys[i];
				checkinstat = db[keys[i]].payLoad().CheckInStatus();
			}
		}

		if (checkinstat == 0) 
		{
			DbElement<NoSqlDb::Package> el = db[keyUse];
			while (db[keyUse].payLoad().CheckInStatus() != 1 && loopCount != 10)
			{
				loopCount++;
				int count = 0;
				for (Key child : el.children())
				{
					Query<NoSqlDb::Package> q1;
					Keys childVers = q1.getKeysByNamePattern(db, child);
					if (childVers.size() != 0 && db[childVers[0]].payLoad().CheckInStatus() == 1) {
						count++;
					}
				}
				if (count == el.children().size()) {
					NoSqlDb::Package demoLoad = el.payLoad();
					demoLoad.CheckInStatus(1);
					el.payLoad(demoLoad);
					db[keyUse] = el;
				}
			}
		}
	}

	//function to add the child dependencies
	template<typename T>
	void CheckIn<T>::addDependency(NoSqlDb::DbCore<T> &db, std::string pack, std::string newPack)
	{
		if(pack.compare("StringUtilities") == 0)
			addDependency1(db, newPack);
		else if (pack.compare("TestUtilities") == 0)
			addDependency2(db, newPack);
		else if (pack.compare("DateTime") == 0)
			addDependency3(db, newPack);
		else if (pack.compare("DbCore") == 0)
			addDependency4(db, newPack);
		else if (pack.compare("Query") == 0)
			addDependency5(db, newPack);
		else if (pack.compare("RepositoryCore") == 0)
			addDependency5(db, newPack);
	}

	//helper function to add the child dependencies
	template<typename T>
	void CheckIn<T>::addDependency1(NoSqlDb::DbCore<T> &db, std::string newPack)
	{
		DbElement<T> elem = db[newPack];
	    elem.addChild("CodeUtilities");
		db[newPack] = elem;
	}
	
	//helper function to add the child dependencies
	template<typename T>
	void CheckIn<T>::addDependency2(NoSqlDb::DbCore<T> &db, std::string newPack)
	{
		DbElement<T> elem = db[newPack];
		elem.addChild("StringUtilities");
		db[newPack] = elem;
	}

	//helper function to add the child dependencies
	template<typename T>
	void CheckIn<T>::addDependency3(NoSqlDb::DbCore<T> &db, std::string newPack)
	{
		DbElement<T> elem = db[newPack];
		elem.addChild("StringUtilities");
		db[newPack] = elem;
	}

	//helper function to add the child dependencies
	template<typename T>
	void CheckIn<T>::addDependency4(NoSqlDb::DbCore<T> &db, std::string newPack)
	{
		DbElement<T> elem = db[newPack];
		elem.addChild("StringUtilities");
		elem.addChild("DateTime");
		db[newPack] = elem;
	}

	//helper function to add the child dependencies
	template<typename T>
	void CheckIn<T>::addDependency5(NoSqlDb::DbCore<T> &db, std::string newPack)
	{
		DbElement<T> elem = db[newPack];
		elem.addChild("StringUtilities");
		elem.addChild("DateTime");
		elem.addChild("DbCore");
		db[newPack] = elem;
	}

	//helper function to add the child dependencies
	template<typename T>
	void CheckIn<T>::addDependency6(NoSqlDb::DbCore<T> &db, std::string newPack)
	{
		DbElement<T> elem = db[newPack];
		elem.addChild("CheckIn");
		elem.addChild("DateTime");
		elem.addChild("DbCore");
		elem.addChild("CheckOut");
		elem.addChild("Browse");
		elem.addChild("FileSystemDemo");
		db[newPack] = elem;
	}

}



