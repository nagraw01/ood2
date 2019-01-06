/////////////////////////////////////////////////////////////////////////////
// FileSystem.cpp - Support file and directory operations                  //
// ver 2.8                                                                 //
// ----------------------------------------------------------------------- //
// copyright © Jim Fawcett, 2012                                           //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Dell XPS 8300, Core i7, Windows 7 SP1                      //
// Application: Summer Projects, 2012                                      //
// Author:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <utility>
#include <clocale>
#include <locale>
#include "FileSystem.h"

using namespace FileSystem;

//----< test stub >--------------------------------------------------------

#ifdef TEST_FILESYSTEM

void title(const std::string& title, char ch='=')
{
  std::cout << "\n  " << title;
  std::cout << "\n " << std::string(title.size()+2, ch);
}

int main(int argc, char* argv[])
{
  title("Demonstrate Path Class");

  std::string fs = Path::fileSpec(".","temp.txt");
  std::cout << "\n  Path::fileSpec(\".\",\"temp.txt\") = " << fs;
  
  std::string name = Path::getName(fs);
  std::cout << "\n  Path::getName(\"" + fs + "\") = " << name;

  // Create directory
  std::string filePath = "../RepoAdd/RepoCore.1";
  FileSystem::Directory::create(filePath);

  //get files
  std::vector<std::string> cppfiles = FileSystem::Directory::getFiles(filePath, "*.cpp");

  // read all lines of text file into string
  title("testing File::readAll()", '-');
  std::cout << "\n";
  File testAll("../FileSystemTest.txt");
  testAll.open(File::in);
  if (testAll.isGood())
  {
    std::string all = testAll.readAll();
    std::cout << all << "\n";
  }
  testAll.close();

  title("testing File::readAll(true)", '-');
  std::cout << "\n";
  File testAllTrue("../FileSystemTest.txt");
  testAllTrue.open(File::in);
  if (testAllTrue.isGood())
  {
    std::string all = testAllTrue.readAll(true);
    std::cout << all << "\n";
  }
  testAllTrue.close();
}
#endif
