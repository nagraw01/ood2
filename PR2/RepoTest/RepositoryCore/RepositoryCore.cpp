
/////////////////////////////////////////////////////////////////////////////////
// RepositoryCore.cpp - Test stub for RepositoryCore package where methods to interact with
//                      CheckIn, CheckOut, Version and Browse packages
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

#include "RepositoryCore.h"

using namespace Repo;

// test stub for this package

int main()
{
	RepositoryCore<NoSqlDb::Package> rc;
	std::string authorName = "Nishant";
	rc.startCheckIn("../NoSqlDb_1", authorName);

	std::vector<std::string> checkOutList;
	checkOutList.push_back("DbCore.1");
	rc.startCheckOut("../CheckedOut", checkOutList);

	std::vector<std::string> dTKey = rc.startBrowse(".*Db.*");
	rc.displayBrowseText(dTKey[0]);
	return 0;
}
