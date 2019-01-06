
/////////////////////////////////////////////////////////////////////////////////
// CheckIn.cpp - Test stub for CheckIn package where all the methods for cheek-in process//
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

#include "CheckIn.h"

using namespace Repo;

// test stub for this package

int main()
{
	Utilities::title("Demonstrating Requirement #4 - Checking In and versioning");
	std::cout << "\n Showing checking functionality:";
	DbCore<NoSqlDb::Package> db_;
	std::string authorName = "Nishant";
	std::cout << "\n Entire NosqlDb project-work is used as the source for checkin, then files are checked in by accepting a single package's files:";
	std::cout << "\n AuthorName is given with check-in, which check against each package, if does not match with the already existing package, check-in is not done:";
	CheckIn<NoSqlDb::Package> checkin;
	checkin.intialize(db_, "../RepositoryCore", authorName);
	std::thread(&CheckIn<NoSqlDb::Package>::close, checkin, std::ref(db_), "RepositoryCore");

	std::cout << "\n The package and its header and source files have been appended with .version_number:";
	std::cout << "\n The checkIn status of any newly created db entry is '0' for open and a new version is generated if the status is '1' for closed:";

	return 0;
}
