using System;
using System.Collections.Generic;
using System.IO;
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

namespace Sonar
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        public Serial serialPort;
        public SonarDevice sonar;

        public MainWindow()
        {
            serialPort = new Serial("COM6");
            sonar = new SonarDevice(serialPort);

            InitializeComponent();
        }

        private async void Window_Initialized(object sender, EventArgs e)
        {
            await sonar.Connect();
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            if (serialPort != null)
            {
                sonar.Disconnect();
                serialPort.Dispose();
            }

            App.Current.Shutdown();
        }

        private async void PulseButton_Click(object sender, RoutedEventArgs e)
        {
            PulseButton.IsEnabled = false;
            await sonar.SpeakerON();
            while(await sonar.GetStatus() == SonarDevice.Status.Bussy) { }
            MicData[] data = await sonar.GetMicData(500);
            PulseButton.IsEnabled = true;

            //string writtenData = null;
            //foreach (MicData m in data)
            //{
            //    writtenData += m.Mic1.ToString() + " ";
            //    writtenData += m.Mic2.ToString() + " ";
            //    writtenData += m.Mic3.ToString() + " ";
            //    writtenData += m.Mic4.ToString() + " ";
            //    writtenData += m.Mic5.ToString() + " ";
            //    writtenData += m.Mic6.ToString() + " ";
            //    writtenData += m.Mic7.ToString() + " ";
            //    writtenData += m.Mic8.ToString() + " ";
            //    writtenData += m.Mic9.ToString() + " ";
            //    writtenData += m.Mic10.ToString() + " ";
            //    writtenData += m.Mic11.ToString() + " ";
            //    writtenData += m.Mic12.ToString() + "\n";
            //}
            //File.WriteAllText("micData.txt", writtenData);
        }
    }
}
