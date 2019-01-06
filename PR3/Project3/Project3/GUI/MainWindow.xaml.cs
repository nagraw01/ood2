///////////////////////////////////////////////////////////////////////
// MainWindow.xaml.cs - GUI for Project3                     //
// ver 1.0                                                           //
// Author: Nishant Agrawal, email-nagraw01@syr.edu
// SUID: 595031520
// Application: CSE681 - OOD, Project 3                 //
// Environment: C# console                                            //
////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package provides a WPF-based GUI for Project3HelpWPF demo.  It's 
 * responsibilities are to:
 * - Provide a display of directory contents of a remote ServerPrototype.
 * - It provides a subdirectory list and a filelist for the selected directory.
 * - You can navigate into subdirectories by double-clicking on subdirectory
 *   or the parent directory, indicated by the name "..".
 *    * Public Interface
 * ----------------
 * setEndPoint();
 * testR1();
 * testR2();
 * testR3();
 * testR4();
 *   
 *   
 * Required Files:
 * ---------------
 * Mainwindow.xaml, MainWindow.xaml.cs
 * App.xaml, App.xaml.cs
 * Translater.dll
 * 
 * Maintenance History:
 * --------------------
 * ver 2.0 : 10 Apr 2018
 * - first release
 * - Several early prototypes were discussed in class. Those are all superceded
 *   by this package.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;
using MsgPassingCommunication;

namespace WpfApp1
{
    public partial class MainWindow : Window
    {
    
    //function to set the endpoint from the command line argument for multiple clients
    public void setEndPoint(string port)
    {
        int x = Int32.Parse(port);
        endPoint_ = new CsEndPoint();
        endPoint_.machineAddress = "localhost";
        endPoint_.port = x;
    }

    private Stack<string> pathStack_ = new Stack<string>();
    private Translater translater;
    private CsEndPoint endPoint_;
    private Thread rcvThrd = null;
    private Dictionary<string, Action<CsMessage>> dispatcher_ 
      = new Dictionary<string, Action<CsMessage>>();

    public MainWindow()
    {
        InitializeComponent();
    }

    //----< process incoming messages on child thread >----------------
    private void processMessages()
    {
      ThreadStart thrdProc = () => {
        while (true)
        {
          CsMessage msg = translater.getMessage();
          string msgId = msg.value("command");
          if (dispatcher_.ContainsKey(msgId))
            dispatcher_[msgId].Invoke(msg);
        }
      };
      rcvThrd = new Thread(thrdProc);
      rcvThrd.IsBackground = true;
      rcvThrd.Start();
    }
    //----< function dispatched by child thread to main thread >-------

    private void clearDirs()
    {
      br_dirs.Items.Clear();
    }
    //----< function dispatched by child thread to main thread >-------

    private void addDir(string dir)
    {
      br_dirs.Items.Add(dir);
    }
    //----< function dispatched by child thread to main thread >-------

    private void insertParent()
    {
      br_dirs.Items.Insert(0, "..");
    }
    //----< function dispatched by child thread to main thread >-------

    private void clearFiles()
    {
      br_files.Items.Clear();
    }
    //----< function dispatched by child thread to main thread >-------

    private void addFile(string file)
    {
      br_files.Items.Add(file);
    }
    //----< add client processing for message with key >---------------

    private void addClientProc(string key, Action<CsMessage> clientProc)
    {
      dispatcher_[key] = clientProc;
    }

    //----< load check-in processing into dispatcher dictionary >------
    private void DispatcherCheckInReply()
    {
    Action<CsMessage> checkInReply = (CsMessage rcvMsg) =>
    {

        var enumer = rcvMsg.attributes.GetEnumerator();
        while (enumer.MoveNext())
        {
            string key = enumer.Current.Key;
            if (key.Contains("reply"))
            {
                Action<String> doFile = (String rep) =>
                {
                    ci_lstBoxFilesForCheckin.Items.Insert(0, rep);
                    statusBarText.Text = "Received " + ci_lstBoxFilesForCheckin.Items.Count + " messages";

                };
                Dispatcher.Invoke(doFile, new Object[] { enumer.Current.Value });
            }
        }
    };
    addClientProc("checkin", checkInReply);
    }

    //----< load check-out processing into dispatcher dictionary >------
    private void DispatcherCheckOutReply()
    {
        Action<CsMessage> checkOutReply = (CsMessage rcvMsg) =>
        {

            var enumer = rcvMsg.attributes.GetEnumerator();
            while (enumer.MoveNext())
            {
                string key = enumer.Current.Key;
                if (key.Contains("reply"))
                {
                    Action<String> doFile = (String rep) =>
                    {
                        co_lstBoxFilesForCheckin.Items.Insert(0, rep);
                        statusBarText.Text = "Received " + co_lstBoxFilesForCheckin.Items.Count + " messages";

                    };
                    Dispatcher.Invoke(doFile, new Object[] { enumer.Current.Value });
                }
            }
        };
        addClientProc("checkout", checkOutReply);
    }

    //----< load view text processing into dispatcher dictionary >------
    private void DispatcherViewFile()
    {
        Action<CsMessage> viewfile = (CsMessage rcvMsg) =>
        {

            var enumer = rcvMsg.attributes.GetEnumerator();
            while (enumer.MoveNext())
            {
                string key = enumer.Current.Key;
                if (key.Contains("fileText"))
                {
                    Action<String> doFile = (String rep) =>
                    {
                            
                        vf_text.Text = rep;
                        statusBarText.Text = "Received File Text";

                    };
                    Dispatcher.Invoke(doFile, new Object[] { enumer.Current.Value });
                }
            }
        };
        addClientProc("view_text", viewfile);
    }

    //----< load view meta data processing into dispatcher dictionary >------
    private void DispatcherViewMeta()
    {
        Action<CsMessage> viewmeta = (CsMessage rcvMsg) =>
        {

            var enumer = rcvMsg.attributes.GetEnumerator();
            while (enumer.MoveNext())
            {
                string key = enumer.Current.Key;
                if (key.Contains("fileText"))
                {
                    Action<String> doFile = (String rep) =>
                    {
                        vm_text.Text = rep;
                        statusBarText.Text = "Received File Meta";

                    };
                    Dispatcher.Invoke(doFile, new Object[] { enumer.Current.Value });
                }
            }
        };
        addClientProc("view_meta", viewmeta);
    }

    //----< load connection processing into dispatcher dictionary >------
    private void DispatcherConnect()
    {
        Action<CsMessage> connect = (CsMessage rcvMsg) =>
        {
            var enumer = rcvMsg.attributes.GetEnumerator();
            while (enumer.MoveNext())
            {
                string key = enumer.Current.Key;
                if (key.Contains("reply"))
                {
                    Action<String> doFile = (String rep) =>
                    {
                        con_listBox.Items.Insert(0, rep);
                        statusBarText.Text = "Received " + con_listBox.Items.Count + " messages";
                    };
                    Dispatcher.Invoke(doFile, new Object[] { enumer.Current.Value });
                }
            }
        };
        addClientProc("connect", connect);
    }

    //----< load browse processing into dispatcher dictionary >------
    private void DispatcherBrowse()
    {
        Action<CsMessage> browse = (CsMessage rcvMsg) =>
        {
            Action clrDirs = () =>
            {
                clearDirs();
            };
            Dispatcher.Invoke(clrDirs, new Object[] { });
            Action clrFiles = () =>
            {
                clearFiles();
            };
            Dispatcher.Invoke(clrFiles, new Object[] { });
            var enumer = rcvMsg.attributes.GetEnumerator();
            while (enumer.MoveNext())
            {
                string key = enumer.Current.Key;
                if (key.Contains("dir"))
                {
                    Action<string> doDir = (string dir) =>
                    {
                        addDir(dir);
                    };
                    Dispatcher.Invoke(doDir, new Object[] { enumer.Current.Value });
                }
                if (key.Contains("file"))
                {
                    Action<string> doFile = (string file) =>
                    {
                        addFile(file);
                    };
                    Dispatcher.Invoke(doFile, new Object[] { enumer.Current.Value });
                }
            }
            Action insertUp = () =>
            {
                insertParent();
            };
            Dispatcher.Invoke(insertUp, new Object[] { });
        };
        addClientProc("browse", browse);
    }


    //----< load all dispatcher processing >---------------------------

    private void loadDispatcher()
    {

      DispatcherBrowse();
        DispatcherCheckInReply();
        DispatcherCheckOutReply();
        DispatcherViewFile();
        DispatcherViewMeta();
        DispatcherConnect();
    }

    //----< start Comm, load dispatcher and start processing incoming messages

    private void Window_Loaded(object sender, RoutedEventArgs e)
    {
      translater = new Translater();
      translater.listen(endPoint_);

      processMessages();

      loadDispatcher();
    }

    //function for doing the check-in functionality, called by test case and button-click
    private void func_checkin_but()
    {
        CsEndPoint serverEndPoint = new CsEndPoint();
        serverEndPoint.machineAddress = "localhost";
        serverEndPoint.port = 8080;
        CsMessage msg = new CsMessage();
        msg.add("to", CsEndPoint.toString(serverEndPoint));
        msg.add("from", CsEndPoint.toString(endPoint_));
        msg.add("command", "checkin");
        translater.postMessage(msg);
    }
    //function for doing the check-out functionality, called by test case and button-click
    private void func_checkout_but()
    {
        CsEndPoint serverEndPoint = new CsEndPoint();
        serverEndPoint.machineAddress = "localhost";
        serverEndPoint.port = 8080;
        CsMessage msg = new CsMessage();
        msg.add("to", CsEndPoint.toString(serverEndPoint));
        msg.add("from", CsEndPoint.toString(endPoint_));
        msg.add("command", "checkout");

        translater.postMessage(msg);
    }

    //function for doing the browse functionality, called by test case and button-click
    private void func_browse_but()
    {
        CsEndPoint serverEndPoint = new CsEndPoint();
        serverEndPoint.machineAddress = "localhost";
        serverEndPoint.port = 8080;
        CsMessage msg = new CsMessage();
        msg.add("to", CsEndPoint.toString(serverEndPoint));
        msg.add("from", CsEndPoint.toString(endPoint_));
        msg.add("command", "browse");

        translater.postMessage(msg);
    }

    //function for doing the View Text functionality, called by test case and button-click
    private void func_viewtext_but()
    {
        CsEndPoint serverEndPoint = new CsEndPoint();
        serverEndPoint.machineAddress = "localhost";
        serverEndPoint.port = 8080;
        CsMessage msg = new CsMessage();
        msg.add("to", CsEndPoint.toString(serverEndPoint));
        msg.add("from", CsEndPoint.toString(endPoint_));
        msg.add("command", "view_text");
        msg.add("path", vf_path.Text);

        translater.postMessage(msg);
    }

    //function for doing the view Meta data functionality, called by test case and button-click
    private void func_viewmetadata_but()
    {
        CsEndPoint serverEndPoint = new CsEndPoint();
        serverEndPoint.machineAddress = "localhost";
        serverEndPoint.port = 8080;
        CsMessage msg = new CsMessage();
        msg.add("to", CsEndPoint.toString(serverEndPoint));
        msg.add("from", CsEndPoint.toString(endPoint_));
        msg.add("command", "view_meta");
        msg.add("path", vm_path.Text);

        translater.postMessage(msg);
    }

    //function for doing the Connection functionality, called by test case and button-click
    private void func_connect_but()
    {
        CsEndPoint serverEndPoint = new CsEndPoint();
        serverEndPoint.machineAddress = "localhost";
        serverEndPoint.port = 8080;
        CsMessage msg = new CsMessage();
        msg.add("to", CsEndPoint.toString(serverEndPoint));
        msg.add("from", CsEndPoint.toString(endPoint_));
        msg.add("command", "connect");

        translater.postMessage(msg);
    }

    // -----< Check-in button click event handler >-----------------------------------
    private void Button_CheckIn(object sender, RoutedEventArgs e)
    {
        func_checkin_but();
    }

    // -----< Check-out button click event handler >-----------------------------------
    private void Button_Checkout(object sender, RoutedEventArgs e)
    {
        func_checkout_but();
    }

    // -----< Browse button click event handler >-----------------------------------
    private void Button_Browse(object sender, RoutedEventArgs e)
    {
        func_browse_but();
    }

    // -----< View File button click event handler >-----------------------------------
    private void Button_ViewFile(object sender, RoutedEventArgs e)
    {
        func_viewtext_but();
    }

    // -----< View Metadata button click event handler >-----------------------------------
    private void Button_ViewMeta(object sender, RoutedEventArgs e)
    {
        func_viewmetadata_but();
    }

    // -----< Connect button click event handler >-----------------------------------
    private void Button_Connect(object sender, RoutedEventArgs e)
    {
        func_connect_but();
    }

    ///////////////////////////////////////////////////////////////////////
    // test suite functions

    //----< demo requirement #1 >------------------------------------------

    public void testR1()
    {
        Console.WriteLine("\n\n Demonstration of Requirement 1:\n======================================================== \n");
        Console.WriteLine("This project only uses Visual Studio 2017 and the standard C++ libraries, as provided in the ECS computer labs.Net Windows Presentation Foundation framework and C++'\'CLI have also been used for the graphical part of Client.");

    }

    //----< demo requirement #2 >------------------------------------------

    public void testR2()
    {
        Console.WriteLine("\n\nDemonstrating Requirement #2:\n======================================================== \n");
        Console.WriteLine("Provide an asynchronous message-passing communication channel, used for all communication between Clients and the Remote Repository Server. The channel uses HTTP style message class, (an unordered map) for sending requests, receiving replies, and transferring files between Clients and Server.");
        Console.WriteLine("\nClient Process #1 at port: "+ endPoint_.port+"\n----------------------------------\n");
    }

    //----< demo first part of requirement #3 >----------------------------

    public void testR3()
    {
        Console.WriteLine("\n\nDemonstrating Requirement #3:\n======================================================== \n");
        Console.WriteLine("Shall provide a Client graphical user interface that supports tabs for the views:"+
                            "Connecting to Servers"+
                            "check -in"+
                            "check -out"+
                            "browsing specified package descriptions"+
                            "viewing full file text"+
                            "viewing file metadata");

        Console.WriteLine("\nCheck-in sends message to server and gets a reply, displayed in listBox and status bar. \n");
        func_checkin_but();
        Console.WriteLine("\nCheck-out also sends message to server and gets a reply, displayed in listBox and status bar. \n");
        func_checkout_but();
        Console.WriteLine("\nConnect sends a connect message to server and gets confirmation on connection, displayed in listBox and status bar. \n");
        func_connect_but();
        Console.WriteLine("\n Browse sends message to server and gets all files and directories as reply message attributes. \n");
        func_browse_but();
        Console.WriteLine("\nView Text sends message to server and gets the file text for the path provided as string, displayed in text box. \n");
        func_viewtext_but();
        Console.WriteLine("\nView Metadata also does the same as View Text as there is no NoSqlDb to store the metadata currently. \n");
        func_viewmetadata_but();
    }

    //----< demo second part of requirement #4 >---------------------------
    public void testR4()
    {
        Console.WriteLine("\n\nDemonstrating Requirement #4:\n======================================================== \n");
        Console.WriteLine("Shall include an automated unit test suite that demonstrates you meet all the requirements of this project2. This set of tests shall run without user intervention when your application starts.");

    }

    }
}
