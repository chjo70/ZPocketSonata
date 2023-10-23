#pragma once


#ifndef SEL_KEYWORD_VALUE

#pragma pack( push, 1 )

// char   ���� ������ ���� NULL ���ڷ� ������ ��. �Է��� ���� ������ NULL �� ������.
// time_t ���� �ð� ������ ����. ������ ������ 0 ���� ��.
// int ���� ������ ������ -1 �� ������.
// int ���� ������ ������ -1 �� ������.
struct SEL_KEYWORD_VALUE {
	// Basic Keyword
	char classification[50];		// �������� �з�
	char writer[50];						// ������ ����

	char writer_version[20];		// ������ ���� ����

	// ����� Ű����
	char signal_id[20];					// ��ȣ ID
	char notes[100];						// Ŀ��Ʈ

	// �ð� ����
	time_t tiTime;							// MIDAS �Լ��� ���� �ð�
	time_t tiCollectionTime;		// ������ ��¥�� �ð� ���� ����

	// Tuning keyword & Collection Parameter
	double dRF;									// �߽� ���ļ� [Hz]
	double dBW;									// �߽� ���ļ��� ���� �뿪�� [Hz]
	double dSamplingPeriod;			// ���ø� [MHz]
	double dRecBW;							// ������ ���ű��� �뿪�� [Hz]
	double dLockedLO;						// LO ��, �����̸� RF+160MHz, ������ �ƴϸ� RF-160MHz
	char collector[20];					// �����Ҹ�
	char feed[20];							// ���׳� ID

	int gain_mode;							// ������ �� 0, �ڵ�(AGC)�� �� 1
	double dGain_value;						// ���� �� [dB]

	unsigned int uiNumberOfData;						// ������ ����

	int mission;
	int receiver;

};

#pragma pack( pop )

#endif