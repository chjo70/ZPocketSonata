//  MODULE:   mssql.h
//
//	AUTHOR: Carlos Antollini 
//
//  mailto: cantollini@hotmail.com
//
//	Date: 08/21/2001
//
//	Version 1.11

#pragma once

#include "odbccore.h"

#include "../Utils/clog.h"


//#include "../../OFP/Identify/ELCEDLibDataType2.h"
#include "../Anal/EmitterMerge/ELEmitterDataType.h"
#include "../Anal/EmitterMerge/PositionEstimationAlg.h"

#include "../Anal/EmitterMerge/ELGMIMsgDefn.h"
#include "../Anal/EmitterMerge/ElintRsltDataTypedb.h"

//#include "../../OFP/Include/globals.h"

//#define MAX_SQL_SIZE								(10000)

#define MAX_OF_COLUMN_LENGTH				(130)
#define MAX_COUNT_OF_FIELD					(100)

// 에러 정의
//#define SQL_ERROR_DISCONNECTION				(0xFFFF)
//#define SQL_ERROR_QUERY								(0xFFF0)
//#define SQL_ERROR_FIELD_LENGTH				(0xFFE0)

#define DECLARE_BEGIN_CHECKODBC				    try { CheckConnection();
#define DECLARE_END_CHECKODBC					} catch( int iErrorException ) { printf( "\n Error !!!" ); if( g_pTheLog ) { Log( enError, "DB 쿼리 에러" ); } else TRACE( "DB 쿼리 에러" );ErrorException( iErrorException ); }
#define	DECLARE_RETURN							return m_bRet;

#define CAST_THROW_MESSAGE						{ m_iErrorException = SQL_ERROR_FIELD_LENGTH; throw m_iErrorException; }

#ifdef _ELINT_
// 인천공항
// #define DB_SERVER_IP_ADDRESS			"192.168.0.41"
#else
// X 밴드 일때 DB 서버 어드레스
//#define DB_SERVER_IP_ADDRESS			"30.30.30.54"
#define DB_SERVER_IP_ADDRESS			"127.0.0.1"
#endif



class CMSSQL 
{
public:
	CODBCDatabase *m_pMyODBC;

private:
	static bool m_bTryConnect;

	//int m_iErrorException;

	//char *m_pszSQLString;

protected:
	bool m_bRet;
    int m_iErrorException;

	CMSSQL( CODBCDatabase *pODBCDataBase )
	{
		m_pMyODBC = pODBCDataBase;
		//m_pszSQLString = (char *) malloc( sizeof(char) * MAX_SQL_SIZE );

	};

	~CMSSQL()
	{
		//free( m_pszSQLString );
	};

	void Init()
	{
        BOOL bRet;
		char szConnect[100];

		if( m_bTryConnect == false && m_pMyODBC->IsConnected() == false ) {
			char szOut[1024];

			m_pMyODBC->SetConnectionTimeout(1);

            memset( szOut, 0, sizeof(szOut) );

			//enPosition enPos=GetPosition();
			sprintf( szConnect, "DRIVER={SQL Server};SERVER=%s, 1433;UID=sa;PWD=devrms;DATABASE=ELINT;" , DB_SERVER_IP_ADDRESS );
			bRet = m_pMyODBC->DriverConnect( szConnect, szOut ); 
			if( bRet == FALSE ) {
				sprintf( szConnect, "SQL 서버(%s)에 연결이 안 됩니다. DB 서버 IP를 확인하거나 Firewall을 확인해주세요..." , DB_SERVER_IP_ADDRESS );
				AfxMessageBox( szConnect );

				m_bTryConnect = true;
			}

// 			if( enPos == enBuiltIn ) {
// 				//if( ! m_pMyODBC->DriverConnect("DRIVER={SQL Server};SERVER=192.168.0.41, 1433;UID=netcususer;PWD=netcusgood;DATABASE=ELINT;", szOut) ) {
//                 bRet = m_pMyODBC->DriverConnect("DRIVER={SQL Server};SERVER=127.0.0.1, 1433;UID=sa;PWD=devrms;DATABASE=ELINT;", szOut ); 
//                 if( bRet == FALSE ) {
// 					AfxMessageBox( "SQL 서버에 연결이 안 됩니다. DB 서버와 연결할 수 없습니다. DB 서버를 확인하거나 랜 선을 확인해주세요..." );
// 					//Log( enError, "SQL 서버에 연결이 안 됩니다. DB 서버와 연결할 수 없습니다. DB 서버를 확인하거나 랜 선을 확인해주세요..." );
// 				}
// 
// 			}
// 			else if( enPos == enMyHome ) {
//                 bRet = m_pMyODBC->DriverConnect("DRIVER={SQL Server};SERVER=192.168.0.156, 1433;UID=sa;PWD=fractal;DATABASE=ELINT;Trusted_Connection=yes;", szOut ); 
//                 if( bRet == FALSE ) {
// 					AfxMessageBox( "SQL 서버에 연결이 안 됩니다. 개인용 컴퓨터에 SQL 서버를 설치하고 포트를 확인해주세요..." );
// 					//Log( enError, "SQL 서버에 연결이 안 됩니다. 개인용 컴퓨터에 SQL 서버를 설치하고 포트를 확인해주세요..." );
// 				}
// 			}
// 			else {
//                 bRet = m_pMyODBC->DriverConnect("DRIVER={SQL Server};SERVER=127.0.0.1, 1433;UID=sa;PWD=devrms;DATABASE=ELINT;", szOut ); 
//                 if( bRet == FALSE ) {
// 					AfxMessageBox( "SQL 서버에 연결이 안 됩니다. 사무용 컴퓨터에 SQL 서버를 설치하고 포트를 확인해주세요..." );
// 					//Log( enError, "SQL 서버에 연결이 안 됩니다. 사무용 컴퓨터에 SQL 서버를 설치하고 포트를 확인해주세요..." );
// 				}
// 			}
// 
            if( bRet == TRUE ) {
                //Log( enNormal, "SQL 서버[0x%p]에 정상 연결됐습니다..." , m_pMyODBC );
            }

		}
	};

	// 에러 처리
	void CheckConnection();
	void ErrorException( int iErrorException );
	void DisplayErrorException( int iErrorException );

    // LOB 데이터 갖고 오기
    bool LoadLOBData(int *pnLOBData, SRxLOBData *pLOBData, int iMaxItems);

	// 레이더 모드 및 위협 테이블 로딩
	bool LoadRadarModeData( int *pnRadarMode, SRadarMode *pRadarMode, int iMaxItems=0 );
	//bool LoadRadarMode_PRISequence( vector<SRadarMode_PRISequence_Values*> *pVecRadarMode_PRISequence, int nMaxRadarMode=0 );
	bool LoadThreatData( int *pnThreat, SThreat *pThreat, int iMaxItems=0 );

	// SQL 쿼리 함수
	int GetLONGData( char *pSQLString );
	bool InsertToDB_LOB( SRxLOBData *pLOBData, SELLOBDATA_EXT *pExt, bool bUpdateRadarMode=false );
	bool InsertToDB_Position( SRxLOBData *pLOBData, SELLOBDATA_EXT *pExt );
	bool InsertToDB_ABT( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, bool bUpdateThreat=false );
	bool InsertToDB_Position( SRxLOBData *pLOBData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData );

	bool GetDB_LOB( int *pnLOB, SRxLOBData *pLOBData, SELLOBDATA_EXT *pExt, char *pWhere, int iMaxItems );
	bool GetDB_LOB_POSITION( int *pnLOB, SRxLOBData *pLOBData, char *pWhere, int iMaxItems );

	// 테이블에서 필드명 갖고 오기
	bool LoadFieldOfTable( int *pCoField, char **pFiled, char *pTable );

    inline CODBCDatabase *GetDBCDatabase() { return m_pMyODBC; }

};