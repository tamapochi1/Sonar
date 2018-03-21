using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Sonar
{
    public class SonarDevice
    {
        public Serial SerialPort { get; protected set; }

        public bool IsConnected { get; protected set; }

        public int NumberOfSample { get; set; } = 16000;

        protected enum Command : byte
        {
            AcknowledgeRequest = 0x31,
            SpeakerON = 0x32,
            GetMicData = 0x33,
            GetStatus = 0x34,
            Disconnect = 0x7A
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        protected struct SendData
        {
            public Command command;
            public int data0;
            public int data1;
        }

        protected enum Response : byte
        {
            Acknowledge1 = 0x10,
            Acknowledge2 = 0xF8,
            BUSSY = 0x01,
            NA = 0x00
        }

        public enum Status
        {
            Free = Response.NA,
            Bussy = Response.BUSSY,
            Error
        }

        public SonarDevice(Serial serialPort)
        {
            SerialPort = serialPort;
        }

        public async Task Connect()
        {
            await SerialPort.SendAsync((byte)Command.AcknowledgeRequest);
            byte[] ack = await SerialPort.ReadAsync(2);
            if(ack != null && ack[0] == (byte)Response.Acknowledge1 && ack[1] == (byte)Response.Acknowledge2)
            {
                IsConnected = true;
            }

            return;
        }

        public async Task SpeakerON()
        {
            SendData sendData = new SendData() { command = Command.SpeakerON, data0 = NumberOfSample };
            await SerialPort.SendAsync(sendData, 5);
        }

        public async Task<MicData[]> GetMicData(uint KbytesToGet)
        {
            if (KbytesToGet > 1 && KbytesToGet < 1024)
            {
                byte[] data = new byte[KbytesToGet * 1024];
                // data0 : 読み出すSDRAMの先頭アドレス
                // data1 : 読み出すバイト数
                SendData sendData = new SendData() { command = Command.GetMicData };

                for (int c = 0; c < KbytesToGet; c++)
                {
                    sendData.data0 = c * 1024;
                    // 何故か1024バイトや2048バイトは受信できない
                    sendData.data1 = 1025;
                    await SerialPort.SendAsync(sendData, 9);
                    byte[] receivedData = await SerialPort.ReadAsync(1025);
                    Array.Copy(receivedData, 0, data, c * 1024, 1024);
                }

                //File.WriteAllBytes(@"micBytes", data);

                return TypeConverter.ByteToMicData(data);
            }
            else
            {
                throw new ArgumentException();
            }
        }

        public async Task<Status> GetStatus()
        {
            await SerialPort.SendAsync((byte)Command.GetStatus);
            byte[] status = await SerialPort.ReadAsync(1);
            return (Status)status[0];
        }

        public void Disconnect()
        {
            SerialPort.Send((byte)Command.Disconnect, 1);
        }
    }
}
