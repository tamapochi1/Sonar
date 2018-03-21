using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32.SafeHandles;

namespace Sonar
{
    public class Serial : IDisposable
    {
        private const uint GENERIC_READ = 0x80000000;
        private const uint GENERIC_WRITE = 0x40000000;
        private const uint OPEN_EXISTING = 3;
        private const byte NOPARITY = 0;
        private const byte ONESTOPBIT = 0;

        [DllImport("kernel32.dll")]
        private static extern IntPtr CreateFile(
            string fileName,
            uint desiredAccess,
            uint shareMode,
            IntPtr securityAttributes,
            uint creationDisposition,
            uint flagsAndAttributes,
            IntPtr templateFile
            );

        [DllImport("kernel32.dll")]
        private static extern bool SetupComm(
            IntPtr file,
            uint inQueue,
            uint outQueue
            );

        [DllImport("kernel32.dll")]
        private static extern bool CloseHandle(
            IntPtr hObject
            );

        [StructLayout(LayoutKind.Sequential)]
        private struct DCB
        {
            public uint DCBlength;     /* sizeof(DCB)                     */
            public uint BaudRate;      /* Baudrate at which running       */

            //uint fBinary: 1;     /* Binary Mode (skip EOF check)    */
            //uint fParity: 1;     /* Enable parity checking          */
            //uint fOutxCtsFlow:1; /* CTS handshaking on output       */
            //uint fOutxDsrFlow:1; /* DSR handshaking on output       */
            //uint fDtrControl:2;  /* DTR Flow control                */
            //uint fDsrSensitivity:1; /* DSR Sensitivity              */
            //uint fTXContinueOnXoff: 1; /* Continue TX when Xoff sent */
            //uint fOutX: 1;       /* Enable output X-ON/X-OFF        */
            //uint fInX: 1;        /* Enable input X-ON/X-OFF         */
            //uint fErrorChar: 1;  /* Enable Err Replacement          */
            //uint fNull: 1;       /* Enable Null stripping           */
            //uint fRtsControl:2;  /* Rts Flow control                */
            //uint fAbortOnError:1; /* Abort all reads and writes on Error */
            //uint fDummy2:17;     /* Reserved                        */
            public uint f; // 32bits

            public ushort Reserved;    /* Not currently used              */
            public ushort XonLim;      /* Transmit X-ON threshold         */
            public ushort XoffLim;     /* Transmit X-OFF threshold        */
            public byte ByteSize;      /* Number of bits/byte, 4-8        */
            public byte Parity;        /* 0-4=None,Odd,Even,Mark,Space    */
            public byte StopBits;      /* 0,1,2 = 1, 1.5, 2               */
            public char XonChar;       /* Tx and Rx X-ON character        */
            public char XoffChar;      /* Tx and Rx X-OFF character       */
            public char ErrorChar;     /* Error replacement char          */
            public char EofChar;       /* End of Input character          */
            public char EvtChar;       /* Received Event character        */
            public ushort Reserved1;   /* Fill for now.                   */
        }

        [DllImport("kernel32.dll")]
        private static extern bool GetCommState(
            IntPtr file,
            out DCB DCB
            );

        [DllImport("kernel32.dll")]
        private static extern bool SetCommState(
            IntPtr file,
            ref DCB DCB
            );

        [DllImport("kernel32.dll")]
        private static extern bool WriteFile(
            IntPtr file,
            IntPtr buffer,
            uint nNumberOfBytesToWrite,
            out uint numberOfBytesWritten,
            IntPtr overlapped
            );

        [StructLayout(LayoutKind.Sequential)]
        private struct COMSTAT
        {
            //DWORD fCtsHold : 1;
            //DWORD fDsrHold : 1;
            //DWORD fRlsdHold : 1;
            //DWORD fXoffHold : 1;
            //DWORD fXoffSent : 1;
            //DWORD fEof : 1;
            //DWORD fTxim : 1;
            //DWORD fReserved : 25;
            public uint f;  // 32bits

            public uint cbInQue;
            public uint cbOutQue;
        }

        [DllImport("kernel32.dll")]
        private static extern bool ClearCommError(
            IntPtr file,
            out uint errors,
            out COMSTAT lpStat
            );

        [DllImport("kernel32.dll")]
        private static extern bool ReadFile(
            IntPtr file,
            IntPtr buffer,
            uint nNumberOfBytesToRead,
            out uint numberOfBytesRead,
            IntPtr overlapped
            );

        private bool disposed = false;
        private SafeFileHandle safeHandle;
        private DCB dcb;
        private byte[] readBuffer = new byte[16384];
        private GCHandle readBufferHandle;
        private static object sendingLock = new object();
        private static object readingLock = new object();

        public string Name { get; private set; }

        public uint NumberOfReceivedBytes
        {
            get
            {
                if (safeHandle.IsClosed) return 0;
                uint errorCount;
                COMSTAT stat;
                if (!ClearCommError(safeHandle.DangerousGetHandle(), out errorCount, out stat))
                    throw new Exception(Name + " のエラーをクリアできませんでした。");
                return stat.cbInQue;
            }
        }

        public uint NumberOfSendingBytes
        {
            get
            {
                if (safeHandle.IsClosed) return 0;
                uint errorCount;
                COMSTAT stat;
                if (!ClearCommError(safeHandle.DangerousGetHandle(), out errorCount, out stat))
                    throw new Exception(Name + " のエラーをクリアできませんでした。");
                return stat.cbOutQue;
            }
        }

        public Serial(string name)
        {
            IntPtr handle = CreateFile(name, GENERIC_READ | GENERIC_WRITE, 0, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            if ((int)handle == -1)
                throw new Exception(name + " を開けませんでした。");

            safeHandle = new SafeFileHandle(handle, true);

            if (!SetupComm(safeHandle.DangerousGetHandle(), 16384, 1024))
                throw new Exception(name + " のバッファサイズを設定できませんでした。");

            if (!GetCommState(safeHandle.DangerousGetHandle(), out dcb))
                throw new Exception(name + " の状態を取得できませんでした。");

            dcb.BaudRate = 9800;
            dcb.f = 0x00000001; // Binary Mode is true
            dcb.ByteSize = 8;
            dcb.Parity = NOPARITY;
            dcb.StopBits = ONESTOPBIT;

            if (!SetCommState(safeHandle.DangerousGetHandle(), ref dcb))
            {
                // エラーコード31が発生する。無視しても問題なし。Sonar側のファームに問題あり？仮想COMだとそもそも設定の意味なし？
                //throw new Exception(name + " の状態を設定できませんでした。");
            }

            // エラーをクリア
            uint dummy = NumberOfReceivedBytes;

            Name = name;
            readBufferHandle = GCHandle.Alloc(readBuffer, GCHandleType.Pinned);
        }

        public async Task SendAsync(object data, uint bytesInData)
        {
            await Task.Run(() =>
            {
                Send(data, bytesInData);
            });
        }

        public async Task SendAsync(byte data)
        {
            await Task.Run(() =>
            {
                Send(data, 1);
            });
        }

        public void Send(object data, uint bytesInData)
        {
            if (safeHandle.IsClosed) return;

            lock (sendingLock)
            {
                IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(data));
                Marshal.StructureToPtr(data, ptr, false);

                bool result = WriteFile(safeHandle.DangerousGetHandle(), ptr, bytesInData, out uint written, IntPtr.Zero);
                while (NumberOfSendingBytes != 0) { }

                Marshal.FreeHGlobal(ptr);

                if (!result || written != bytesInData)
                    throw new Exception(Name + " にデータを送信できませんでした。");
            }
        }

        public async Task<byte[]> ReadAsync(int count)
        {
            return await Task.Run(() =>
            {
                lock (readingLock)
                {
                    while (NumberOfReceivedBytes < count) { }
                    return ReadBytes();
                }
            });
        }

        public string ReadStrings()
        {
            if (safeHandle.IsClosed) return null;

            if (!ReadFile(safeHandle.DangerousGetHandle(), readBufferHandle.AddrOfPinnedObject(), NumberOfReceivedBytes, out uint read, IntPtr.Zero))
                throw new Exception(Name + " からデータを受信できませんでした。");

            string buffer = null;

            if (read != 0)
            {
                for(int i = 0; i < read; i++)
                {
                    buffer += (char)readBuffer[i];
                }
            }

            return buffer;
        }

        public byte[] ReadBytes()
        {
            if (safeHandle.IsClosed) return null;

            if (!ReadFile(safeHandle.DangerousGetHandle(), readBufferHandle.AddrOfPinnedObject(), NumberOfReceivedBytes, out uint read, IntPtr.Zero))
                throw new Exception(Name + " からデータを受信できませんでした。");

            byte[] buffer = null;

            if(read != 0)
            {
                buffer = new byte[read];
                Array.Copy(readBuffer, buffer, read);
            }

            return buffer;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposed) return;

            if (disposing)
            {
                if (safeHandle != null) safeHandle.Dispose();
                if (readBufferHandle.IsAllocated) readBufferHandle.Free();
            }

            disposed = true;
        }
    }
}
