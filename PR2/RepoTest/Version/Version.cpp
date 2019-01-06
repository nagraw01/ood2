
/////////////////////////////////////////////////////////////////////////////////
// Version.cpp - Test stub for Version package where set version and remove version 
//               methods are provided respectively for check-in and check-out process
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

#include "Version.h"

using namespace Repo;

// test stub for this package

int main()
{

	Version::setFileVersion("../RepoFolder/RepoCore.1", "../RepoCore", ".1");
	Version::removeFileVersion("../ RepoFolder","../Checkedout", "RepoCore.1");

	return 0;
}