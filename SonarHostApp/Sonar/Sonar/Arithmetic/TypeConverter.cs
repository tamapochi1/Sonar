using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sonar
{
    public class TypeConverter
    {
        public static MicData[] ByteToMicData(byte[] source)
        {
            int numberOfSamples = source.Length / 32;
            MicData[] result = new MicData[numberOfSamples];

            for(int s = 0; s < numberOfSamples; s++)
            {
                result[s].SetByte(source, s * 32);
            }

            return result;
        }
    }
}
