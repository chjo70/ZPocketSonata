
// DeltaGraphDoc.h : CDeltaGraphDoc 클래스의 인터페이스
//


#pragma once

#include "../../Files/Anal/SigAnal/_Macro.h"
#include "../../Files/Anal/SigAnal/_Struct.h"

#include "../../Files/Anal/Collect/DataFile/DataFile.h"

class CDeltaGraphDoc : public CDocument
{
private:
	CMainFrame *m_pFrame;
	CString m_strPathname;

	CDataFile *m_pTheDataFile;

	ENUM_UnitType m_enUnitType;
	ENUM_DataType m_enDataType;

private:
	

public:
	bool ReadDataFile( DWORD dwOffset=0, STR_FILTER_SETUP *pstFilterSetup=NULL, bool bCountOfWindow=false );

	bool OpenFile( CString &strPathname, STR_FILTER_SETUP *pstFilterSetup=NULL );
	UINT GetPDWDataItems();

	ENUM_UnitType WhatUnitType();
	ENUM_DataType WhatDataType();

    ENUM_DataType GetDataType();

	inline int GetFileIndex() { return m_pTheDataFile->GetFileIndex(); }
	
	inline UINT GetDataItems() { return m_pTheDataFile->GetDataItems(); }
	inline ENUM_UnitType GetUnitType() { return m_enUnitType; /* .GetUnitType(); */ }
	inline void *GetData() { return m_pTheDataFile->GetData(); }
    inline void *GetRealData() { return m_pTheDataFile->GetRealData(); }

	inline int GetFilteredDataItems() { return m_pTheDataFile->GetFilteredDataItems(); }
    inline int GetFilteredRealDataItems() { return m_pTheDataFile->GetFilteredRealDataItems(); }
	inline UINT GetWindowNumber() { return m_pTheDataFile->GetWindowNumber(); }


protected: // serialization에서만 만들어집니다.
	CDeltaGraphDoc();
	DECLARE_DYNCREATE(CDeltaGraphDoc)

// 특성입니다.
public:

// 작업입니다.
public:

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
	virtual ~CDeltaGraphDoc();
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
};
