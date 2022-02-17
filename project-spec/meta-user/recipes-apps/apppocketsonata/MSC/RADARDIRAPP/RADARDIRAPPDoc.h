
// RADARDIRAPPDoc.h : CRADARDIRAPPDoc Ŭ������ �������̽�
//


#pragma once


#include "../../files/Anal/Collect/DataFile/DataFile.h"


class CRADARDIRAPPDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CRADARDIRAPPDoc();
	DECLARE_DYNCREATE(CRADARDIRAPPDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
private:
	CMainFrame *m_pMainFrame;
	CRADARDIRAPPDoc *m_pDoc;

	CString m_strPathname;

    CDataFile m_theDataFile;

    STR_PDWDATA m_stPDWData;

private:
	void ReadDataFile();

public:
	bool OpenFile( CString &strPathname );

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
	virtual ~CRADARDIRAPPDoc();
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
};
