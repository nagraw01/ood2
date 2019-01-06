
/////////////////////////////////////////////////////////////////////////////////
// Browse.cpp - Test stub for Browse package where all the methods for repo browsing are provided//
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

#include "Browse.h"

using namespace Repo;

// test stub for this package

int main()
{
	DbCore<NoSqlDb::Package> db_;
	Browse<NoSqlDb::Package> b;
	std::vector<std::string> dTKey  =  b.intialize(db_, ".*Date.*");
	b.display(db_, dTKey[0]);
	return 0;
}
