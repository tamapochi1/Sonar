using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Sonar
{
    [StructLayout(LayoutKind.Explicit)]
    public struct MicData
    {
        public void SetByte(byte[] bytes, int offset)
        {
            long1 = (long)bytes[offset + 7] << 56 | (long)bytes[offset + 6] << 48 | (long)bytes[offset + 5] << 40 | (long)bytes[offset + 4] << 32
                  | (long)bytes[offset + 3] << 24 | (long)bytes[offset + 2] << 16 | (long)bytes[offset + 1] << 8 | bytes[offset];

            long2 = (long)bytes[offset + 15] << 56 | (long)bytes[offset + 14] << 48 | (long)bytes[offset + 13] << 40 | (long)bytes[offset + 12] << 32
                  | (long)bytes[offset + 11] << 24 | (long)bytes[offset + 10] << 16 | (long)bytes[offset + 9] << 8 | bytes[offset + 8];

            long3 = (long)bytes[offset + 23] << 56 | (long)bytes[offset + 22] << 48 | (long)bytes[offset + 21] << 40 | (long)bytes[offset + 20] << 32
                  | (long)bytes[offset + 19] << 24 | (long)bytes[offset + 18] << 16 | (long)bytes[offset + 17] << 8 | bytes[offset + 16];

            long4 = (long)bytes[offset + 31] << 56 | (long)bytes[offset + 30] << 48 | (long)bytes[offset + 29] << 40 | (long)bytes[offset + 28] << 32
                  | (long)bytes[offset + 27] << 24 | (long)bytes[offset + 26] << 16 | (long)bytes[offset + 25] << 8 | bytes[offset + 24];
        }

        public int Mic1 => (int)((field1 & 0x00000000_001FFFFF) << 43 >> 43);
        public int Mic2 => (int)((field1 & 0x000003FF_FFE00000) << 22 >> 43);
        public int Mic3 => (int)((field1 & 0x7FFFFC00_00000000) <<  1 >> 43);
        public int Mic4 => (int)((field2 & 0x00000000_0FFFFF80) << 36 >> 43);
        public int Mic5 => (int)((field2 & 0x0001FFFF_F0000000) << 15 >> 43);
        public int Mic6 => (int)((field3 & 0x00000000_003FFFFE) << 42 >> 43);
        public int Mic7 => (int)((field3 & 0x000007FF_FFC00000) << 21 >> 43);
        public int Mic8 => (int)(field3 >> 43);
        public int Mic9 => (int)((field4 & 0x00000000_001FFFFF) << 43 >> 43);
        public int Mic10 => (int)((field4 & 0x000003FF_FFE00000) << 22 >> 43);
        public int Mic11 => (int)((field4 & 0x7FFFFC00_00000000) <<  1 >> 43);
        public int Mic12 => (int)((field5 & 0x0FFFFF80) << 4 >> 11);

        [FieldOffset(0)]
        public Int64 long1;
        [FieldOffset(8)]
        public Int64 long2;
        [FieldOffset(16)]
        public Int64 long3;
        [FieldOffset(24)]
        public Int64 long4;

        [FieldOffset(0)]
        public Int64 field1;
        [FieldOffset(7)]
        public Int64 field2;
        [FieldOffset(13)]
        public Int64 field3;
        [FieldOffset(21)]
        public Int64 field4;
        [FieldOffset(28)]
        public Int32 field5;
    }
}
