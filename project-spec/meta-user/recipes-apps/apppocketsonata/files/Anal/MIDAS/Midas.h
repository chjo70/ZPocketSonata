/*!
 * @file      Midas.h
 * @brief     
 * @exception MIDAS Blue File Format 헤더 파일
 * @author    조철희
 * @date      2014-11-22 오후 8:19 
 * @warning   
 */

#pragma once

#include <string.h>
#include <vector>

using namespace std;

#include "../OFP_Main.h"

#include "PDWIQ.h"

#define XOR_I_DATA			(0x8A5A)
#define XOR_Q_DATA			(0x8A5A)


#include "RawFile.h"



//#include "./PDW2SP370.h"


enum EnumSCDataType
{
	E_EL_SCDT_UNKNOWN		= 0x00,
	E_EL_SCDT_IF				= 0x01,		//IF
	E_EL_SCDT_PDW				= 0x02,		//PDW
	E_EL_SCDT_IQ				= 0x04,		//IQ
	E_EL_SCDT_SPECTRUM	= 0x08,		//스펙트럼
	E_EL_SCDT_LOB				= 0x10,		//위협데이터
	E_EL_SCDT_PRF				= 0x20,		//PRF
	E_EL_SCDT_LOG				= 0x40,		// 운용 로그
	//E_EL_SCDT_SAMPLING	= 0x80,		//Sampling

	E_EL_SCDT_PDW2SP370	= 0x88,		//PDWfmf SP350변환  

	E_EL_SCDT_ALL = -1					// 검색할 때 인자를 주기 위한 것
};


#define HEADER_CONTROL_BLOCK_SIZE		(0x200)
#define EXTENDED_HEADER_SIZE				(0x400)

#define BYTE_IN_A_BLOCK							(512)

// Extended Header에 대한 키워드 기본값 정의
#define DEFAULT_CLASSIFICATION_VALUE	"UNCLASSIFIED"
#define DEFAULT_WRITER_VALUE					"Night OWL IF Recorder SW"						// 타체계 연동하려면 반드시 이 값으로 설정해야 함.
#define DEFAULT_WRITER_1_VALUE				"701-BaekDu IF Recoder Storage"				// IF 데이터
#define DEFAULT_WRITER_2_VALUE				"701-BaekDu IQ Receiver"							// IQ 데이터
#define DEFAULT_WRITER_3_VALUE				"701-BaekDu PRFTone Receiver"					// PRF톤 데이터
#define DEFAULT_WRITER_VERSION_VALUE	"1.0"
#define DEFAULT_COLLECTOR_VALUE				"AIR-1"
#define DEFAULT_FEED_VALUE						"DR ANT."
#define DEFAULT_SIGNAL_ID_VALUE				"99999"
#define DEFAULT_NOTES_VALUE						"Reference"
#define DEFAULT_SAMPLINGRATE_VALUE		(200000000.)				// 200 MS/s, 711

// PDW 레코드 정의 : TOA, FREQ, DTOA, PA, PW, DOA 등
#define MAX_SUBRECORDS_OF_PDWDATA			(6)

/**
 * @def       MAX_OF_KEYWORD
 * @brief     키워드에 대한 최대 길이
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
#define MAX_OF_KEYWORD		(99999)												

// MIDAS 변환 파일에 대한 버젼 정보 저장
//#define HEADER_VER_IF		"1.0"
#define DEFAULT_HEADER_VER  "1.0"

// MIDAS 변환 파일에 대한 파일 헤더 정보
#define HEADER_IO_IF		"Night OWL IF Recorder SW"
#define HEADER_IO_PDW		"PLATINUM"

//////////////////////////////////////////////////////////////////////////
// MIDAS File types
// 

#define MIDAS_FILE_TYPE_1000	1000		// Generic one-dimensional scalar data
#define MIDAS_FILE_TYPE_1001	1001		// Uniformly sampled amplitude data
#define MIDAS_FILE_TYPE_1002	1002		// Time-of-arrival (TOA) data
#define MIDAS_FILE_TYPE_1003	1003		// Histogram data
#define MIDAS_FILE_TYPE_1004	1004		// Uniformly sampled asynchronous burst data
#define MIDAS_FILE_TYPE_1005	1005		// Multi-point data
#define MIDAS_FILE_TYPE_1200	1200		// Packetized one-dimensional scalar data
#define MIDAS_FILE_TYPE_1999	1999		// Records of connected points (e.g., mapping polygons or complex data)
#define MIDAS_FILE_TYPE_2000	2000		// Generic two-dimensional scalar data
#define MIDAS_FILE_TYPE_2001	2001		// Frame data (e.g., spectra vs. time)
#define MIDAS_FILE_TYPE_2004	2004		// Burst with uniform intra- and inter-burst sampling
#define MIDAS_FILE_TYPE_2200	2200		// Packetized two-dimensional scalar data
#define MIDAS_FILE_TYPE_3000	3000		// Record structured data (non-homogeneous, limited to 26 subrecords)
#define MIDAS_FILE_TYPE_3999	3999		// Records indicating a set of parameters
#define MIDAS_FILE_TYPE_4000	4000		// Key/value pairs
#define MIDAS_FILE_TYPE_5000	5000		// Record structured data (non-homogeneous, limited to 14 components) plus system	modeling parameters
#define MIDAS_FILE_TYPE_5001	5001		// State vector information
#define MIDAS_FILE_TYPE_5010	5010		// Geodetic reference positions
#define MIDAS_FILE_TYPE_6000	6000		// Record structured data (non-homogeneous)
#define MIDAS_FILE_TYPE_6001	6001		// Uniformly sampled record data
#define MIDAS_FILE_TYPE_6002	6002		// Multi-point record data
#define MIDAS_FILE_TYPE_6003	6003		// Time-based data
#define MIDAS_FILE_TYPE_6004	6004		// Time-based data associated with a type 1004 burst file
#define MIDAS_FILE_TYPE_6005	6005		// Index data associated with a type 1004 multi-point file
#define MIDAS_FILE_TYPE_6080	6000		// SDDS network packet data (56-byte SDDS header, 1024-byte data)



//////////////////////////////////////////////////////////////////////////
// Data Format Size Designator
#define DATA_FORMAT_SIZE_DESIGNATOR_SCALR									'S'	// 1 element per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_COMPLEX								'C'	// 2 elements per data point, representing a complex number (real, imaginary)
#define DATA_FORMAT_SIZE_DESIGNATOR_VECTOR								'V'	// 3 elements per data point, representing a positional vector (x,y,z) or (alt,lat,lon)
#define DATA_FORMAT_SIZE_DESIGNATOR_QUAD									'Q'	// 4 elements per data point, representing a positional vector with time (x,y,z,time)
#define DATA_FORMAT_SIZE_DESIGNATOR_MATRIX								'M'	// 9 elements per data point, representing a 3-by-3 coordinate transformation
#define DATA_FORMAT_SIZE_DESIGNATOR_TRANSFORM_MATRIX			'T'	// 16 elements per data point, representing	a 4-by-4 coordinate transformation with scaling
																															// (may be used as a generic multiplier	for ASCII strings)
#define DATA_FORMAT_SIZE_DESIGNATOR_USER_DEFINED					'U'	// Deprecated Extremely limited support in Midas baselines.

#define DATA_FORMAT_SIZE_HOMOGENIUS_FIXED_LENGTH1					'N'

#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_1	'1'	// 1 elements per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_2	'2'	// 2 elements per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_3	'3'	// 3 elements per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_4	'4'	// 4 elements per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_5	'5'	// 5 elements per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_6	'6'	// 6 elements per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_7	'7'	// 7 elements per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_8	'8'	// 8 elements per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_9	'9'	// 9 elements per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_10	'X'	// 10 elements per data point
#define DATA_FORMAT_SIZE_DESIGNATOR_GENERIC_MULTIPLIER_32	'A'	// 32 elements per data point

//////////////////////////////////////////////////////////////////////////
// Data Format Type Designator
#define DATA_FORMAT_TYPE_DESIGNATOR__8BIT_INTEGER					'B'	//  8-bit integer, KW, DATA, SUBRECORDS
#define DATA_FORMAT_TYPE_DESIGNATOR_16BIT_INTEGER					'I'	// 16-bit integer, KW, DATA, SUBRECORDS
#define DATA_FORMAT_TYPE_DESIGNATOR_32BIT_INTEGER					'L'	// 32-bit integer, KW, DATA, SUBRECORDS
#define DATA_FORMAT_TYPE_DESIGNATOR_64BIT_INTEGER					'X'	// 64-bit integer, KW, DATA, SUBRECORDS
#define DATA_FORMAT_TYPE_DESIGNATOR_32BIT_FLOAT						'F'	// 32-bit float KW, DATA, SUBRECORDS
#define DATA_FORMAT_TYPE_DESIGNATOR_64BIT_FLOAT						'D'	// 64-bit float KW, DATA, SUBRECORDS
#define DATA_FORMAT_TYPE_DESIGNATOR_PACKED_BITS						'P'	// Packed bits (accessible on byte boundaries)
#define DATA_FORMAT_TYPE_DESIGNATOR_4BIT_INTEGER					'N'	// 4-bit integer (accessible on byte integer boundaries)
#define DATA_FORMAT_TYPE_DESIGNATOR_OFFSET_BYTE						'O'	// Offset byte DATA, SUBRECORDS
#define DATA_FORMAT_TYPE_DESIGNATOR_ASCII									'A'	// ASCII (8 characters) DATA, SUBRECORDS
#define DATA_FORMAT_TYPE_DESIGNATOR_ASCII_VARIABLE				'A'	// ASCII (variable length) KW
#define DATA_FORMAT_TYPE_DESIGNATOR_UTF_8									'S'	// Modified UTF-8 (8 octets) Reserved for future use in DATA, SUBRECORDS
#define DATA_FORMAT_TYPE_DESIGNATOR_UTF_8_VARIABLE				'S'	// Modified UTF-8 (variable length) Reserved
#define DATA_FORMAT_TYPE_DESIGNATOR_32BIT_INTEGER2				'T'	// KW

#define DATA_FORMAT_SIZE_HOMOGENIUS_FIXED_LENGTH2					'H'


//////////////////////////////////////////////////////////////////////////
// Midas Codes to Identify Value Units
// 
#define VALUE_UNITS_NOT_APPLICABLE						0		// Not applicable
#define VALUE_UNITS_TIME											1		// [s] Time ( seconds )
#define VALUE_UNITS_DELAY											2		// [s] Delay (seconds) (less common then 1 (Time) since “delay” is usually implied by context)
#define VALUE_UNITS_HZ												3		// [Hz] Frequency ( hertz )
#define VALUE_UNITS_TCODE											4		// [tcode] Time code format
#define VALUE_UNITS_DISTANCE									5		// [m] Distance ( meters )
#define VALUE_UNITS_SPEED											6		// [m/s] Speed (meters per second)
#define VALUE_UNITS_ACCELERATION							7		// [m/s^2] Acceleration (m/s per second)
#define VALUE_UNITS_JERK											8		// [m/s^3] Jerk (m/s^2 per second)
#define VALUE_UNITS_DOPPLER										9		// [Hz] Doppler ( hertz )
#define VALUE_UNITS_DOPPLER_RATE							10	// [Hz/s] Doppler rate (hertz per second)
#define VALUE_UNITS_JOULES										11	// [J] Energy ( joules )	
#define VALUE_UNITS_WATTS											12	// [W] Power ( watts )
#define VALUE_UNITS_GRAMS											13	// [g] Mass ( grams )
#define VALUE_UNITS_VOLUME										14	// [dm^3] Volume (dm^3 = cubic decimeter = liter)
#define VALUE_UNITS_ANGULAR_POWER_DENSITY			15	// [W/sr] Angular power density (watts per steradian)
#define VALUE_UNITS_INTEGRATED_POWER_DENSITY	16	// [W/rad] Integrated power density (watts per radian)
#define VALUE_UNITS_SPATIAL_POWER_DENSITY			17	// [W/m^2] Spatial power density (watts per square meter)
#define VALUE_UNITS_INTEGRATED_POWER_DENSITY2	18	// [W/m] Integrated power density (watts per meter)
#define VALUE_UNITS_SPATIAL_POWER_DENSITY2		19	// [W/MHz] Spectral power density (watts per megahertz)
#define VALUE_UNITS_UNKNOWN										30	// [unk] Unknown
#define VALUE_UNITS_NONE											31	// [none] General dimensionless
#define VALUE_UNITS_COUNTS										32	// [counts] Counts
#define VALUE_UNITS_RADIANS										33	// [rad] Angle ( radians )
#define VALUE_UNITS_DEGREE										34	// [deg] Angle ( degrees )
#define VALUE_UNITS_RELATIVE_POWER						35	// [dB] Relative power ( decibels )
#define VALUE_UNITS_RELATIVE_POWER2						36	// [dB] Relative power (decibels relative to 1 milliwatt)
// 	37	dBW	Relative power (decibels relative to 1 watt)
// 	38	sr	Solid angle ( steradian )
// 	40	ft	Distance (US foot = 25.4 mm )
// 	41	nmi	Distance (nautical mile = 1852m)
// 	42	ft/s	Speed (feet per second)
// 	43	nmi/s	Speed (nautical miles per second)
// 	44 	 kt 	 Speed (knots = nautical miles per hour)
// 	45	ft/s^2	Acceleration (feet per second per second)
// 	46	nmi/s^2	Acceleration (nautical mile per second per second)
// 	47	kt/s	Acceleration (knots per second)
// 	48	g	Acceleration (gravities = 9.8 m/s^2)
// 	49	g/s	Jerk (gravities per second)
// 	50	rps	Rotation or revolution rate (rotations per second)
// 	51	rpm	Rotation or revolution rate (rotations per minute)
// 	52	rad/s	Angular velocity (radians per second)
// 	53	deg/s	Angular velocity (degrees per second)
// 	54	rad/s^2	Angular acceleration (radians per second per second)
// 	55	deg/s^2	Angular acceleration (degrees per second per second)
// 	56	%	Percentage
// 	57	psi	Pressure (pounds per square inch = 6.894757 kPa)
// 	58		unknown (reserved for future use)
// 	59		unknown (reserved for future use)
// 	60	deg	Latitude (in a range of [-90,+90] where +90 is the North Pole and -90 is South Pole)
// 	61	deg	Longitude (in a range of [-180,+180] where negative values measure west of the Prime Meridian and positive values measure east of the Prime Meridian; note that -180.0 and +180.0 are both valid descriptions of the 180th Meridian)

#define VALUE_UNITS_ALTITUDE									62	// [ft] Altitude ( feet )
#define VALUE_UNITS_ALTITUDE2									63	// [m] Altitude ( meters )



/**
 * @enum      E_EL_ADJUNCT_FILE_TYPE
 * @brief     MIDAS ADJUNCT MIDAS 파일 포멧 종류 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
enum E_EL_ADJUNCT_FILE_TYPE { 
	// Type 1000
	_TYPE_1000=0, 

	// Type 2000
	_TYPE_2000, 
	
	// Type 3000
	_TYPE_3000, 

	// Type 4000
	_TYPE_4000, 
	
	// Type 5000
	_TYPE_5000 

};

/*!
 * @typedef		SELMIDAS_HCB
 * @brief			MIDAS 포멧의 고정된 Header Control Block (HCB)
 * @author    조철희
 * @date      2014-11-22 
 */
typedef struct {
	char version[4];									// header version
	char head_rep[4];									// header representation
	char data_rep[4];									// Data representation
	unsigned int detached;						// Detached header

	unsigned int _protected;					// Protected from overwrite
	unsigned int pipe;								// Pipe mode (N/A)
	unsigned int ext_start;						// Extended header start, in 512-byte blocks
	unsigned int ext_size;						// Extended header size in bytes

	double data_start;								// Data start in bytes
	double data_size;									// Data size in bytes

	unsigned int type;								// File type code
	char format[2];										// Data format code

	unsigned short flagmask;					// 16-bit flagmask (1=flagbit)
	double timecode;									// Time code field
	unsigned short inlet;							// Inlet owner
	unsigned short outlets;						// Number of outlets
	unsigned int outmaks;							// Outlet async mask
	unsigned int pipeloc;							// Pipe location
	unsigned int pipesize;						// Pipe size in bytes
	double in_byte;										// Next input byte
	double out_byte;									// Next out byte (cumulative)
	double outbytes[8];								// Next out byte (each outlet)

	unsigned int keylength;						// Length of keyword string
	char keywords[92];								// User defined keyword string

} SELMIDAS_HCB ;

/*!
 * @typedef		SELMIDAS_BINARY_KEYWORD
 * @brief			Extended Header 에대한 구조체 정의
 * @author    조철희
 * @date      2015-03-05 
 */
typedef struct {
	unsigned int lkey;								// total length of keyword
	unsigned short lext;							// length of non-value part of keyword
	unsigned char ltag;								// length of keyword tag
	char type;												// type of data in keyword value

} SELMIDAS_BINARY_KEYWORD ;


/**
 * @typedef   SELMIDAS_ADJUNCT_TYPE_1000
 * @brief     Type 1000 추가 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
typedef struct {
	double xstart;
	double xdelta;
	unsigned int xunits;

} SELMIDAS_ADJUNCT_TYPE_1000 ;


/**
 * @typedef   SELMIDAS_ADJUNCT_TYPE_2000
 * @brief     Type 2000 추가 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
typedef struct {
	unsigned long int xstart;
	unsigned long int xdelta;
	unsigned int xunits;
	unsigned int subsize;
	unsigned long int ystart;
	unsigned long int ydelta;
	unsigned int yunits;

} SELMIDAS_ADJUNCT_TYPE_2000 ;

/**
 * @typedef   SELSUBRECORDS
 * @brief     subrecords 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
typedef struct  {
	char name[4];
	char format[2];
	unsigned short offset;

} SELSUBRECORDS;

/**
 * @typedef   SELMIDAS_ADJUNCT_TYPE_3000
 * @brief     Type 3000/6000 추가 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
typedef struct {
	double rstart;
	double rdelta;
	unsigned int runits;
	unsigned int subrecords;
	double r2start;
	double r2delta;
	unsigned int r2units;
	unsigned int record_length;

	// SELSUBRECORDS subr;

} SELMIDAS_ADJUNCT_TYPE_3000 ;

#define	SELMIDAS_ADJUNCT_TYPE_6000  SELMIDAS_ADJUNCT_TYPE_3000

/**
 * @typedef   SELMIDAS_ADJUNCT_TYPE_4000
 * @brief     Type 4000 추가 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
typedef struct {
	unsigned long int vrstart;
	unsigned long int vrdelta;
	unsigned int vrunits;
	unsigned int nrecords;
	unsigned long int vr2start;
	unsigned long int vr2delta;
	unsigned int vr2units;
	unsigned int vrecord_length;

} SELMIDAS_ADJUNCT_TYPE_4000 ;

typedef struct {
	unsigned long int tstart;
	unsigned long int tdelta;
	unsigned int tunits;
	unsigned int components;
	unsigned long int t2start;
	unsigned long int t2delta;
	unsigned int t2units;
	unsigned int record_length;

	unsigned long int quadwords[12];

} SELMIDAS_ADJUNCT_TYPE_5000 ;


//////////////////////////////////////////////////////////////////////////
// Type 6000 TYPE0 Subrecord Format
typedef struct  {
	char name[24];				/// 컬럼명
	char minval[24];			/// 최소 값
	char maxval[24];			/// 최대 값
	char offset[8];				/// 옵셋
	char num_elts[4];			/// 엘리먼트 갯수
	char units[4];				/// 단위
	char format[2];				/// 포멧
	char uprefix[3];			/// Greek 접두어 코드
	char reserved[3];			/// 예비

} SELMIDAS_SUBRECORDS;

typedef struct {
	float fMinVal;
	float fMaxVal;

} SEL_MIN_MAX ;

enum enSUBRECORDS { enTOAOfSub=0, enDTOAOfSub, enFreqOfSub, enPWOfSub, enPAOfSub, enDOAOfSub };
const char stSubrecordName[MAX_SUBRECORDS_OF_PDWDATA][10] = { "TOA", "DTOA", "FREQ", "PW", "PA", "AOA" } ;
const char stSubrecordUnit[MAX_SUBRECORDS_OF_PDWDATA] = { VALUE_UNITS_TIME, VALUE_UNITS_TIME, VALUE_UNITS_HZ, VALUE_UNITS_TIME, VALUE_UNITS_RELATIVE_POWER2, VALUE_UNITS_DEGREE } ;
const char stSubrecordFormat[MAX_SUBRECORDS_OF_PDWDATA][10] = { "%e", "%e", "%f", "%e", "%f", "%f" } ;

// PDW 데이터 구조체 정의
// 위 stSubrecordName, 과 stSubrecordUnit 과 동일 순서로 설정해야 함.
typedef struct {
    double ltoa;
    double ldtoa;
    double lfreq;

    double lpw;
    double lpa;
    double ldoa;

} S_EL_PDW_RECORDS;

// char   형은 마지막 끝에 NULL 문자로 끝나야 함. 입력할 것이 없으면 NULL 로 저장함.
// time_t 형은 시간 정보를 저장. 정보가 없으면 0 으로 함.
// int 형은 정보가 없으면 -1 로 저장함.
// int 형은 정보가 없으면 -1 로 저장함.
struct SEL_KEYWORD_VALUE{
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

	int numberofdata;						// 데이터 개수

	int mission;
	int receiver;

	SEL_KEYWORD_VALUE() :
		dRF(0.0),
		dBW(0.0),
		dSamplingPeriod(0.0),
		dRecBW(0.0),
		gain_mode(0),
		dGain_value(0.0),
		numberofdata(0)
	{
		strcpy_s( classification, "701-ELINT" );
		// memset(classification, NULL, 50);
        memset(writer, 0, sizeof(writer) );
        memset(writer_version, 0, sizeof(writer_version));
        memset(signal_id, 0, sizeof(signal_id) );
        memset(notes, 0, sizeof(notes) );
        memset(collector, 0, sizeof(collector));
        memset(feed, 0, sizeof(feed));

		dGain_value = 70;

		mission = 0;
		receiver = 0;
	}
};



//////////////////////////////////////////////////////////////////////////
// 데이터 구조체 정의
#define	MAX_OF_IQ_DATA					(200)
#define	MAX_OF_IF_DATA					(200)
#define	MAX_OF_PRF_TONE_DATA		(200)
#define	MAX_OF_PDW_DATA					(30)
#define	MAX_OF_SAMPLING_DATA		(200)



struct S_UNI_DATA_SET {
	//char cbyte;

	// codesonar의 Uninitialized Variable 과 충돌 남.	SRxIQDataRGroup, SRxIFDataRGroup 구조체 초기화를 강제로 막으면 안됨. 해결 필요. 
	SRxIQDataRGroup1 iqData[MAX_OF_IQ_DATA];
	SRxIFDataRGroupEEEI ifData[MAX_OF_IF_DATA];
	//short samplingData[MAX_OF_SAMPLING_DATA];
	//short prftoneData[MAX_OF_PRF_TONE_DATA];
    SRxPDWDataRGroup pdwData[MAX_OF_PDW_DATA];

	S_EL_PDW_RECORDS pdwRecord[MAX_OF_PDW_DATA];

	S_UNI_DATA_SET()
	{
		memset( iqData, 0, sizeof(iqData) );
		memset( ifData, 0, sizeof(ifData) );

		//memset( samplingData, 0, sizeof(samplingData) );
		//memset( prftoneData, 0, sizeof(prftoneData) );
        //memset( pdwData, 0, sizeof(pdwData) );

	}

} ;

typedef struct {
	char szInputFilename[500];
	char szOutputFilename[500];

	SEL_KEYWORD_VALUE keywordValue;

} SELIFMIDAS;

/**
 * @class     CMIDASBlueFileFormat
 * @brief     PDW, IQ, IF 데이터를 MIDAS 포멧으로 변환해주는 클래스
 * 
 * (1)　클래스 설명
 *  - PDW, IQ, IF 데이터 파일을 MIDAS 포멧으로 변환해주는 클래스임.
 * 
 * (2)　설계결정사항
 *  - PDW, IQ, IF 데이터 파일을 MIDAS 포멧으로 변환
 *  - 이외에 추가적인 데이터 변환이 있음.
 * 
 * (3)　제한 및 예외처리
 *  - 해당사항 없음.
 * 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2014-11-22 오후 8:50 
 * @warning   
 */
//class CMIDASBlueFileFormat : public CRawFile, public CPDW2SP370
class CMIDASBlueFileFormat : public CRawFile
{
protected:
	int m_SizeOfExtend;
	EnumSCDataType m_enFileType;																///< 변환하기 위한 변환 데이터 포멧
	SELMIDAS_HCB *m_pHCB;
	unsigned char *m_pExtendOfHeader;

	S_EL_PDW_RECORDS *m_pPDWRecords;

	SEL_MIN_MAX m_MinMaxOfSubrecords[MAX_SUBRECORDS_OF_PDWDATA];
	SELMIDAS_SUBRECORDS *m_pSubrecords;													///< MIDAS 포멧으로 변환하기 위한 Subrecord

	vector<SELIFMIDAS> m_vecConvertIFList;											///< IF 데이터 파일을 MIDAS 포멧으로 변환하기 위한 목록
	char m_szIFTaskId[200];

    _TOA m_ullfirstTOA;

private:
    char m_szRawDataFilename[500];

    SEL_KEYWORD_VALUE m_strKeywordValue;

    STR_PDWDATA *m_pPDWData;

private:
	int GetSampleSize();
	void MakeHeader();
	void MakeAdjunct();
	int WriteHeader();
	int WriteAdjunct();
	unsigned int GetValueUnits();
	bool WriteData( int destFileId, int iSkipByte, bool bMultiIFData=false );
	void MakePRFToneData();
	unsigned int CalcExtStart();
	double CalcDataSize();
	void MakeExtendedHeader();
	int WriteExtendedHeader();
	void MakeBinaryKeyword( SELMIDAS_BINARY_KEYWORD *pBinKeyword, char *value_keyword, char *keyword, int c, char type, int lkey=0 );
	SELMIDAS_BINARY_KEYWORD *MakeValueBinaryKeyword( SELMIDAS_BINARY_KEYWORD *pBinKeyword, unsigned long long iValue, char *keyword, char type, int lkey=0 );
    SELMIDAS_BINARY_KEYWORD *MakeValueBinaryKeyword( SELMIDAS_BINARY_KEYWORD *pBinKeyword, long double iValue, char *keyword, char type );
	SELMIDAS_BINARY_KEYWORD *MakeSetBinaryKeyword( SELMIDAS_BINARY_KEYWORD *pBinKeyword, char *pValue, char *keyword );
	int MakeSubRecords( SELSUBRECORDS *pSubRecords, char *pName, unsigned char data_type1, unsigned char data_type2, int nOffset );
    void TransferPDW2Record( SRxPDWDataRGroup *pS_EL_PDW_DATA, int iRecords );
    void TransferPDW2Record( _PDW *pS_EL_PDW_DATA, int iRecords );
	void TransferIQ( SRxIQDataRGroup1 *pSRxIQDataRGroup, int iByte );
	void TransferIF( SRxIFDataRGroupEEEI *pSRxIFDataRGroupEEEI, int iByte );
	int MakeSubRecords();
	void MIDASClose();
	void MakeMinMaxValue( SEL_MIN_MAX *pSEL_MIN_MAX, double dValue );
	void MakeInitMinMaxValue( SEL_MIN_MAX *pSEL_MIN_MAX );

public:
	CMIDASBlueFileFormat(void);
	~CMIDASBlueFileFormat(void);
	bool SaveMIDASFormat( char *pMidasFileName, EnumSCDataType enFileType, int i_pstReadFile, int i_nFileRawDataStartOffset, SEL_KEYWORD_VALUE & stKeywordValue, char *pInputFilename=NULL, char *pTaskID=NULL );

    bool SaveMIDASFormat( char *pMidasFileName, EnumSCDataType enFileType, void *pData, SEL_KEYWORD_VALUE *pstKeywordValue );

	void MakeMIDASFileName( char *pstOutFilePathName, char *pstFileName, EnumSCDataType eDataType );

	// IF 데이터를 변환하기 위한 함수
	void InitIFMidas();
	bool SaveAllIFMIDASFormat();

    void SaveRawDataFile( TCHAR *pLocalDirectory, EnumSCDataType enDataType, void *pData, unsigned int uiStep );

    inline char *GetRawDataFilename() { return m_szRawDataFilename; }
	
};
