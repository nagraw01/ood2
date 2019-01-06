
/////////////////////////////////////////////////////////////////////////////////
// TestExecutive.cpp - Main execution thread for the project is here.          //
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

#include "TestExecutive.h"

using namespace Repo;

// test stub for this package

int main()
{
	Utilities::Title("Testing test repository: ");
	putLine();
	TestExecutive ex;
	// define test structures with test function and message
	TestExecutive::TestStr ts1{ testR1, "Requirement# 1" };
	TestExecutive::TestStr ts2{ testR2, "Requirement# 2" };
	TestExecutive::TestStr ts3{ testR3, "Requirement# 3" };
	TestExecutive::TestStr ts4{ testR4, "Requirement# 4" };
	TestExecutive::TestStr ts5{ testR5, "Requirement# 5" };
	TestExecutive::TestStr ts6{ testR6, "Requirement# 6" };
	TestExecutive::TestStr ts7{ testR7, "Requirement# 7" };

	// register test structures with TestExecutive instance, ex
	ex.registerTest(ts1);
	ex.registerTest(ts2);
	ex.registerTest(ts3);
	ex.registerTest(ts4);
	ex.registerTest(ts5);
	ex.registerTest(ts6);
	ex.registerTest(ts7);

	// run tests
	bool result = ex.doTests();
	if (result == true)
		std::cout << "\n  all tests passed";
	else
		std::cout << "\n  at least one test failed";
	putLine(2);
	return 0;
}