using System;
using System.Collections.Generic;
using System.IO.Ports;
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
using System.Runtime.InteropServices;

namespace SonarHostApp_TEST
{
    public class Vector3
    {
        public float x;
        public float y;
        public float z;
    }

    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        [StructLayout(LayoutKind.Explicit)]
        struct MicData
        {
            public void SetByte(byte[] bytes)
            {
                byte0 = bytes[0];
                byte1 = bytes[1];
                byte2 = bytes[2];
            }

            public int Mic1 => long1 & 0x001FFFFF;

            [FieldOffset(0)]
            public byte byte0;

            [FieldOffset(1)]
            public byte byte1;

            [FieldOffset(2)]
            public byte byte2;

            [FieldOffset(0)]
            public Int32 long1;
        }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void ActionButton_Click(object sender, RoutedEventArgs e)
        {
            Vector3 R1 = new Vector3();
            Vector3 V = new Vector3();
            int rui = -1;
            int rui1 = 1;

            for(int i = 0; i < 1000000; i++)
            {
                Calculation_delta_K_remake(R1, V, rui, rui1);

                float a = 0f;

                for (int j = 0; j < 100; j++)
                {
                    a = 20.156354f * j;
                }

                Math.Sqrt(a);
                Math.Sqrt(a);
            }
        }

        void Calculation_delta_K_remake(Vector3 R1, Vector3 V, int rui, int rui1)
        {
            Vector3 direction = new Vector3();
            float[] K_parameters = new float[6];

            direction.x = R1.x - V.x;
            direction.y = R1.y - V.y;
            direction.z = R1.z - V.z;
            float length = (float)Math.Sqrt(direction.x * direction.x + direction.y * direction.y + direction.z + direction.z);
            // K値算出
            K_parameters[0] = (float)(rui1 * Math.Atan2(direction.y * direction.z, direction.x * length));
            K_parameters[1] = (float)(rui * Math.Log(length + direction.z));
            K_parameters[2] = (float)(rui * Math.Log(length + direction.y));
            K_parameters[3] = (float)(rui1 * Math.Atan2(direction.x * direction.z, direction.y * length));
            K_parameters[4] = (float)(rui * Math.Log(length + direction.x));
            K_parameters[5] = (float)(rui1 * Math.Atan2(direction.y * direction.x, direction.z * length));
            return;
        }
    }
}
