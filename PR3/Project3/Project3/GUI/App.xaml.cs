using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace WpfApp1
{
  /// <summary>
  /// Interaction logic for App.xaml
  /// </summary>
  public partial class App : Application
  {
        private void Application_Startup(object sender, StartupEventArgs e)
        {
            WpfApp1.MainWindow mwin = new WpfApp1.MainWindow();
            if (e.Args.Length != 0)
            {
                mwin.setEndPoint(e.Args[0]);
                mwin.Show();
                mwin.testR1();
                mwin.testR2();
                mwin.testR3();
                mwin.testR4();
            }
        }
    }
}
