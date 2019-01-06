
/////////////////////////////////////////////////////////////////////////////////
// CheckOut.cpp - Test stub for CheckOut package where all the methods used 
//                for check-out process                                       //
// ver 1.0                                                                     //
// -----------------------------------------------------------------------     //
// copyright © Nishant Agrawal, 2018                                          //
// Source: Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018           //                                                                   //
// -----------------------------------------------------------------------     //
// Language:    Visual C++, Visual Studio 2017                                //
// Platform:    Windows 7                                                      //
// Application: Spring Project, CSE 687, 2018                                   //
// Author:      Nishant Agrawal, Syracuse University                           //
//              SUID: 595031520, nagraw01@syr.edu                              //
/////////////////////////////////////////////////////////////////////////////////

#include "CheckOut.h"

using namespace Repo;

// test stub for this package

int main()
{
	Utilities::title("Demonstrating Requirement- CheckOut package");
	DbCore<NoSqlDb::Package> db_;
	CheckOut<NoSqlDb::Package> checkOut;
	checkOut.intialize(db_, "../CheckedOut", "DbCore.1");
	
	std::cout << "\n CheckOut package provides initialize() method to start the check-out process and recurse() to check-out all the dependent packages:";
	std::cout << "\n CheckOut is done to a path provided, of the required package version:";
	std::cout << "A list of packages to be checked out is inputted, all the dependencies of each package are also checked-out alongwith:";

	return 0;
}
