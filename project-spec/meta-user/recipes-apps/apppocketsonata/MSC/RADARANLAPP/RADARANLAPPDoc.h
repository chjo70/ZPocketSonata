
// RADARANLAPPDoc.h : CRADARANLAPPDoc Ŭ������ �������̽�
//


#pragma once

#include "../../files/ODBC/MSSQL.h"

#include "../RadarAnl/RadarAnlAlgorithm.h"


class CRADARANLAPPDoc : public CDocument, public CMSSQL
{
protected: // serialization������ ��������ϴ�.
	CRADARANLAPPDoc();
	DECLARE_DYNCREATE(CRADARANLAPPDoc)

// Ư���Դϴ�.
private:
	static CODBCDatabase m_theMyODBC;

public:

// �۾��Դϴ�.
public:
	//inline int GetLOBData( SRxLOBData *pLOBData, SELLOBDATA_EXT *pExt, char *pWhere ) { return GetDB_LOB( pLOBData, pExt, pWhere ); }
	inline void GetFieldNameOfTable( int *pCoField, char **pField, char *pTable ) { LoadFieldOfTable( pCoField, pField, pTable ); }
	//inline void GetLOBData( int *pnLOBData, SRxLOBData *pLOBData, int iMaxItems ) { GetLOBData( pnLOBData, pLOBData, iMaxItems ); }

	void OnFileOpen();
	double GCAzimuth(double lat1, double lon1, double lat2, double lon2, bool bInitial=true);

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CRADARANLAPPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
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
