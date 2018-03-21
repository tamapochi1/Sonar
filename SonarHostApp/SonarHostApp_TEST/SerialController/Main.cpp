#include "SerialController.h"
#include <iostream>
#include <fstream>

using namespace std;

union ByteInt32 {
	char Byte[32];
	int	Int[8];
	long long LongLong[4];
};

void main(void)
{
	SerialController serial(6);
	char readBuf[16384];
	int count = 0, temp = 0;


	serial.begin(9800);

	char sendData[4096];

	//for (int i = 0; i < 4096; i++)
	//{
	//	sendData[i] = i;
	//}

	//for (int i = 0; i < 100; i++)
	//{
	//	serial.write(sendData, 4096);

	//	while (count != 4096)
	//	{
	//		temp = serial.read(readBuf);
	//		if (temp > 0)
	//			count += temp;
	//	}

	//	count = 0;
	//}

	int mic1Data[4096];
	int mic2Data[4096];

	for (int c = 0; c < 8; c++)
	{
		serial.write((char)('0' + c));

		count = 0;
		while (count < 16384)
		{
			count = serial.available();
		}

		serial.read(readBuf);

		for (int i = 0; i < 512; i++)
		{
			ByteInt32 data;
			data.Byte[0] = readBuf[i * 32];
			data.Byte[1] = readBuf[i * 32 + 1];
			data.Byte[2] = readBuf[i * 32 + 2];
			data.Byte[3] = readBuf[i * 32 + 3];
			data.Byte[4] = readBuf[i * 32 + 4];
			data.Byte[5] = readBuf[i * 32 + 5];
			data.Byte[6] = readBuf[i * 32 + 6];
			data.Byte[7] = readBuf[i * 32 + 7];

			mic1Data[512*c + i] = (data.Int[0] & 0x001FFFFF) << 11 >> 11;
			mic2Data[512 * c + i] = (data.LongLong[0] & 0x000003FFFFE00000) << 22 >> 43;
		}
	}

	ofstream fileOut1("mic1.txt");

	for (int i = 0; i < 4096; i++)
	{
		fileOut1 << mic1Data[i] << endl;
	}

	ofstream fileOut2("mic2.txt");

	for (int i = 0; i < 4096; i++)
	{
		fileOut2 << mic2Data[i] << endl;
	}
}

