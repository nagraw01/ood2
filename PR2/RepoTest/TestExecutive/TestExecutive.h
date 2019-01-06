#pragma once
/////////////////////////////////////////////////////////////////////////////////
// TestExecutive.h - All the requirements are created as test methods here 
//                  to be executed in a try-catch block are defined here                       //
// ver 1.0                                                                     //
// -----------------------------------------------------------------------     //
// copyright © Nishant Agrawal, 2018                                          //
// Source: Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018           // 
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
* This package does not have any class

Public Interface :
== == == == == == == == =

//Function Prologues
/* prologues written next to functions

Build commands
== == == ==  == == == == ==
- devenv RepoTest.sln

* Required Files:
* ---------------
* DbCore.h, DbCore.cpp
* DateTime.h, DateTime.cpp
* StringUtilities.h, StringUtilities.cpp
* Query.h, Query.cpp
* TestUtilities.h, TestUtilities.cpp
* RepositoryCore.h, RepositoryCore.cpp

* Maintenance History:
* --------------------
* ver 1.0 : 8 Mar 2018
* - first release
*/

#include "../NoSqlDb_1/Utilities/TestUtilities/TestUtilities.h"
#include "../RepositoryCore/RepositoryCore.h"

#include <iostream>
#include <iomanip>
#include <functional>

namespace Repo
{


	//----< reduce the number of characters to type >----------------------

	auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
	{
		Utilities::putline(n, out);
	};

	///////////////////////////////////////////////////////////////////////
	// test functions

	//----< demo requirement #1 >------------------------------------------

	bool testR1()
	{
		Utilities::title("Demonstrating Requirement #1");
		std::cout << "\n  " << typeid(std::function<bool()>).name()
			<< ", declared in this function, "
			<< "\n  is only valid for C++11 and later versions.";
		putLine();
		return true; // would not compile unless C++11
	}

	//----< demo requirement #2 >------------------------------------------

	bool testR2()
	{
		Utilities::title("Demonstrating Requirement #2");
		std::cout << "\n  A visual examination of all the submitted code "
			<< "will show only\n  use of streams and operators new and delete.";
		putLine();
		return true;
	}

	//----< demo first part of requirement #3 >----------------------------

	bool testR3()
	{
		Utilities::title("Demonstrating Requirement #3a- TestExecutive package");
		std::cout << "\n Executes a sequence of tests to demonstrate core Repository functionality:";
		Utilities::title("Demonstrating Requirement #3b- RepositoryCore package");
		std::cout << "\n Provides methods startCheckIn() to use CheckIn package functions , Versioning done in Version package, startBrowse() and displayBrowseText() methods to use Browse functions package, and startCheckOut() to use CheckOut package functions.";
		Utilities::title("Demonstrating Requirement #3c- CheckIn package");
		std::cout << "\n Showing checking functionality:";
		RepositoryCore<NoSqlDb::Package> rc;
		std::string authorName = "Nishant";
		rc.startCheckIn("../NoSqlDb_1", authorName);
		std::cout << "\n CheckIn package provides initialize() method to start the check-in process and close to stop check-in process, there are many helper functions to set the dependencies:";
		Utilities::title("Demonstrating Requirement #3d- CheckOut package");
		std::cout << "\n CheckOut package provides initialize() method to start the check-out process and recurse() to check-out all the dependent packages:";
		std::cout << "\n CheckOut is done to a path provided, of the required package version:";
		std::cout << "A list of packages to be checked out is inputted, all the dependencies of each package are also checked-out alongwith:";
		std::vector<std::string> checkOutList;
		checkOutList.push_back("DbCore.1");
		rc.startCheckOut("../CheckedOut", checkOutList);
		Utilities::title("Demonstrating Requirement #3e- Version package");
		std::cout << "\n Version package provides setVersion() method to set during check-in process and removeVersion() to remove while check-out:";
		Utilities::title("Demonstrating Requirement #3f- Browse package");
		std::cout << "\n Browse package provides initialize() method to start the browsing using a query and returns the query result, and then display to show all the contents of the package using the selected key, graphWalk() method for doing the graph walk while browsing and setmark() and getMark() methods as graph walk helper functions:";
		std::vector<std::string> dTKey = rc.startBrowse(".*Db.*");
		rc.displayBrowseText(dTKey[0]);
		return true;
	}

	//----< demo second part of requirement #4 >---------------------------
	bool testR4()
	{
		Utilities::title("Demonstrating Requirement #4 - Checking In and versioning");
		std::cout << "\n Showing checking functionality:";
		
		RepositoryCore<NoSqlDb::Package> rc;
		std::string authorName = "Nishant";
		std::cout << "\n Entire NosqlDb project-work is used as the source for checkin, then files are checked in by accepting a single package's files:";
		std::cout << "\n AuthorName is given with check-in, which check against each package, if does not match with the already existing package, check-in is not done:";
		rc.startCheckIn("../RepositoryCore", authorName);
		std::cout << "\n The package and its header and source files have been appended with .version_number:";
		std::cout << "\n The checkIn status of any newly created db entry is '0' for open and a new version is generated if the status is '1' for closed:";
		
		return true;
	}

	//----< demo of requirement #5 >---------------------------

	bool testR5()
	{
		Utilities::title("Demonstrating Requirement #5 - Brwosing with query, do graphwalk on resultset and display the full contents of a package files:");
		
		RepositoryCore<NoSqlDb::Package> rc;
		std::string authorName = "Nishant";
		rc.startCheckIn("../NoSqlDb_1", authorName);
		std::cout << "\n For Browse query is applied on NoSqlDb, graph walk is used for displaying description, a pattern query is applied to get a keyset, after graphwalk the list of keys is returned:";
		std::vector<std::string> dTKey = rc.startBrowse(".*Date.*");
		std::cout << "\n One key out of keyset is inputted to display the full text of the package files:";
		rc.displayBrowseText(dTKey[0]);
		
		return true;
	}

	//----< demo second part of requirement #6 >---------------------------

	bool testR6()
	{
		Utilities::title("Demonstrating Requirement #6 - multiple packages in the repository with open and closed check-ins both:");	
		return true;
	}

	//----< demo second part of requirement #7 >---------------------------

	bool testR7()
	{
		Utilities::title("Demonstrating Requirement #7- TestExecutive package defines and executes all the tests satisfying the requirements: ");
		return true;
	}

}

