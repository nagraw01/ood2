/////////////////////////////////////////////////////////////////////////
// ServerPrototype.cpp - Console App that processes incoming messages  //
// ver 1.0                                                             //
// -----------------------------------------------------------------------     //
// copyright © Nishant Agrawal, 2018                                          //
// Source: Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018           //                                                                   //
// -----------------------------------------------------------------------     //
// Language:    Visual C++, Visual Studio 2017                                //
// Platform:    Windows 7                                                      //
// Application: Spring Project,CSE 687,2018                                   //
// Author:      Nishant Agrawal, Syracuse University                           //
//              SUID: 595031520, nagraw01@syr.edu                              //
////////////////////////////////////////////////////////////////////////////////

#include "ServerPrototype.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include <chrono>

namespace MsgPassComm = MsgPassingCommunication;

using namespace Repository;
using namespace FileSystem;
using Msg = MsgPassingCommunication::Message;


//function to getFiles using the FileSystem directory
Files Server::getFiles(const Repository::SearchPath& path)
{
	return Directory::getFiles(path);
}

//function to getDirs using the FileSystem directory
Dirs Server::getDirs(const Repository::SearchPath& path)
{
  return Directory::getDirectories(path);
}

//function to display the message to or on server
template<typename T>
void show(const T& t, const std::string& msg)
{
  std::cout << "\n  " << msg.c_str();
  for (auto item : t)
  {
    std::cout << "\n    " << item.c_str();
  }
}

//function to echo back the same message 
std::function<Msg(Msg)> echo = [](Msg msg) {
  Msg reply = msg;
  reply.to(msg.from());
  reply.from(msg.to());
  return reply;
};

//callable object called for browse
std::function<Msg(Msg)> getFiles = [](Msg msg) {

    Files files = Server::getFiles(storageRoot);
	Files dirs = Server::getDirs(storageRoot);
	std::cout << dirs.size();
    size_t count = 0;
	
	for (auto item : dirs)
	{
		if (item != "." && item != "..") 
		{
			Files files1 = Server::getFiles(FileSystem::Path::fileSpec(storageRoot, item));

			for (auto file1 : files1)
			{
				std::string dirPath = item + "//" + file1;
				files.push_back(dirPath);
			}
		}
	}
    for (auto item : files)
    {
	  std::string countStr = Utilities::Converter<size_t>::toString(++count);
      msg.attribute("file" + countStr, item);
    }
  return msg;
};

//callable object called for browse
std::function<Msg(Msg)> getDirs = [](Msg msg) {

    Files dirs = Server::getDirs(storageRoot);
    size_t count = 0;
    for (auto item : dirs)
    {
      if (item != ".." && item != ".")
      {
        std::string countStr = Utilities::Converter<size_t>::toString(++count);
		msg.attribute("dir" + countStr, item);
      }
    }

  return msg;
};

//callable object added in the dispatcher for browse
std::function<Msg(Msg)> replyBrowse = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command(msg.command());
	reply = getDirs(reply);
	reply = getFiles(reply);

	return reply;
};

//callable object added in the dispatcher for check-in
std::function<Msg(Msg)> replyCheckIn = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command(msg.command());
	reply.attribute("reply", "Check_in succesful");

	return reply;
};

//callable object added in the dispatcher for check-out
std::function<Msg(Msg)> replyCheckout = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command(msg.command());
	reply.attribute("reply", "Check_out succesful");

	return reply;
};

//callable object added in the dispatcher for view text
std::function<Msg(Msg)> replyViewtext = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command(msg.command());
	std::string path = msg.value("path");
	std::cout << path << "...new path";

	if (path != "")
	{
		std::string searchPath = FileSystem::Path::fileSpec(storageRoot, path);
		std::cout << searchPath << "...new path";
		FileSystem::File testAll(searchPath);
		testAll.open(FileSystem::File::in);
		if (testAll.isGood())
		{
			std::string all = testAll.readAll();
			reply.attribute("fileText", all);
		}
		testAll.close();
	}
	else
	{
		std::cout << "\n  view text message did not define a path attribute";
	}
	return reply;
};

//callable object added in the dispatcher for view meta data
std::function<Msg(Msg)> replyViewmeta = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command(msg.command());
	std::string path = msg.value("path");
	if (path != "")
	{
		std::string searchPath = FileSystem::Path::fileSpec(storageRoot, path);
		std::cout << searchPath << "...new path";
		FileSystem::File testAll(searchPath);
		testAll.open(FileSystem::File::in);
		if (testAll.isGood())
		{
			std::string all = testAll.readAll();
			reply.attribute("fileText", all);
		}
		testAll.close();
	}
	else
	{
		std::cout << "\n  view text message did not define a path attribute";
	}
	return reply;
};

//callable object added in the dispatcher for the connection messages
std::function<Msg(Msg)> replyConnect = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command(msg.command());
	reply.attribute("reply", "Successfully connected on communication channel");

	return reply;
};

//////test stub or executable
int main()
{
  std::cout << "\n  Testing Server Prototype";
  std::cout << "\n ==========================";
  std::cout << "\n";

  Server server(serverEndPoint, "ServerPrototype");
  server.start();

  std::cout << "\n  testing getFiles and getDirs methods";
  std::cout << "\n --------------------------------------";
  Files files = server.getFiles();
  show(files, "Files:");
  Dirs dirs = server.getDirs();
  show(dirs, "Dirs:");
  std::cout << "\n";

  std::cout << "\n  testing message processing";
  std::cout << "\n ----------------------------";
  server.addMsgProc("echo", echo);
  server.addMsgProc("getFiles", getFiles);
  server.addMsgProc("getDirs", getDirs);
  server.addMsgProc("checkin", replyCheckIn);
  server.addMsgProc("checkout", replyCheckout);
  server.addMsgProc("browse", replyBrowse);
  server.addMsgProc("view_text", replyViewtext);
  server.addMsgProc("view_meta", replyViewmeta);
  server.addMsgProc("connect", replyConnect);
  server.addMsgProc("serverQuit", echo);
  server.processMessages();
  server.msgProcThrd_.join();

  return 0;
}

