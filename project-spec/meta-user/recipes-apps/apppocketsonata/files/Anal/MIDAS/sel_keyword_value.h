#pragma once


#ifndef SEL_KEYWORD_VALUE

#pragma pack( push, 1 )

// char   형은 마지막 끝에 NULL 문자로 끝나야 함. 입력할 것이 없으면 NULL 로 저장함.
// time_t 형은 시간 정보를 저장. 정보가 없으면 0 으로 함.
// int 형은 정보가 없으면 -1 로 저장함.
// int 형은 정보가 없으면 -1 로 저장함.
struct SEL_KEYWORD_VALUE {
	// Basic Keyword
	char classification[50];		// 데이터의 분류
	char writer[50];						// 생성기 장비명

	char writer_version[20];		// 생성기 버젼 정보

	// 사용자 키워드
	char signal_id[20];					// 신호 ID
	char notes[100];						// 커멘트

	// 시간 정보
	time_t tiTime;							// MIDAS 함수를 콜한 시간
	time_t tiCollectionTime;		// 수집한 날짜와 시간 정보 저장

	// Tuning keyword & Collection Parameter
	double dRF;									// 중심 주파수 [Hz]
	double dBW;									// 중심 주파수에 대한 대역폭 [Hz]
	double dSamplingPeriod;			// 샘플링 [MHz]
	double dRecBW;							// 디지털 수신기의 대역폭 [Hz]
	double dLockedLO;						// LO 값, 반전이면 RF+160MHz, 반전이 아니면 RF-160MHz
	char collector[20];					// 수집소명
	char feed[20];							// 안테나 ID

	int gain_mode;							// 수동일 때 0, 자동(AGC)일 때 1
	double dGain_value;						// 게인 값 [dB]

	unsigned int uiNumberOfData;						// 데이터 개수

	int mission;
	int receiver;

};

#pragma pack( pop )

#endif