//////////////////////////////////////////////////////////////////////////
//
//  MODULE:   odbccore.cpp
//
//	AUTHOR: Carlos Antollini 
//
//  mailto: cantollini@hotmail.com
//
//	Date: 08/21/2001
//
//	Version 1.11
// 

#include "stdafx.h"

#include "mssql.h"




//CODBCDatabase *CMSSQL::m_pMyODBC=NULL;

bool CMSSQL::m_bTryConnect=false;

/**
	* @brief		
	* @return 	void
*/
void CMSSQL::CheckConnection()
{
	m_bRet = true;
	if( m_pMyODBC->IsConnected() != TRUE ) {
		m_iErrorException = SQL_ERROR_DISCONNECTION;
		throw m_iErrorException;
	}

}

/**
	* @brief		
	* @param		int iErrorException
	* @return 	void
	* @return		성공시 true, 실패시 false
*/
void CMSSQL::ErrorException( int iErrorException )
{
	m_bRet = false;

	DisplayErrorException( iErrorException );

}

/**
	* @brief		
	* @param		int iErrorException
	* @return 	void
	* @date			2019/04/19 14:54
*/
void CMSSQL::DisplayErrorException( int iErrorException )
{
// 	switch( iErrorException ) {
// 	case SQL_ERROR_DISCONNECTION :
// 		printf( "ODBC 연결이 실패 되었습니다." );
// 		Log( enError, "ODBC 연결이 실패 되었습니다." );
// 		break;
// 
// 	case SQL_ERROR_QUERY :
// 		printf( "Open() 함수에서 에러가 발생했습니다." );
// 		Log( enError, "Open() 함수에서 에러가 발생했습니다." );
// 		break;
// 
// 	default :
// 		break;
// 	}
}

/**
	* @brief		LONG 값을 리턴한다.
	* @param		char * pSQLString
	* @return 	int
	* @date			2019/04/18 17:10
*/
LONG CMSSQL::GetLONGData( char *pSQLString )
{
	LONG lValue=0;

	DECLARE_BEGIN_CHECKODBC

	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

	theRS.Open( pSQLString );
	if( ! theRS.IsEof() ) {
		theRS.GetFieldValue( 0, & lValue );
	}

	theRS.Close();

	DECLARE_END_CHECKODBC

	return lValue;
}

/**
	* @brief		LONG 값을 리턴한다.
	* @param		char * pSQLString
	* @return 	int
	* @date			2019/04/18 17:10
*/
int CMSSQL::GetINTData( char *pSQLString )
{
	int iValue=0;

	DECLARE_BEGIN_CHECKODBC

	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

	theRS.Open( pSQLString );
	if( ! theRS.IsEof() ) {
		theRS.GetFieldValue( 0, & iValue );
	}

	theRS.Close();

	DECLARE_END_CHECKODBC

	return iValue;
}

// /**
// 	* @brief		
// 	* @param		SRxLOBData * pLOBData
// 	* @return 	void
// 	* @date			2019/04/19 9:33
// */
// bool CMSSQL::InsertToDB_LOB( SRxLOBData *pLOBData, SELLOBDATA_EXT *pExt, bool bUpdateRadarMode )
// {
// 	DECLARE_BEGIN_CHECKODBC
// 	
// 	struct tm stTime;
// 	char buffer[100];
// 
// 	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );
// 
// 	_localtime32_s( &stTime, & pLOBData->tiContactTime );
// 	strftime( buffer, 100, "%Y-%m-%d %H:%M:%S", & stTime);
// 	sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO LOBDATA ( OP_INIT_ID, LOBID, ABTID, AETID, TASK_ID, CONTACT_TIME, CONTACT_TIME_MS, SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DI_RATIO, FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_POSITION_COUNT, PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PW_MEAN, PW_MIN, PW_MAX, PA_MEAN, PA_MIN, PA_MAX, IS_STORED_PDW, NUM_PDW, COLLECTOR_ID, RADAR_LATITUDE, RADAR_LONGGITUDE, RADAR_NAME, RADARMODE_INDEX, THREAT_INDEX ) values( '%d', '%d', '%d', '%d', '%s', '%s', '%d', '%d', '%f', '%f', '%f', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%f', '%f', '%s', '%d', '%d' )", \
// 		pExt->aetData.uiOpInitID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pExt->aetData.aucTaskID, buffer, pLOBData->tiContactTimems, pLOBData->iSignalType, \
// 		pLOBData->fMeanDOA, pLOBData->fMinDOA, pLOBData->fMaxDOA, pLOBData->iDIRatio, \
// 		pLOBData->iFreqType, pLOBData->iFreqPatternType, pLOBData->fFreqPatternPeriod, pLOBData->fMeanFreq, pLOBData->fMinFreq, pLOBData->fMaxFreq, pLOBData->iFreqPositionCount, \
// 		pLOBData->iPRIType, pLOBData->iPRIPatternType, pLOBData->fPRIPatternPeriod, pLOBData->fMeanPRI, pLOBData->fMinPRI, pLOBData->fMaxPRI, pLOBData->fPRIJitterRatio, pLOBData->iPRIPositionCount, \
// 		pLOBData->fMeanPW, pLOBData->fMinPW, pLOBData->fMaxPW, pLOBData->fMeanPA, pLOBData->fMinPA, pLOBData->fMaxPA, \
// 		pLOBData->iIsStorePDW, pLOBData->iNumOfPDW, pLOBData->iCollectorID, \
// 		pLOBData->dRadarCollectionLatitude, pLOBData->dRadarCollectionLongitude, \
// 		pLOBData->aucRadarName, pLOBData->iRadarModeIndex, pLOBData->iThreatIndex );
// 
// 	theRS.Open( m_pszSQLString );
// 
// 	if( bUpdateRadarMode == true && pLOBData->iRadarModeIndex > 0 ) {
// 		__time32_t nowTime=_time32(NULL);
// 
// 		_localtime32_s( & stTime, & nowTime );
// 		strftime( buffer, 100, "%Y-%m-%d %H:%M:%S", & stTime);
// 
// 		// RADARMODE 테이블에 DATE_LAST_SEEN에 현재 날짜 및 시간을 업데이트 함.
// 		sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "UPDATE RADARMODE SET DATE_LAST_SEEN='%s' where RADAR_MODE_INDEX=%d", buffer, pLOBData->iRadarModeIndex );
// 		theRS.Open( m_pszSQLString );
// 
// 		// RADARMODE 테이블에 DATE_FIRST_SEEN에 현재 날짜 및 시간을 업데이트 함.
// 		sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "UPDATE RADARMODE SET DATE_FIRST_SEEN='%s' where ( RADAR_MODE_INDEX=%d and ISNULL( DATE_FIRST_SEEN, '')='' )", buffer, pLOBData->iRadarModeIndex );
// 		//theRS.Open( m_pszSQLString );
// 
// 	}
// 
// 	theRS.Close();
// 
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// }
// 
// /**
// 	* @brief		
// 	* @param		SRxLOBData * pLOBData
// 	* @return 	void
// 	* @date			2019/04/19 9:33
// */
// bool CMSSQL::InsertToDB_Position( SRxLOBData *pLOBData, SELLOBDATA_EXT *pExt )
// {
// 	DECLARE_BEGIN_CHECKODBC
// 
// 	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );
// 
// 	sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO LOB_POSITION (OP_INIT_ID, LOBID, ABTID, AETID, TASK_ID, POSITION_COUNT, SEQ_01, SEQ_02, SEQ_03, SEQ_04, SEQ_05, SEQ_06, SEQ_07, SEQ_08, SEQ_09, SEQ_10, SEQ_11, SEQ_12, SEQ_13, SEQ_14, SEQ_15, SEQ_16 ) values( '%d', '%d', '%d', '%d', '%s', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f')" , 
// 		pExt->aetData.uiOpInitID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pExt->aetData.aucTaskID, pLOBData->iPRIPositionCount,
// 		pLOBData->fPRISeq[0], pLOBData->fPRISeq[1], pLOBData->fPRISeq[2], pLOBData->fPRISeq[3], pLOBData->fPRISeq[4],
// 		pLOBData->fPRISeq[5], pLOBData->fPRISeq[6], pLOBData->fPRISeq[7], pLOBData->fPRISeq[8], pLOBData->fPRISeq[9],
// 		pLOBData->fPRISeq[10], pLOBData->fPRISeq[11], pLOBData->fPRISeq[12], pLOBData->fPRISeq[13], pLOBData->fPRISeq[14],
// 		pLOBData->fPRISeq[15], pLOBData->fPRISeq[16] );
// 
// 	theRS.Open( m_pszSQLString );
// 	theRS.Close();
// 
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// }
 
// bool CMSSQL::GetDB_LOB( int *pnLOB, SRxLOBData *pLOBData, SELLOBDATA_EXT *pLOBExt, char *pWhere, int iMaxItems )
// {
// 	*pnLOB = 0;
// 
// 	DECLARE_BEGIN_CHECKODBC
// 
// 	int index, iCnt=0;
// 
// 	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );
// 
// 	iCnt += sprintf_s( & m_pszSQLString[iCnt], MAX_SQL_SIZE-iCnt, "select OP_INIT_ID, SEQ_NUM, LOBID, ABTID, AETID, TASK_ID, CONTACT_TIME, CONTACT_TIME_MS, SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DI_RATIO, FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_POSITION_COUNT, PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PW_MEAN, PW_MIN, PW_MAX, PA_MEAN, PA_MIN, PA_MAX, IS_STORED_PDW, NUM_PDW, COLLECTOR_ID, RADAR_LATITUDE, RADAR_LONGGITUDE, RADAR_NAME, RADARMODE_INDEX, THREAT_INDEX from LOBDATA" );
// 	iCnt += sprintf_s( & m_pszSQLString[iCnt], MAX_SQL_SIZE-iCnt, " %s", pWhere );
// 	iCnt += sprintf_s( & m_pszSQLString[iCnt], MAX_SQL_SIZE-iCnt, " ORDER BY SEQ_NUM desc" );
// 
// 	theRS.Open( m_pszSQLString );
// 	while (!theRS.IsEof()) {
// 		index = 0;
// 
// 		theRS.GetFieldValue(index++, (int *) & pLOBExt->aetData.uiOpInitID );
// 
// 		theRS.GetFieldValue(index++, (int *) & pLOBData->uiSeqNum );
// 		theRS.GetFieldValue(index++, (int *) & pLOBData->uiLOBID );
// 		theRS.GetFieldValue(index++, (int *) & pLOBData->uiABTID );
// 		theRS.GetFieldValue(index++, (int *) & pLOBData->uiAETID );
// 
// 		theRS.GetFieldValue(index++, pLOBData->aucTaskID);
// 
// 		theRS.GetFieldTimeValue(index++, & pLOBData->tiContactTime );
// 		theRS.GetFieldValue(index++, (int *) &pLOBData->tiContactTimems);
// 
// 		theRS.GetFieldValue(index++, (int *)&pLOBData->iSignalType);
// 
// 		theRS.GetFieldValue(index++, &pLOBData->fMeanDOA);
// 		theRS.GetFieldValue(index++, &pLOBData->fMinDOA);
// 		theRS.GetFieldValue(index++, &pLOBData->fMaxDOA);
// 
// 		theRS.GetFieldValue(index++, &pLOBData->iDIRatio);
// 
// 		theRS.GetFieldValue(index++, (int *)&pLOBData->iFreqType);
// 		theRS.GetFieldValue(index++, &pLOBData->iFreqPatternType);
// 		theRS.GetFieldValue(index++, &pLOBData->fFreqPatternPeriod);
// 		theRS.GetFieldValue(index++, &pLOBData->fMeanFreq);
// 		theRS.GetFieldValue(index++, &pLOBData->fMinFreq);
// 		theRS.GetFieldValue(index++, &pLOBData->fMaxFreq);
// 		theRS.GetFieldValue(index++, &pLOBData->iFreqPositionCount);
// 
// 		theRS.GetFieldValue(index++, (int *) &pLOBData->iPRIType);
// 		theRS.GetFieldValue(index++, (int *) &pLOBData->iPRIPatternType);
// 		theRS.GetFieldValue(index++, &pLOBData->fPRIPatternPeriod);
// 		theRS.GetFieldValue(index++, &pLOBData->fMeanPRI);
// 		theRS.GetFieldValue(index++, &pLOBData->fMinPRI);
// 		theRS.GetFieldValue(index++, &pLOBData->fMaxPRI);
// 		theRS.GetFieldValue(index++, & pLOBData->fPRIJitterRatio);
// 		theRS.GetFieldValue(index++, (int *) &pLOBData->iPRIPositionCount);
// 
// 		theRS.GetFieldValue(index++, &pLOBData->fMeanPW);
// 		theRS.GetFieldValue(index++, &pLOBData->fMinPW);
// 		theRS.GetFieldValue(index++, &pLOBData->fMaxPW);
// 
// 		theRS.GetFieldValue(index++, &pLOBData->fMeanPA);
// 		theRS.GetFieldValue(index++, &pLOBData->fMinPA);
// 		theRS.GetFieldValue(index++, &pLOBData->fMaxPA);
// 
// 		theRS.GetFieldValue(index++, (int*)&pLOBData->iIsStorePDW);
// 		theRS.GetFieldValue(index++, (int*)&pLOBData->iNumOfPDW);
// 		theRS.GetFieldValue(index++, (int*)&pLOBData->iCollectorID);
// 
// 		theRS.GetFieldValue(index++, &pLOBData->dRadarCollectionLatitude);
// 		theRS.GetFieldValue(index++, &pLOBData->dRadarCollectionLongitude);
// 
// 		theRS.GetFieldValue(index++, pLOBData->aucRadarName);
// 		theRS.GetFieldValue(index++, (int*)&pLOBData->iRadarModeIndex);
// 		theRS.GetFieldValue(index++, (int*)&pLOBData->iThreatIndex);
// 
// 		++*pnLOB;
// 		++pLOBData;
// 		++pLOBExt;
// 
// 		if (iMaxItems != 0 && *pnLOB >= iMaxItems) {
// 			break;
// 		}
// 
// 		theRS.MoveNext();
// 
// 	}
// 
// 	theRS.Close();
// 
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// }
// 
// bool CMSSQL::GetDB_LOB_POSITION( int *pnLOB, SRxLOBData *pLOBData, char *pWhere, int iMaxItems )
// {
// 	*pnLOB = 0;
// 
// 	DECLARE_BEGIN_CHECKODBC
// 
// 	int i, index, iCnt=0;
// 
// 	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );
// 
// 	iCnt += sprintf_s( & m_pszSQLString[iCnt], MAX_SQL_SIZE-iCnt, "select POSITION_COUNT, SEQ_01, SEQ_02, SEQ_03, SEQ_04, SEQ_05, SEQ_06, SEQ_07, SEQ_08, SEQ_09, SEQ_10, SEQ_11, SEQ_12, SEQ_13, SEQ_14, SEQ_15, SEQ_16 FROM LOB_POSITION" );
// 	iCnt += sprintf_s( & m_pszSQLString[iCnt], MAX_SQL_SIZE-iCnt, " %s", pWhere );
// 
// 	theRS.Open( m_pszSQLString );
// 	while (!theRS.IsEof()) {
// 		index = 0;
// 
// 		theRS.GetFieldValue(index++, (int *) & pLOBData->iPRIPositionCount );
// 
// 		memset( pLOBData->fPRISeq, 0, sizeof(pLOBData->fPRISeq) );
// 		for( i=0 ; i < pLOBData->iPRIPositionCount ; ++i ) {
// 			theRS.GetFieldValue(index++, (float *) & pLOBData->fPRISeq[i] );
// 		}
// 
// 		++*pnLOB;
// 		++pLOBData;
// 
// 		if (iMaxItems != 0 && *pnLOB >= iMaxItems) {
// 			break;
// 		}
// 
// 		theRS.MoveNext();
// 
// 	}
// 
// 	theRS.Close();
// 
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// }
// 
// /**
// 	* @brief		
// 	* @param		SRxABTData * pABTData
// 	* @param		SELABTDATA_EXT * pABTExtData
// 	* @return 	bool
// 	* @date			2019/04/19 15:03
// */
// bool CMSSQL::InsertToDB_ABT( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, bool bUpdateThreat )
// {
// 	DECLARE_BEGIN_CHECKODBC
// 
// 	struct tm stTime;
// 	char buffer1[100], buffer2[100], buffer3[100];
// 
// 	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );
// 
// 	_localtime32_s(& stTime, & pABTData->tiFirstSeenTime );
// 	strftime( buffer1, 100, "%Y-%m-%d %H:%M:%S", &stTime);
// 	_localtime32_s(&stTime, & pABTData->tiLastSeenTime );
// 	strftime( buffer2, 100, "%Y-%m-%d %H:%M:%S", &stTime);
// 	_localtime32_s(&stTime, & pABTData->tiFinalAlarmTime );
// 	strftime( buffer3, 100, "%Y-%m-%d %H:%M:%S", &stTime);
// 	sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO ABTDATA (OP_INIT_ID, ABTID, AETID, FIRST_TIME, LAST_TIME, SIGNAL_TYPE, NUM_LOB, BEAM_VALIDITY, FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD_MEAN, FREQ_PATTERN_PERIOD_MIN, FREQ_PATTERN_PERIOD_MAX, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_POSITION_COUNT, PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD_MEAN, PRI_PATTERN_PERIOD_MIN, PRI_PATTERN_PERIOD_MAX, PRI_MEAN, PRI_MAX, PRI_MIN, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PW_MEAN, PW_MIN, PW_MAX, PA_MEAN, PA_MIN, PA_MAX, TOTAL_PDW, RADAR_NAME, RADARMODE_INDEX, THREAT_INDEX, PE_VALID, PE_LATITUDE, PE_LONGGITUDE, PE_CEP, PE_MINOR_AXIS, PE_MAJOR_AXIS, PE_THETA, PE_DISTANCE, ALARM_TIME, STAT ) values( '%d', '%d', '%d', '%s', '%s', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%s', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%s', '%d' )", \
// 												pABTExtData->uiOpInitID, pABTData->uiABTID, pABTData->uiAETID, buffer1, buffer2, \
// 												pABTData->iSignalType, pABTData->uiCoLOB, pABTData->iValidity, \
// 												pABTData->iFreqType, pABTData->iFreqPatternType, pABTData->fFreqPatternPeriodMean, pABTData->fFreqPatternPeriodMin, pABTData->fFreqPatternPeriodMax, pABTData->fMeanFreq, pABTData->fMinFreq, pABTData->fMaxFreq, pABTData->iFreqPositionCount, \
// 												pABTData->iPRIType, pABTData->iPRIPatternType, pABTData->fPRIPatternPeriodMean, pABTData->fPRIPatternPeriodMin, pABTData->fPRIPatternPeriodMax, pABTData->fMeanPRI, pABTData->fMinPRI, pABTData->fMaxPRI, pABTData->fPRIJitterRatio, pABTData->iPRIPositionCount, \
// 												pABTData->fMeanPW, pABTData->fMinPW, pABTData->fMaxPW, pABTData->fMeanPA, pABTData->fMinPA, pABTData->fMaxPA, \
// 												pABTData->uiTotalOfPDW, pABTData->aucRadarName, pABTData->iRadarModeIndex, pABTData->iThreatIndex, \
// 												pABTData->iPEValid, pABTData->dLatitude, pABTData->dLongitude, pABTData->fCEP, pABTData->fMinorAxis, pABTData->fMajorAxis, pABTData->fTheta, pABTData->fDistanceErrorOfThreat, \
// 												buffer3, pABTData->iStat );
// 
// 
// 	theRS.Open( m_pszSQLString );
// 
// 	if( bUpdateThreat == true && pABTData->iThreatIndex > 0 ) {
// 		__time32_t nowTime=_time32(NULL);
// 
// 		_localtime32_s( & stTime, & nowTime );
// 		strftime( buffer1, 100, "%Y-%m-%d %H:%M:%S", & stTime);
// 
// 		// RADARMODE 테이블에 DATE_LAST_SEEN에 현재 날짜 및 시간을 업데이트 함.
// 		sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "UPDATE THREAT SET DATE_LAST_SEEN='%s' where THREAT_INDEX=%d", buffer1, pABTData->iThreatIndex );
// 		theRS.Open( m_pszSQLString );
// 	}
// 
// 	theRS.Close();
// 
// 	// 아래에서 다운이 되면 SQL 버퍼수를 늘히면 됩니다.
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// 
// }
// 
// /**
// 	* @brief		
// 	* @param		SRxLOBData * pLOBData
// 	* @return 	void
// 	* @date			2019/04/19 9:33
// */
// bool CMSSQL::InsertToDB_Position( SRxLOBData *pLOBData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
// {
// 	DECLARE_BEGIN_CHECKODBC
// 
// 	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );
// 
// 	sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO ABT_POSITION ( OP_INIT_ID, LOBID, ABTID, AETID, TASK_ID, POSITION_COUNT, SEQ_01, SEQ_02, SEQ_03, SEQ_04, SEQ_05, SEQ_06, SEQ_08, SEQ_07, SEQ_09, SEQ_10, SEQ_11, SEQ_13, SEQ_12, SEQ_14, SEQ_15, SEQ_16 ) values( '%d', '%d', '%d', '%d', '%s', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f')" , 
// 		pABTExtData->uiOpInitID, pLOBData->uiLOBID, pABTData->uiABTID, pABTData->uiAETID, pLOBData->aucTaskID, pABTData->iPRIPositionCount,
// 		pABTData->fPRISeq[0], pABTData->fPRISeq[1], pABTData->fPRISeq[2], pABTData->fPRISeq[3], pABTData->fPRISeq[4],
// 		pABTData->fPRISeq[5], pABTData->fPRISeq[6], pABTData->fPRISeq[7], pABTData->fPRISeq[8], pABTData->fPRISeq[9],
// 		pABTData->fPRISeq[10], pABTData->fPRISeq[11], pABTData->fPRISeq[12], pABTData->fPRISeq[13], pABTData->fPRISeq[14],
// 		pABTData->fPRISeq[15], pABTData->fPRISeq[16] );
// 
// 	theRS.Open( m_pszSQLString );
// 	theRS.Close();
// 
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// }
// 
// 
// bool CMSSQL::LoadLOBData(int *pnLOBData, SRxLOBData *pLOBData, int iMaxItems)
// {
// 	DECLARE_BEGIN_CHECKODBC
// 	int index;
// 
// 	*pnLOBData = 0;
// 
// 	CODBCRecordset theRS = CODBCRecordset(m_pMyODBC);
// 
// 	sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "SELECT top(%d) SEQ_NUM, LOBID, ABTID, AETID, TASK_ID, CONTACT_TIME, CONTACT_TIME_MS, \
// 													SIGNAL_TYPE, DOA_MEAN, DOA_MAX, DOA_MIN, DI_RATIO, FREQ_TYPE, FREQ_PATTERN_TYPE, \
// 													FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_POSITION_COUNT, PRI_TYPE, \
// 													PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_JITTER_RATIO, \
// 													PRI_POSITION_COUNT, PW_MEAN, PW_MIN, PW_MAX, PA_MEAN, PA_MIN, PA_MAX, IS_STORED_PDW, \
// 													NUM_PDW, COLLECTOR_ID, RADAR_LATITUDE, RADAR_LONGGITUDE, RADAR_NAME, RADARMODE_INDEX, \
// 													THREAT_INDEX FROM LOBDATA ORDER BY SEQ_NUM desc", iMaxItems );
// 
// 	theRS.Open(m_pszSQLString);
// 	while (!theRS.IsEof()) {
// 		index = 0;
// 		theRS.GetFieldValue(index++, (int *) & pLOBData->uiSeqNum );
// 		theRS.GetFieldValue(index++, (int *) & pLOBData->uiLOBID );
// 		theRS.GetFieldValue(index++, (int *) & pLOBData->uiABTID );
// 		theRS.GetFieldValue(index++, (int *) & pLOBData->uiAETID );
// 
// 		theRS.GetFieldValue(index++, pLOBData->aucTaskID);
// 
// 		theRS.GetFieldTimeValue(index++, & pLOBData->tiContactTime );
// 		theRS.GetFieldValue(index++, (int *) &pLOBData->tiContactTimems);
// 
// 		theRS.GetFieldValue(index++, (int *)&pLOBData->iSignalType);
// 
// 		theRS.GetFieldValue(index++, &pLOBData->fMeanDOA);
// 		theRS.GetFieldValue(index++, &pLOBData->fMaxDOA);
// 		theRS.GetFieldValue(index++, &pLOBData->fMinDOA);
// 
// 		theRS.GetFieldValue(index++, &pLOBData->iDIRatio);
// 
// 		theRS.GetFieldValue(index++, (int *)&pLOBData->iFreqType);
// 		theRS.GetFieldValue(index++, &pLOBData->iFreqPatternType);
// 		theRS.GetFieldValue(index++, &pLOBData->fFreqPatternPeriod);
// 		theRS.GetFieldValue(index++, &pLOBData->fMeanFreq);
// 		theRS.GetFieldValue(index++, &pLOBData->fMaxFreq);
// 		theRS.GetFieldValue(index++, &pLOBData->fMinFreq);
// 		theRS.GetFieldValue(index++, &pLOBData->iFreqPositionCount);
// 
// 		theRS.GetFieldValue(index++, (int *) &pLOBData->iPRIType);
// 		theRS.GetFieldValue(index++, (int *) &pLOBData->iPRIPatternType);
// 		theRS.GetFieldValue(index++, &pLOBData->fPRIPatternPeriod);
// 		theRS.GetFieldValue(index++, &pLOBData->fMeanPRI);
// 		theRS.GetFieldValue(index++, &pLOBData->fMaxPRI);
// 		theRS.GetFieldValue(index++, &pLOBData->fMinPRI);
// 		theRS.GetFieldValue(index++, & pLOBData->fPRIJitterRatio);
// 		theRS.GetFieldValue(index++, (int *) &pLOBData->iPRIPositionCount);
// 
// 		theRS.GetFieldValue(index++, &pLOBData->fMeanPW);
// 		theRS.GetFieldValue(index++, &pLOBData->fMaxPW);
// 		theRS.GetFieldValue(index++, &pLOBData->fMinPW);
// 
// 		theRS.GetFieldValue(index++, &pLOBData->fMeanPA);
// 		theRS.GetFieldValue(index++, &pLOBData->fMaxPA);
// 		theRS.GetFieldValue(index++, &pLOBData->fMinPA);
// 
// 		theRS.GetFieldValue(index++, (int*)&pLOBData->iIsStorePDW);
// 		theRS.GetFieldValue(index++, (int*)&pLOBData->iNumOfPDW);
// 		theRS.GetFieldValue(index++, (int*)&pLOBData->iCollectorID);
// 
// 		theRS.GetFieldValue(index++, &pLOBData->dRadarCollectionLatitude);
// 		theRS.GetFieldValue(index++, &pLOBData->dRadarCollectionLongitude);
// 
// 		theRS.GetFieldValue(index++, pLOBData->aucRadarName);
// 		theRS.GetFieldValue(index++, (int*)&pLOBData->iRadarModeIndex);
// 		theRS.GetFieldValue(index++, (int*)&pLOBData->iThreatIndex);
// 
// 		++*pnLOBData;
// 		++pLOBData;
// 
// 		if (iMaxItems != 0 && *pnLOBData >= iMaxItems) {
// 			break;
// 		}
// 
// 		theRS.MoveNext();
// 	
// 	}
// 
// 	theRS.Close();
// 
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// }
// 
// 
// /**
// 	* @brief		레이더 모드와 위협 라이브러리를 로딩한다.
// 	* @return 	void
// 	* @date			2019/04/22 11:04
// */
// bool CMSSQL::LoadRadarModeData( int *pnRadarMode, SRadarMode *pRadarMode, int iMaxItems )
// {
// 	*pnRadarMode = 0;
// 
// 	DECLARE_BEGIN_CHECKODBC
// 	int index;
// 
// 	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );
// 
// 	sprintf_s( m_pszSQLString, MAX_SQL_SIZE,  "SELECT * FROM RADARMODE ORDER BY RADAR_MODE_INDEX" );
// 
// 	theRS.Open( m_pszSQLString );
// 
// 	while (!theRS.IsEof()) {
// 		index = 0;
// 
// 		theRS.GetFieldValue( index++, & pRadarMode->iRadarModeIndex );
// 
// 		theRS.GetFieldValue( index++, pRadarMode->szRadarName );
// 
// 		theRS.GetFieldTimeValue( index++, & pRadarMode->tiCreated );
// 		theRS.GetFieldTimeValue( index++, & pRadarMode->tiLastUpdated );
// 
// 		theRS.GetFieldTimeValue( index++, & pRadarMode->tiFirstSeen );
// 		theRS.GetFieldTimeValue( index++, & pRadarMode->tiLastSeen );
// 
// 		theRS.GetFieldValue( index++, (int *) & pRadarMode->ePlatform );
// 
// 		theRS.GetFieldValue( index++, (int *) & pRadarMode->eSignalType );
// 
// 		theRS.GetFieldValue( index++, (int *) & pRadarMode->eFreqType );
// 		theRS.GetFieldValue( index++, & pRadarMode->fRF_TypicalMin );
// 		theRS.GetFieldValue( index++, & pRadarMode->fRF_TypicalMax );
// 		theRS.GetFieldValue( index++, (int *) & pRadarMode->eRF_PatternType );
// 		theRS.GetFieldValue( index++, & pRadarMode->nRF_NumPositions );
// 		theRS.GetFieldValue( index++, & pRadarMode->fRF_PatternPeriodMin );
// 		theRS.GetFieldValue( index++, & pRadarMode->fRF_PatternPeriodMax );
// 
// 		theRS.GetFieldValue( index++, (int *) & pRadarMode->ePRIType );
// 		theRS.GetFieldValue( index++, & pRadarMode->fPRI_TypicalMin );
// 		theRS.GetFieldValue( index++, & pRadarMode->fPRI_TypicalMax );
// 		theRS.GetFieldValue( index++, (int *) & pRadarMode->ePRI_PatternType );
// 		theRS.GetFieldValue( index++, & pRadarMode->nPRI_NumPositions );
// 		theRS.GetFieldValue( index++, & pRadarMode->fPRI_PatternPeriodMin );
// 		theRS.GetFieldValue( index++, & pRadarMode->fPRI_PatternPeriodMax );
// 
// 		theRS.GetFieldValue( index++, & pRadarMode->fPD_TypicalMin );
// 		theRS.GetFieldValue( index++, & pRadarMode->fPD_TypicalMax );
// 
// 		theRS.GetFieldValue( index++, (int *) & pRadarMode->eValidation );
// 
// 		if( pRadarMode->eValidation == enumValidated ) {
// 			++ *pnRadarMode;
// 			++ pRadarMode;
// 		}
// 
// 		if( iMaxItems != 0 && *pnRadarMode >= iMaxItems ) {
// 			break;
// 		}
// 
// 		theRS.MoveNext();
// 	}
// 
// 	theRS.Close();
// 
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// }

/**
	* @brief		
	* @param		vector<SRadarMode_PRISequence_Values * > * pVecRadarMode_PRISequence
	* @param		int nMaxRadarMode
	* @return 	void
	* @date			2019/04/24 15:39
*/
// bool CMSSQL::LoadRadarMode_PRISequence( vector<SRadarMode_PRISequence_Values*> *pVecRadarMode_PRISequence, int nMaxRadarMode )
// {
// 	DECLARE_BEGIN_CHECKODBC
// 	int index;
// 
// 	SRadarMode_PRISequence_Values *pRadarMode_PRISequence_Values;
// 
// 	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );
// 
// 	sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "SELECT RADAR_MODE_INDEX, PRI_SEQ_ID, PRI_MIN, PRI_MAX FROM RADARMODE_PRI_SEQUENCE ORDER BY RADAR_MODE_INDEX ASC, PRI_SEQ_ID ASC" );
// 	theRS.Open( m_pszSQLString );
// 
// 	pVecRadarMode_PRISequence->reserve( nMaxRadarMode * MAX_FREQ_PRI_STEP );
// 	DeletePointers( *pVecRadarMode_PRISequence );
// 
// 	while (!theRS.IsEof()) {
// 		index = 0;
// 
// 		pRadarMode_PRISequence_Values = new SRadarMode_PRISequence_Values;
// 
// 		theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->iRadarModeIndex );
// 		theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->iPRI_Index );
// 
// 		theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->fPRI_Min );
// 		theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->fPRI_Max );
// 
// 		pVecRadarMode_PRISequence->push_back( pRadarMode_PRISequence_Values );
// 
// 		theRS.MoveNext();
// 
// 	}
// 
// 	theRS.Close();
// 
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// }

/**
	* @brief		
	* @param		int * pnThreat
	* @param		SThreat * pThreat
	* @param		int iMaxItems
	* @return 	bool
	* @date			2019/04/22 15:52
*/
// bool CMSSQL::LoadThreatData( int *pnThreat, SThreat *pThreat, int iMaxItems )
// {
// 	DECLARE_BEGIN_CHECKODBC
// 	int index;
// 
// 	*pnThreat = 0;
// 
// 	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );
// 
// 	sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "SELECT THREAT_INDEX, RADAR_MODE_NAME, THREAT_NAME, LATITUDE, LONGITUDE, SITE_NAME, THREAT_PLATFORM, ID_RANGE FROM THREAT" );
// 
// 	theRS.Open( m_pszSQLString );
// 
// 	while (!theRS.IsEof()) {
// 		index = 0;
// 
// 		theRS.GetFieldValue( index++, & pThreat->iThreatIndex );
// 		theRS.GetFieldValue( index++, pThreat->szRadarModeName );
// 		theRS.GetFieldValue( index++, pThreat->szThreatName );
// 
// 		theRS.GetFieldValue( index++, & pThreat->fLatitude );
// 		theRS.GetFieldValue( index++, & pThreat->fLongitude );
// 
// 		theRS.GetFieldValue( index++, pThreat->szSiteName );
// 
// 		theRS.GetFieldValue( index++, (int *) & pThreat->enPlatform );
// 
// 		theRS.GetFieldValue( index++, & pThreat->fIdRange );
// 
// 		++ *pnThreat;
// 		++ pThreat;
// 
// 		if( iMaxItems != 0 && *pnThreat >= iMaxItems ) {
// 			break;
// 		}
// 
// 		theRS.MoveNext();
// 
// 	}
// 
// 	theRS.Close();
// 
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// }


// bool CMSSQL::LoadFieldOfTable( int *pCoField, char **pField, char *pTable )
// {
// 	DECLARE_BEGIN_CHECKODBC
// 	*pCoField=0;
// 
// 	CODBCRecordset theRS = CODBCRecordset(m_pMyODBC);
// 
// 	sprintf_s(m_pszSQLString, MAX_SQL_SIZE, "SELECT name from syscolumns where id=object_id('%s') order by colid", pTable );
// 
// 	theRS.Open(m_pszSQLString);
// 	while (!theRS.IsEof()) {
// 		// 테이블의 필드 길이를 한번만 체크한다.
// 		if( *pCoField == 0 ) {
// 			if( theRS.GetFieldLength(0) >= MAX_OF_COLUMN_LENGTH ) {
// 				theRS.Close();
// 				CAST_THROW_MESSAGE 
// 			}
// 		}
// 		
// 		theRS.GetFieldValue(0, pField[*pCoField] );
// 		++ *pCoField;
// 		
// 		theRS.MoveNext();
// 
// 	}
// 
// 	theRS.Close();
// 
// 	DECLARE_END_CHECKODBC
// 	DECLARE_RETURN
// }
