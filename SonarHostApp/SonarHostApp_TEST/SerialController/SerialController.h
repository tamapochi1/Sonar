#pragma once

#include <Windows.h>

class SerialController
{
	HANDLE com_port;

public:
	// arg1 : COM�|�[�g�̔ԍ����w��
	// �w�肵���V���A���f�o�C�X���J��
	SerialController(int comNum);

	// �J���Ă����V���A���f�o�C�X��j������
	~SerialController();

	// arg1 : �`�����x[bps]
	// �V���A���ʐM�̏�����
	void begin(unsigned long speed);

	// arg1 : ���M����1byte
	// 1byte�̃f�[�^�𑗐M����
	// ���ۂɑ��M����byte����Ԃ�
	virtual size_t write(char byte);

	// arg1 : ���M����byte��
	// arg2 : ���M����byte��
	// ����byte�̃f�[�^����x�ɑ��M����
	// ���ۂɑ��M����byte����Ԃ�
	virtual size_t write(const char buf[], int len);

	// ��M�o�b�t�@�ɗ��܂���byte����Ԃ�
	virtual int available();

	// ���s�����ꍇ-1��Ԃ�
	virtual int read(char* buf);
};