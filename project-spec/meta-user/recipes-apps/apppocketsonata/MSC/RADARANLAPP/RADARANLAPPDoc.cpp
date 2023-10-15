
// RADARANLAPPDoc.cpp : CRADARANLAPPDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "RADARANLAPP.h"
#endif

#define _MAIN_
#define _MAIN_GLOBALS_

float _spAOAres;
float _spAMPres;

#include "../../files/Anal/OFP_Main.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <propkey.h>

#include "RADARANLAPPDoc.h"

#include "../../files/Utils/cthread.h"
#include "../../files/Anal/EmitterMerge/ELEmitterMergeMngr.h"

#include "../../files/Include/globals.h"



float AOA( float x );

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CODBCDatabase CRADARANLAPPDoc::m_theMyODBC;

// [1]: 소방대 분소, [2]: 관제 수신소, [3]: 신불 레이더#1, [4]: 신불 레이더#2
//double dRCLatitude[RADARCOL_MAX] = { 0.0, 37.485168456889, 37.454452514694, 37.453517913889 } ;
//double dRCLongitude[RADARCOL_MAX] = { 0.0, 126.457916259694, 126.481880188111, 126.423416137778 } ;

double dRTarget[2] = { 37.485131, 126.423459 } ;

// CRADARANLAPPDoc

IMPLEMENT_DYNCREATE(CRADARANLAPPDoc, CDocument)

BEGIN_MESSAGE_MAP(CRADARANLAPPDoc, CDocument)
	ON_COMMAND(ID_OP_INIT, &CRADARANLAPPDoc::OnOpInit)
END_MESSAGE_MAP()


// CRADARANLAPPDoc 생성/소멸

#ifdef _MSSQL_
CRADARANLAPPDoc::CRADARANLAPPDoc() : CMSSQL( & m_theMyODBC )
#else
CRADARANLAPPDoc::CRADARANLAPPDoc()
#endif
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
#ifdef _MSSQL_
	CMSSQL::Init();
#endif

	MakeIniFilename();

}

CRADARANLAPPDoc::~CRADARANLAPPDoc()
{
	m_theMyODBC.Close();

}

BOOL CRADARANLAPPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CRADARANLAPPDoc serialization

void CRADARANLAPPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CRADARANLAPPDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CRADARANLAPPDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CRADARANLAPPDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CRADARANLAPPDoc 진단

#ifdef _DEBUG
void CRADARANLAPPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRADARANLAPPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRADARANLAPPDoc 명령
void CRADARANLAPPDoc::OnFileOpen()
{
	unsigned int i;
	float fTheta, fErr;
	STR_LOBDATA stLOBData;
	SRxLOBData *pLOBData;

	float fDOAMax, fDOAMin;

	stLOBData.stLOBHeader.uiNumOfLOB = 1;
	//strcpy_s( stLOBData.stLOBHeader.aucTaskID, sizeof(stLOBData.stLOBHeader.aucTaskID), "RADARANLAPP" );

	pLOBData = & stLOBData.stLOBData[0];
	for( i=0 ; i < stLOBData.stLOBHeader.uiNumOfLOB ; ++i ) {
#if defined(_POCKETSONATA_) || defined(_712_)

#elif defined(_ELINT_) || defined(_XBAND_)
		pLOBData->iCollectorID = RADARCOL_1 + ( i % RADARCOL_3 ) ;
		if( i % 2 == 0 ) {
			pLOBData->iCollectorID = RADARCOL_1;
			pLOBData->fDOAMean = (float) 240.8;
		}
		else {
			pLOBData->iCollectorID = RADARCOL_2;
			pLOBData->fDOAMean = (float) 270.0;
		}
#else
#endif

		pLOBData->uiLOBID = i + 1;
		pLOBData->uiABTID = 0;
		pLOBData->uiAETID = 0;

		pLOBData->tiContactTime = _time32(NULL);
		pLOBData->tiContactTimems = i;

		pLOBData->vSignalType = ST_CW;


#if defined(_POCKETSONATA_) || defined(_712_)
        fTheta = (float) (rand() % 360);
#elif defined(_ELINT_) || defined(_XBAND_)
		fTheta = (float) GCAzimuth( (double) dRCLatitude[pLOBData->iCollectorID], (double) dRCLongitude[pLOBData->iCollectorID], dRTarget[0], dRTarget[1], false );
#else
        fTheta = (float)(rand() % 360);
#endif
		fErr = (float) ( ( rand() % 100 ) / 10. - 5. );
		//printf( "\n fDOA Err[%f]" , fErr );
		pLOBData->fDOAMean = AOA( fTheta + fErr );
		fErr = (float) ( ( rand() % 100 ) / 50. - 1. );
		//printf( "\n fDOA (MAX/MIN) Err[%f]" , fErr );
		if( fErr > 0 ) {
			fDOAMax = AOA( pLOBData->fDOAMean + fErr );
			fDOAMin = AOA( pLOBData->fDOAMean - fErr );
		}
		else {
			fDOAMin = AOA( pLOBData->fDOAMean + fErr );
			fDOAMax = AOA( pLOBData->fDOAMean - fErr );
		}

		pLOBData->fDOAMax = fDOAMax;
		pLOBData->fDOAMin = fDOAMin;		// _min( fMaxDOA, fMinDOA );

		if( i % 2 == 0 ) {
			pLOBData->fDOAMean = (float) 140.8;
			pLOBData->fDOAMax = (float) 140.9;
			pLOBData->fDOAMin = (float) 140.7;
		}
		else {
			pLOBData->fDOAMean = (float) 111.8;
			pLOBData->fDOAMax = (float) 112.1;
			pLOBData->fDOAMin = (float) 111.5;
		}

		pLOBData->uiDIRatio = 100;

		pLOBData->vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
		pLOBData->vFreqPatternType = ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_UNKNOWN;
		pLOBData->fFreqPatternPeriod = 0;	  // [us]
		pLOBData->fFreqMean = (float) 6000.297852;										// [10KHz]
		pLOBData->fFreqMax = (float) 6000.803955;
		pLOBData->fFreqMin = (float) 6000.763916;
		pLOBData->vFreqPositionCount = 0;
		memset( pLOBData->fFreqSeq, 0 , sizeof(pLOBData->fFreqSeq) );

		pLOBData->vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
		pLOBData->vPRIPatternType = ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_UNKNOWN;
		pLOBData->fPRIPatternPeriod = 0;
		pLOBData->fPRIMean = (float) 1233.268188;
		pLOBData->fPRIMax = (float) 1359.570313;
		pLOBData->fPRIMin = (float) 1132.8125;
		pLOBData->fPRIJitterRatio = 18.;
		pLOBData->vPRIPositionCount = 2;
		memset( pLOBData->fPRISeq, 0 , sizeof(pLOBData->fPRISeq) );
		pLOBData->fPRISeq[0] = (float) 1132.8125;
		pLOBData->fPRISeq[1] = (float) 1359.570313;

		pLOBData->fPWMean = (float) 2411.52002;
		pLOBData->fPWMax = (float) 4392.959961;
		pLOBData->fPWMin = (float) 706.560059;

		pLOBData->fPAMean = -58;
		pLOBData->fPAMax = -57.5;
		pLOBData->fPAMin = -69;

#if defined(_XBAND_) || defined(_ELINT_)
		pLOBData->iIsStoreData = 0;
#endif
		pLOBData->uiNumOfCollectedPDW = 50;
        pLOBData->uiNumOfAnalyzedPDW = 50;

        memset(pLOBData->szRadarModeName, 0, sizeof(pLOBData->szRadarModeName));
        pLOBData->uiRadarModeIndex = 0;
        //pLOBData->iThreatIndex = 0;

#if defined(_POCKETSONATA_) || defined(_712_)

#elif defined(_ELINT_) || defined(_XBAND_)
		pLOBData->fLatitude = (float) dRCLatitude[pLOBData->iCollectorID];
		pLOBData->fLongitude = (float) dRCLongitude[pLOBData->iCollectorID];

        pLOBData->uiSeqNum = 0;
#else

#endif

#if defined(_ELINT_) || defined(_XBAND_)
		strcpy_s( pLOBData->aucTaskID, sizeof(pLOBData->aucTaskID), "RADARANLAPP" );
#endif

		++ pLOBData;
	}

	//////////////////////////////////////////////////////////////////////////
	//

	Run( stLOBData.stLOBHeader.uiNumOfLOB, & stLOBData.stLOBData[0], NULL );

}


void CRADARANLAPPDoc::OnOpInit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	RadarAnlAlgotirhm::RadarAnlAlgotirhm::SWInit();

}


// namespace GEO {
// 	const double PIOVER2 = M_PI/2.0;
// 	const double TWOPI = 6.28318530718;
// 	const double DE2RA = 0.01745329252;
// 	const double RA2DE = 57.2957795129;
// 	const double ERAD = 6378.137;
// 	const double ERADM = 6378137.0;
// 	const double AVG_ERAD = 6371.0;
// 	const double FLATTENING = 1.000000/298.257223563;// Earth flattening (WGS84)
// 	const double EPS = 0.000000000005;
// 	const double KM2MI = 0.621371;
// 	const double GEOSTATIONARY_ALT = 35786.0; // km - approximate value
// }

// initial bearing 값 측정
double CRADARANLAPPDoc::GCAzimuth(double lat1, double lon1, double lat2, double lon2, bool bInitialBearing )
{
	double result = 0.0;

	INT32 ilat1 = (INT32)(0.50 + lat1 * 360000.0);
	INT32 ilat2 = (INT32)(0.50 + lat2 * 360000.0);
	INT32 ilon1 = (INT32)(0.50 + lon1 * 360000.0);
	INT32 ilon2 = (INT32)(0.50 + lon2 * 360000.0);

	lat1 *= GEO::DE2RA;
	lon1 *= GEO::DE2RA;
	lat2 *= GEO::DE2RA;
	lon2 *= GEO::DE2RA;

	if ((ilat1 == ilat2) && (ilon1 == ilon2))
	{	//DTEC_Else
		return result;
	}
	else if (ilon1 == ilon2)
	{	//DTEC_Else
		if (ilat1 > ilat2) { //DTEC_Else
			result = 180.0;
		}
	}
	else
	{
		if( bInitialBearing == true ) {
			double angle = atan2(cos(lat2) * sin(lon2 - lon1), sin(lat2) * cos(lat1) - sin(lat1) * cos(lat2) * cos(lon2 - lon1));
			result = (angle * GEO::RA2DE);
			result += ( 360.0 * 2 );
			result = fmod( result, 360.0 );
		}
		else {
			double angle = atan2(cos(lat1) * sin(lon1 - lon2), sin(lat1) * cos(lat2) - sin(lat2) * cos(lat1) * cos(lon1 - lon2));
			result = (angle * GEO::RA2DE);
			result += ( 360.0 * 2 );
			result += ( 180.0 );
			result = fmod( result, 360.0 );
		}
	}

	return result;
}

float AOA( float x )
{
	float fAOA;

	fAOA = x + (float) 720.;
	fAOA = (float) fmod( (double) fAOA, 360. );
	return fAOA;
}


void CRADARANLAPPDoc::MakeIniFilename()
{
	char envini_path[100] = "RadarAnl.ini";
	CString	strTemp = _T(""), strFilename;

	GetCurrentDirectory( _MAX_PATH, m_szProgramPath );

	CFileStatus fs;

	strTemp = m_szProgramPath;

	int iFind=strTemp.Find( "ELINTOP\\ELINTOP" );

	if( iFind > 0 ) {
		m_strIniFilename = strTemp + "/../RADARANLAPP/" + envini_path;
		//m_strFilename = strTemp + '/' + envini_path;
	}
	else {
		m_strIniFilename = strTemp + '/' + envini_path;

	}
	if( CFile::GetStatus( m_strIniFilename, fs ) == FALSE ) {
		strTemp.Format( "%s 파일이 %s 폴더에 존재하지 않습니다 !!! 관리자에게 문의하세요.", m_strIniFilename, m_szProgramPath );
		AfxMessageBox( strTemp );
	}

}

void CRADARANLAPPDoc::WriteProfile( char *pAppName, char *pAppKey, char *pValue )
{

	if( pValue != NULL ) {
		WritePrivateProfileString( pAppName, pAppKey, pValue, m_strIniFilename );
	}

}

/**
 * @brief     LoadProfile
 * @param     char * pValue
 * @param     int iSize
 * @param     char * pAppName
 * @param     char * pAppKey
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-13 09:44:51
 * @warning
 */
void CRADARANLAPPDoc::LoadProfile( char *pValue, int iSize, char *pAppName, char *pAppKey )
{
	CFileStatus fs;

	CString	strTemp;

	if( CFile::GetStatus( m_strIniFilename, fs ) == FALSE ) {
		strTemp.Format( "%s 파일이 %s 폴더에 존재하지 않습니다 !!! 관리자에게 문의하세요.", m_strIniFilename, m_szProgramPath );
		AfxMessageBox( strTemp );
	}

	GetPrivateProfileString( pAppName, pAppKey, NULL, pValue, iSize, m_strIniFilename );

}

/**
 * @brief     Init
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-13 09:44:49
 * @warning
 */
void CRADARANLAPPDoc::Init()
{
	RadarAnlAlgotirhm::RadarAnlAlgotirhm::SWInit();
}

/**
 * @brief     Run
 * @param     int nLOB
 * @param     SRxLOBData * pLOBData
 * @param     SELLOBDATA_EXT * pLOBExt
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-13 09:44:48
 * @warning
 */
void CRADARANLAPPDoc::Run( int nLOB, SRxLOBData *pLOBData, SELLOBDATA_EXT *pLOBExt )
{
	int i;

	STR_LOBDATA stResLOBData;
	STR_ABTDATA stResABTData;
    STR_AETDATA stResAETData;

	m_stLOBData.stLOBHeader.uiNumOfLOB = nLOB;
	for( i=0 ; i < nLOB ; ++i ) {
		memcpy( & m_stLOBData.stLOBData[i], pLOBData, sizeof( struct SRxLOBData) );

		++ pLOBData;
	}

	RadarAnlAlgotirhm::RadarAnlAlgotirhm::Start( & m_stLOBData );
    //RadarAnlAlgotirhm::RadarAnlAlgotirhm::ManageThreat(&m_stLOBData);

	RadarAnlAlgotirhm::RadarAnlAlgotirhm::GetLOBData( & stResLOBData );
	RadarAnlAlgotirhm::RadarAnlAlgotirhm::GetABTData( & stResABTData );
    RadarAnlAlgotirhm::RadarAnlAlgotirhm::GetAETData( & stResAETData );

}


/**
 * @brief     GetDB_LOB
 * @param     int * pnLOB
 * @param     SRxLOBData * pLOBData
 * @param     SELLOBDATA_EXT * pLOBExt
 * @param     char * pWhere
 * @param     int iMaxItems
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-12, 12:02
 * @warning
 */
bool CRADARANLAPPDoc::GetDB_LOB( int *pnLOB, SRxLOBData *pLOBData, SELLOBDATA_EXT *pLOBExt, char *pWhere, int iMaxItems )
{
	*pnLOB = 0;

#ifdef _MSSQL_
	DECLARE_BEGIN_CHECKODBC

	int index, iCnt=0;

	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

#if defined(_POCKETSONATA_) || defined(_712_)
	iCnt += sprintf_s(&m_szSQLString[iCnt], MAX_SQL_SIZE - iCnt, "select OP_INIT_ID, PDWID, PLOBID, LOBID, ABTID, AETID, CONTACT_TIME, CONTACT_TIME_MS, SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DOA_DEV, DOA_STD, DI_RATIO, FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_DEV, FREQ_STD, FREQ_POSITION_COUNT, PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_MODE, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PW_MEAN, PW_MIN, PW_MAX, PW_MODE, PA_MEAN, PA_MIN, PA_MAX, PA_MODE, NUM_PDW, ISNULL(COLLECTOR_ID,0) AS COLLECTOR_ID, LATITUDE, LONGITUDE, RADARMODE_NAME, RADARMODE_INDEX from LOBDATA");
#else
	iCnt += sprintf_s( & m_szSQLString[iCnt], MAX_SQL_SIZE-iCnt, "select OP_INIT_ID, PDWID, PLOBID, LOBID, ABTID, AETID, TASK_ID, CONTACT_TIME, CONTACT_TIME_MS, SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DOA_MODE, DI_RATIO, FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_MODE, FREQ_POSITION_COUNT, PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_MODE, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PW_MEAN, PW_MIN, PW_MAX, PW_MODE, PA_MEAN, PA_MIN, PA_MAX, PA_MODE, NUM_PDW, ISNULL(COLLECTOR_ID,0) AS COLLECTOR_ID, LATITUDE, LONGITUDE, RADARMODE_NAME, RADARMODE_INDEX from LOBDATA" );
#endif

	iCnt += sprintf_s( & m_szSQLString[iCnt], MAX_SQL_SIZE-iCnt, " %s", pWhere );
	//iCnt += sprintf_s( & m_szSQLString[iCnt], MAX_SQL_SIZE-iCnt, " ORDER BY OP_INIT_ID desc, LOBID desc" );

	theRS.Open( m_szSQLString );
	while (!theRS.IsEof()) {
        int iDummy;

		index = 0;

		memset(pLOBData, 0, sizeof( struct SRxLOBData));
		memset(pLOBExt, 0, sizeof( struct SELLOBDATA_EXT));

		theRS.GetFieldValue(index++, (int *) & pLOBExt->aetData.uiOpInitID );
#if defined(_ELINT_) || defined(_XBAND_)
        pLOBData->uiOpInitID = pLOBExt->aetData.uiOpInitID;
#endif

		theRS.GetFieldValue(index++, (int *) & pLOBData->uiPDWID );
        theRS.GetFieldValue(index++, (int *) & pLOBData->uiPLOBID );
		theRS.GetFieldValue(index++, (int *) & pLOBData->uiLOBID );
		theRS.GetFieldValue(index++, (int *) & pLOBData->uiABTID );
		theRS.GetFieldValue(index++, (int *) & pLOBData->uiAETID );

#if defined(_ELINT_) || defined(_XBAND_)
		theRS.GetFieldValue(index++, pLOBData->aucTaskID);
#endif

		theRS.GetFieldTimeValue(index++, (time_t *) & pLOBData->tiContactTime );
		theRS.GetFieldValue(index++, (int *) &pLOBData->tiContactTimems);

#if defined(_POCKETSONATA_) || defined(_712_)
		theRS.GetFieldValue(index++, (int *)& iDummy );
        pLOBData->vSignalType = ( unsigned char ) iDummy;
#else
        theRS.GetFieldValue( index++, ( int * ) &pLOBData->vSignalType );
#endif

		theRS.GetFieldValue(index++, &pLOBData->fDOAMean);
		theRS.GetFieldValue(index++, &pLOBData->fDOAMin);
		theRS.GetFieldValue(index++, &pLOBData->fDOAMax);
        theRS.GetFieldValue( index++, &pLOBData->fDOAMode );

		theRS.GetFieldValue(index++, &pLOBData->uiDIRatio);

		theRS.GetFieldValue(index++, (int *)&pLOBData->vFreqType);
#if defined(_POCKETSONATA_) || defined(_712_)
        theRS.GetFieldValue( index++, ( int * ) & iDummy );
		pLOBData->vFreqPatternType = ( ENUM_AET_FREQ_PRI_PATTERN_TYPE ) iDummy;
#else
        theRS.GetFieldValue( index++, &pLOBData->vFreqPatternType );
#endif
		theRS.GetFieldValue(index++, &pLOBData->fFreqPatternPeriod);
		theRS.GetFieldValue(index++, &pLOBData->fFreqMean);
		theRS.GetFieldValue(index++, &pLOBData->fFreqMin);
		theRS.GetFieldValue(index++, &pLOBData->fFreqMax);
        theRS.GetFieldValue( index++, &pLOBData->fFreqMode );
#if defined(_POCKETSONATA_) || defined(_712_)
        theRS.GetFieldValue( index++, ( int * ) & iDummy );
		pLOBData->vFreqPositionCount = ( unsigned char ) iDummy;
#else
        theRS.GetFieldValue( index++, &pLOBData->vFreqPositionCount );
#endif

#if defined(_POCKETSONATA_) || defined(_712_)
        theRS.GetFieldValue( index++, ( int * ) & iDummy );
        pLOBData->vPRIType = ( ENUM_AET_PRI_TYPE ) iDummy;
        theRS.GetFieldValue( index++, ( int * ) & iDummy );
		pLOBData->vPRIPatternType = ( ENUM_AET_FREQ_PRI_PATTERN_TYPE ) iDummy;
#else
        theRS.GetFieldValue( index++, ( int * ) &pLOBData->vPRIType );
        theRS.GetFieldValue( index++, ( int * ) &pLOBData->vPRIPatternType );
#endif


		theRS.GetFieldValue(index++, &pLOBData->fPRIPatternPeriod);
		theRS.GetFieldValue(index++, &pLOBData->fPRIMean);
		theRS.GetFieldValue(index++, &pLOBData->fPRIMin);
		theRS.GetFieldValue(index++, &pLOBData->fPRIMax);
        theRS.GetFieldValue( index++, &pLOBData->fPRIMode );
		theRS.GetFieldValue(index++, & pLOBData->fPRIJitterRatio);
#if defined(_POCKETSONATA_) || defined(_712_)
        theRS.GetFieldValue( index++, ( int * ) & iDummy );
        pLOBData->vPRIPositionCount = ( unsigned char ) iDummy;
#else
        theRS.GetFieldValue( index++, ( int * ) &pLOBData->vPRIPositionCount );
#endif

		theRS.GetFieldValue(index++, &pLOBData->fPWMean);
		theRS.GetFieldValue(index++, &pLOBData->fPWMin);
		theRS.GetFieldValue(index++, &pLOBData->fPWMax);
        theRS.GetFieldValue( index++, &pLOBData->fPWMode );

		theRS.GetFieldValue(index++, &pLOBData->fPAMean);
		theRS.GetFieldValue(index++, &pLOBData->fPAMin);
		theRS.GetFieldValue(index++, &pLOBData->fPAMax);
        theRS.GetFieldValue( index++, &pLOBData->fPAMode );

		// theRS.GetFieldValue(index++, (int*)&pLOBData->iIsStoreData);
		theRS.GetFieldValue(index++, (int*)&pLOBData->uiNumOfCollectedPDW );
		theRS.GetFieldValue(index++, (int*)& iDummy);

		theRS.GetFieldValue(index++, &pLOBData->fCollectLatitude);
		theRS.GetFieldValue(index++, &pLOBData->fCollectLongitude);

		theRS.GetFieldValue(index++, pLOBData->szRadarModeName);
		theRS.GetFieldValue(index++, (int*)&pLOBData->uiRadarModeIndex);
		//theRS.GetFieldValue(index++, (int*)&pLOBData->iThreatIndex);

		++*pnLOB;
		++pLOBData;
		++pLOBExt;

		if (iMaxItems != 0 && *pnLOB >= iMaxItems) {
			break;
		}

		theRS.MoveNext();

	}

	theRS.Close();

	DECLARE_END_CHECKODBC
	DECLARE_RETURN

#else

    return true;

#endif

}


/**
 * @brief     LoadFieldOfTable
 * @param     int * pCoField
 * @param     char * * pField
 * @param     char * pTable
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-12, 12:10
 * @warning
 */
bool CRADARANLAPPDoc::LoadFieldOfTable( int *pCoField, char **pField, char *pTable )
{
    *pCoField = 0;

#ifdef _MSSQL_
    
	DECLARE_BEGIN_CHECKODBC

	CODBCRecordset theRS = CODBCRecordset(m_pMyODBC);

	sprintf_s(m_szSQLString, MAX_SQL_SIZE, "SELECT name from syscolumns where id=object_id('%s') order by colid", pTable );

	theRS.Open(m_szSQLString);
	while (!theRS.IsEof()) {
		// 테이블의 필드 길이를 한번만 체크한다.
		if( *pCoField == 0 ) {
			if( theRS.GetFieldLength(0) >= MAX_OF_COLUMN_LENGTH ) {
				theRS.Close();
				CAST_THROW_MESSAGE
			}
		}

		theRS.GetFieldValue( (SQLSMALLINT) 0, pField[*pCoField] );
		++ *pCoField;

		theRS.MoveNext();

	}

	theRS.Close();

	DECLARE_END_CHECKODBC
	DECLARE_RETURN

#else

    return true;

#endif
}

/**
 * @brief     GetFieldNameOfTable
 * @param     std::vector<string> * pVecString
 * @param     char * pTable
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-09 11:21:13
 * @warning
 */
bool CRADARANLAPPDoc::GetFieldNameOfTable( std::vector<string> *pVecString, char *pTable)
{
#ifdef _MSSQL_
	DECLARE_BEGIN_CHECKODBC

	CODBCRecordset theRS = CODBCRecordset(m_pMyODBC);

	char szBuffer[300];

	pVecString->clear();
	sprintf(m_szSQLString, "SELECT name from syscolumns where id=object_id('%s') order by colid", pTable);

	theRS.Open(m_szSQLString);
	while (!theRS.IsEof()) {
		if (TRUE == theRS.GetFieldValue((SQLSMALLINT)0, szBuffer))
		{
			pVecString->push_back(szBuffer);
		}

		theRS.MoveNext();

	}

	theRS.Close();

	DECLARE_END_CHECKODBC
	DECLARE_RETURN

#else

    return true;

#endif

}

/**
 * @brief     GetDB_LOB_POSITION
 * @param     int * pnLOB
 * @param     SRxLOBData * pLOBData
 * @param     char * pWhere
 * @param     int iMaxItems
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-12, 12:12
 * @warning
 */
bool CRADARANLAPPDoc::GetDB_LOB_POSITION( int *pnLOB, SRxLOBData *pLOBData, char *pWhere, int iMaxItems )
{
	*pnLOB = 0;

#ifdef _MSSQL_

	DECLARE_BEGIN_CHECKODBC

	int i, index, iCnt=0;

	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

	iCnt += sprintf_s( & m_szSQLString[iCnt], MAX_SQL_SIZE-iCnt, "select POSITION_COUNT, SEQ_01, SEQ_02, SEQ_03, SEQ_04, SEQ_05, SEQ_06, SEQ_07, SEQ_08, SEQ_09, SEQ_10, SEQ_11, SEQ_12, SEQ_13, SEQ_14, SEQ_15, SEQ_16 FROM LOB_POSITION" );
	iCnt += sprintf_s( & m_szSQLString[iCnt], MAX_SQL_SIZE-iCnt, " %s", pWhere );

	theRS.Open( m_szSQLString );
	while (!theRS.IsEof()) {
		index = 0;

		theRS.GetFieldValue(index++, (int *) & pLOBData->vPRIPositionCount );

		memset( pLOBData->fPRISeq, 0, sizeof(pLOBData->fPRISeq) );
		for( i=0 ; i < pLOBData->vPRIPositionCount ; ++i ) {
			theRS.GetFieldValue(index++, (float *) & pLOBData->fPRISeq[i] );
		}

		++*pnLOB;
		++pLOBData;

		if (iMaxItems != 0 && *pnLOB >= iMaxItems) {
			break;
		}

		theRS.MoveNext();

	}

	theRS.Close();

	DECLARE_END_CHECKODBC
	DECLARE_RETURN
#else
    return true;

#endif

}