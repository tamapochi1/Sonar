#include "SerialController.h"

#include <tchar.h>

SerialController::SerialController(int comNum)
{
	TCHAR com[10];
	_stprintf_s(com, 10, _T("COM%d"), comNum);

	// �V���A���|�[�g���J��
	com_port = CreateFile(com, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	SetupComm(
		com_port,	// �@�ʐM�f�o�C�X�̃n���h���FCreateFile()�Ŏ擾�����n���h�����w��
		16384,		//   ��M�o�b�t�@�[�T�C�Y�F�@��M�̃o�b�t�@�[�T�C�Y���o�C�g�P�ʂŎw��
		1024		// �@���M�o�b�t�@�[�T�C�Y�F�@���M�̃o�b�t�@�[�T�C�Y���o�C�g�P�ʂŎw��
	);

	//COMMTIMEOUTS timeout;

	//timeout.ReadIntervalTimeout = 5000; // �����Ǎ����̂Q�����Ԃ̑S�̑҂����ԁimsec�j

	//timeout.ReadTotalTimeoutMultiplier = 0; //�Ǎ��̂P����������̎���
	//timeout.ReadTotalTimeoutConstant = 5000; //�Ǎ��G���[���o�p�̃^�C���A�E�g����
	//										//(��M�g�[�^���^�C���A�E�g) = ReadTotalTimeoutMultiplier * (��M�\��o�C�g��) + ReadTotalTimeoutConstant 

	//timeout.WriteTotalTimeoutMultiplier = 0; //�������݂P����������̑҂�����
	//timeout.WriteTotalTimeoutConstant = 500;//�������݃G���[���o�p�̃^�C���A�E�g����
	//										//(���M�g�[�^���^�C���A�E�g) = WriteTotalTimeoutMultiplier * (���M�\��o�C�g��) + WriteTotalTimeoutConstant 

	//SetCommTimeouts(com_port, &timeout);
}

// �J���Ă����V���A���f�o�C�X��j������
SerialController::~SerialController()
{
	// �V���A���|�[�g�����
	CloseHandle(com_port);
}

void SerialController::begin(unsigned long speed)
{
	DCB dcb; // �V���A���|�[�g�̍\����񂪓���\����
	GetCommState(com_port, &dcb); // ���݂̐ݒ�l��ǂݍ���

	dcb.BaudRate = speed; // ���x
	dcb.ByteSize = 8; // �f�[�^��
	dcb.Parity = NOPARITY; // �p���e�B
	dcb.StopBits = ONESTOPBIT; // �X�g�b�v�r�b�g��
	dcb.fOutxCtsFlow = FALSE; // ���M��CTS�t���[
	dcb.fRtsControl = RTS_CONTROL_DISABLE; // RTS�t���[

										  // �ύX�����ݒ�l����������
	SetCommState(com_port, &dcb);
	DWORD err = GetLastError();
}

size_t SerialController::write(char byte)
{
	char* sentData = &byte; // ���M����1byte
	DWORD numberOfPut; // ���ۂɑ��M����byte��

					   // �|�[�g�֑��M
	WriteFile(com_port, sentData, 1, &numberOfPut, NULL);

	return numberOfPut;
}

size_t SerialController::write(const char buf[], int len)
{
	DWORD lengthOfSent = len; // ���M����byte��
	DWORD numberOfPut; // ���ۂɑ��M����byte��

					   // �|�[�g�֑��M
	WriteFile(com_port, buf, lengthOfSent, &numberOfPut, NULL);

	return numberOfPut;
}

int SerialController::available()
{
	//��M�f�[�^���𒲂ׂ�
	DWORD errors;
	COMSTAT comStat;
	ClearCommError(com_port, &errors, &comStat);

	int lengthOfRecieved = comStat.cbInQue; // ��M�������b�Z�[�W�����擾����

	return lengthOfRecieved;
}

int SerialController::read(char* buf)
{
	int count = available();

	//��M�f�[�^���Ȃ��ꍇ�͓ǂݍ��܂Ȃ�
	if (count < 1)
	{
		return -1;
	}

	DWORD numberOfRead; // ���ۂɎ�M�����o�C�g��

						//�f�[�^��M
	bool result = ReadFile(com_port, buf, count, &numberOfRead, NULL);

	if (result == FALSE)
	{
		return -1;
	}
	
	return numberOfRead;
}