#include "SerialController.h"

#include <tchar.h>

SerialController::SerialController(int comNum)
{
	TCHAR com[10];
	_stprintf_s(com, 10, _T("COM%d"), comNum);

	// シリアルポートを開く
	com_port = CreateFile(com, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	SetupComm(
		com_port,	// 　通信デバイスのハンドル：CreateFile()で取得したハンドルを指定
		16384,		//   受信バッファーサイズ：　受信のバッファーサイズをバイト単位で指定
		1024		// 　送信バッファーサイズ：　送信のバッファーサイズをバイト単位で指定
	);

	//COMMTIMEOUTS timeout;

	//timeout.ReadIntervalTimeout = 5000; // 文字読込時の２も時間の全体待ち時間（msec）

	//timeout.ReadTotalTimeoutMultiplier = 0; //読込の１文字あたりの時間
	//timeout.ReadTotalTimeoutConstant = 5000; //読込エラー検出用のタイムアウト時間
	//										//(受信トータルタイムアウト) = ReadTotalTimeoutMultiplier * (受信予定バイト数) + ReadTotalTimeoutConstant 

	//timeout.WriteTotalTimeoutMultiplier = 0; //書き込み１文字あたりの待ち時間
	//timeout.WriteTotalTimeoutConstant = 500;//書き込みエラー検出用のタイムアウト時間
	//										//(送信トータルタイムアウト) = WriteTotalTimeoutMultiplier * (送信予定バイト数) + WriteTotalTimeoutConstant 

	//SetCommTimeouts(com_port, &timeout);
}

// 開いていたシリアルデバイスを破棄する
SerialController::~SerialController()
{
	// シリアルポートを閉じる
	CloseHandle(com_port);
}

void SerialController::begin(unsigned long speed)
{
	DCB dcb; // シリアルポートの構成情報が入る構造体
	GetCommState(com_port, &dcb); // 現在の設定値を読み込み

	dcb.BaudRate = speed; // 速度
	dcb.ByteSize = 8; // データ長
	dcb.Parity = NOPARITY; // パリティ
	dcb.StopBits = ONESTOPBIT; // ストップビット長
	dcb.fOutxCtsFlow = FALSE; // 送信時CTSフロー
	dcb.fRtsControl = RTS_CONTROL_DISABLE; // RTSフロー

										  // 変更した設定値を書き込み
	SetCommState(com_port, &dcb);
	DWORD err = GetLastError();
}

size_t SerialController::write(char byte)
{
	char* sentData = &byte; // 送信する1byte
	DWORD numberOfPut; // 実際に送信したbyte数

					   // ポートへ送信
	WriteFile(com_port, sentData, 1, &numberOfPut, NULL);

	return numberOfPut;
}

size_t SerialController::write(const char buf[], int len)
{
	DWORD lengthOfSent = len; // 送信するbyte数
	DWORD numberOfPut; // 実際に送信したbyte数

					   // ポートへ送信
	WriteFile(com_port, buf, lengthOfSent, &numberOfPut, NULL);

	return numberOfPut;
}

int SerialController::available()
{
	//受信データ数を調べる
	DWORD errors;
	COMSTAT comStat;
	ClearCommError(com_port, &errors, &comStat);

	int lengthOfRecieved = comStat.cbInQue; // 受信したメッセージ長を取得する

	return lengthOfRecieved;
}

int SerialController::read(char* buf)
{
	int count = available();

	//受信データがない場合は読み込まない
	if (count < 1)
	{
		return -1;
	}

	DWORD numberOfRead; // 実際に受信したバイト数

						//データ受信
	bool result = ReadFile(com_port, buf, count, &numberOfRead, NULL);

	if (result == FALSE)
	{
		return -1;
	}
	
	return numberOfRead;
}