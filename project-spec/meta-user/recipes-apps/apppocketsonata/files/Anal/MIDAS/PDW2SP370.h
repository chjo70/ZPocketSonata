#pragma once

#include "PDWIQ.h"

#define	LIBRARY_NAME				"Default.Mas"
#define	BLOCK_OF_PDWDATA		(200)								// MAX_OF_PDW_DATA 값과 동일 해야 함

#define PDW_PHASE_OF_SP370	4

#define _VALID							1
#define _INVALID						0

typedef struct {
	unsigned short uiSignalInterceptNumer;

	unsigned char uiReserved1[4];
	unsigned char uiReserved2[14];

	unsigned char	ucIndexOffsetInBytes;

	unsigned char uiReserved3;
	unsigned char uiReserved4[2];

	char szMasterLibraryName[48];
	unsigned int uiPadbytes[2];
} SELSP350_PDWHEADER;

typedef union {
	unsigned int wpdw[PDW_PHASE_OF_SP370];

	struct {
		// 1번째 Phase
		unsigned int usTOA;

		// 2번째 Phase
		unsigned short ucAmp								: 8;

		unsigned short _notused2						: 3;
		unsigned short usPMOPFlag						: 1;
		unsigned short usPOPFlag						: 1;
		unsigned short usPOPPedFlag					: 1;
		unsigned short _notused3						: 2;

		unsigned short _notused1						: 3;
		unsigned short uiLowAOA							: 5;

		unsigned short uiHighAOA						: 7;
		unsigned short uiAOAInvalid					: 1;

		// 3번째 Phase
		unsigned short usPulseSource				: 5;
		unsigned short usIFMValid						: 1;						// 주파수 Valid
		unsigned short _notused4						: 1;						// FMOP Status
		unsigned short usSignalCenterStatus	: 1;						// 신호 중심 상태

		unsigned short usFreqFraction				: 8;						// 주파수 소수 단위 [3.90625 kHz]

		unsigned short usFreq								: 16;						// 주파수 [1 MHz]

		// 4번째 Phase
		unsigned short usLowFMOP						: 8;						//  하위 FMOP 주파수
		unsigned short usHighFMOP						: 8;						//  상위 FMOP 주파수

		unsigned short usPW									:15;						// 펄스폭 [40ns]
		unsigned short usCW									: 1;						// CW flag

	} x;
} SELSP350_PDWWORDS;


class CPDW2SP370
{
public:
	SELSP350_PDWHEADER m_stPDWHeader;

	unsigned int m_nPDWWord;
	SELSP350_PDWWORDS m_stPDWWord[BLOCK_OF_PDWDATA];

private:
public:
	void Init();
	bool MakeHeader();
	bool TransferPDW2SP370( SRXPDWDataRGroup *pS_EL_PDW_DATA, int iRecords );


public:
	CPDW2SP370(void);
	~CPDW2SP370(void);
};
