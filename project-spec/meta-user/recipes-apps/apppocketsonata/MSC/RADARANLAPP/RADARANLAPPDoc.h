
// RADARANLAPPDoc.h : CRADARANLAPPDoc 클래스의 인터페이스
//


#pragma once

#include "../../files/ODBC/MSSQL.h"

#include "../RadarAnl/RadarAnlAlgorithm.h"


class CRADARANLAPPDoc : public CDocument, public CMSSQL
{
protected: // serialization에서만 만들어집니다.
	CRADARANLAPPDoc();
	DECLARE_DYNCREATE(CRADARANLAPPDoc)

// 특성입니다.
private:
	static CODBCDatabase m_theMyODBC;

public:

// 작업입니다.
public:
	//inline int GetLOBData( SRxLOBData *pLOBData, SELLOBDATA_EXT *pExt, char *pWhere ) { return GetDB_LOB( pLOBData, pExt, pWhere ); }
	inline void GetFieldNameOfTable( int *pCoField, char **pField, char *pTable ) { LoadFieldOfTable( pCoField, pField, pTable ); }
	//inline void GetLOBData( int *pnLOBData, SRxLOBData *pLOBData, int iMaxItems ) { GetLOBData( pnLOBData, pLOBData, iMaxItems ); }

	void OnFileOpen();
	double GCAzimuth(double lat1, double lon1, double lat2, double lon2, bool bInitial=true);

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CRADARANLAPPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:
	CString m_strIniFilename;
	char m_szProgramPath[_MAX_PATH];

	STR_LOBDATA m_stLOBData;

    char m_szSQLString[4000];

public:
	afx_msg void OnOpInit();

	void WriteProfile( char *pAppName, char *pAppKey, char *pValue );
	void MakeIniFilename();
	void LoadProfile( char *pValue, int iSize, char *pAppName, char *pAppKey );
	void Init();
	void Run( int nLOB, SRxLOBData *pLOBData, SELLOBDATA_EXT *pLOBExt );

    bool GetDB_LOB( int *pnLOB, SRxLOBData *pLOBData, SELLOBDATA_EXT *pLOBExt, char *pWhere, int iMaxItems );
    bool LoadFieldOfTable( int *pCoField, char **pField, char *pTable );
    bool GetDB_LOB_POSITION( int *pnLOB, SRxLOBData *pLOBData, char *pWhere, int iMaxItems );
};
