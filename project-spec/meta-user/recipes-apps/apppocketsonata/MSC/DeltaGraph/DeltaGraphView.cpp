
// DeltaGraphView.cpp : CDeltaGraphView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "DeltaGraph.h"
#endif

#include "MainFrm.h"

#include "DeltaGraphDoc.h"
#include "DeltaGraphView.h"

//#include "../ShuDeltaGraph/Log/LogDebug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDeltaGraphView

IMPLEMENT_DYNCREATE(CDeltaGraphView, CFormView)

BEGIN_MESSAGE_MAP(CDeltaGraphView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, &CDeltaGraphView::OnBnClickedButtonPrevious)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CDeltaGraphView::OnBnClickedButtonNext)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_PDW, &CDeltaGraphView::OnLvnGetdispinfoListPdw)
END_MESSAGE_MAP()


BEGIN_EASYSIZE_MAP(CDeltaGraphView)
	EASYSIZE(IDC_LIST_PDW,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_BUTTON_PREVIOUS,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_BUTTON_NEXT,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
END_EASYSIZE_MAP

// CDeltaGraphView ����/�Ҹ�

CDeltaGraphView::CDeltaGraphView()
	: CFormView(CDeltaGraphView::IDD)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	CLEAR_EASYSIZE;

}

CDeltaGraphView::~CDeltaGraphView()
{
}

void CDeltaGraphView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PDW, m_CListRawData);
	DDX_Control(pDX, IDC_SPIN_FRQ_LOW, m_CSpinPage);
}

BOOL CDeltaGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

/**
 * @brief     
 * @return    void
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/10 10:05:12
 * @warning   
 */
 void CDeltaGraphView::OnInitialUpdate()
{
	bool bRet;

	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	m_pDoc = ( CDeltaGraphDoc * ) GetDocument();

	InitListCtrl();
	InitButton();
	InitSpinCtrl();

	bRet = m_pDoc->ReadDataFile( 0, NULL, true );
	ShowGraph();

	GetDlgItem( IDC_BUTTON_NEXT )->EnableWindow( ! bRet );

	INIT_EASYSIZE;

}

void CDeltaGraphView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDeltaGraphView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDeltaGraphView ����

#ifdef _DEBUG
void CDeltaGraphView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDeltaGraphView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDeltaGraphDoc* CDeltaGraphView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDeltaGraphDoc)));
	return (CDeltaGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CDeltaGraphView �޽��� ó����

void CDeltaGraphView::InitButton()
{
	GetDlgItem(IDC_BUTTON_PREVIOUS)->EnableWindow( FALSE );
}

void CDeltaGraphView::InitSpinCtrl()
{

	m_CSpinPage.SetDecimalPlaces(0);
	m_CSpinPage.SetTrimTrailingZeros(FALSE);
	m_CSpinPage.SetRangeAndDelta( 0, 10000, 10.0 );
	m_CSpinPage.SetPos( (double) 0 );

}

#define TEXT_WIDTH			(18)
/**
 * @brief     
 * @return    void
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/09 9:19:02
 * @warning   
 */
void CDeltaGraphView::InitListCtrl( bool bInit )
{
	int j=0;

	if( m_pDoc->GetDataType() == en_PDW_DATA ) {
		if( bInit == true ) {
			m_CListRawData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | 0x00004000);
			//m_CListPDW.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

			m_CListRawData.InsertColumn( j++, _T("����"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("����  ")), -1 );
			m_CListRawData.InsertColumn( j++, _T("��ȣ ����"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("��ȣ ����")), -1 ); 
			m_CListRawData.InsertColumn( j++, _T("TOA[s]/TOA"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("TOA[s]/TOA[s]")), -1 ); 
			m_CListRawData.InsertColumn( j++, _T("DTOA[s]"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("DTOA[s]")), -1 ); 
			m_CListRawData.InsertColumn( j++, _T("DV"), LVCFMT_CENTER, TEXT_WIDTH*strlen(_T("DV")), -1 ); 
			m_CListRawData.InsertColumn( j++, _T("����[��]"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("����[��]")), -1 ); 
			m_CListRawData.InsertColumn( j++, _T("���ļ�[MHz]"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("���ļ�[MHz]")), -1 ); 
			m_CListRawData.InsertColumn( j++, _T("��ȣ����[dBm]"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("��ȣ����[dBm]")), -1 ); 
			m_CListRawData.InsertColumn( j++, _T("�޽���[ns]"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("�޽���[ns]")), -1 ); 

			//m_CListPDW.SetGridLines(TRUE);
			//m_CListPDW.SetCheckboxeStyle(RC_CHKBOX_NORMAL); // Enable checkboxes
			//m_ColList.SetCheckboxes(TRUE);

			//m_CListPDW.SetItemCount( PDW_ITEMS );

		}
		else {
			int i;

			for( i=0 ; i < m_CListRawData.GetItemCount() ; ++i ) {
				//m_CListPDW.SetItemBkColor( i, -1, RGB(255, 255, 255) );
			}
		}
	}
	else if( m_pDoc->GetDataType() == en_IQ_DATA ) {
		if( bInit == true ) {
			m_CListRawData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | 0x00004000);
			//m_CListPDW.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

			m_CListRawData.InsertColumn( j++, _T("����"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("����  ")), -1 );
			m_CListRawData.InsertColumn( j++, _T("I ������"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("I ������")), -1 );
			m_CListRawData.InsertColumn( j++, _T("Q ������"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("Q ������")), -1 ); 
			m_CListRawData.InsertColumn( j++, _T("���� ����"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("���� ����")), -1 ); 
			m_CListRawData.InsertColumn( j++, _T("���� ������[��]"), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T("���� ������[��]")), -1 ); 
			m_CListRawData.InsertColumn( j++, _T("FFT"), LVCFMT_CENTER, TEXT_WIDTH*strlen(_T("FFT")), -1 ); 

			//m_CListPDW.SetGridLines(TRUE);
			//m_CListPDW.SetCheckboxeStyle(RC_CHKBOX_NORMAL); // Enable checkboxes
			//m_ColList.SetCheckboxes(TRUE);

			//m_CListPDW.SetItemCount( PDW_ITEMS );

		}
		else {
			int i;

			for( i=0 ; i < m_CListRawData.GetItemCount() ; ++i ) {
				//m_CListPDW.SetItemBkColor( i, -1, RGB(255, 255, 255) );
			}
		}
	}
}

/**
 * @brief     
 * @param     UINT nType
 * @param     int cx
 * @param     int cy
 * @return    void
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/10 10:04:38
 * @warning   
 */
 void CDeltaGraphView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
// 	if( m_hPE ) {
// 		::MoveWindow( m_hPE, 0, 0, cx, cy, FALSE);
// 	}

	UPDATE_EASYSIZE;
}

/**
 * @brief     
 * @param     ENUM_SUB_GRAPH enSubGraph
 * @return    void
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/10 9:39:40
 * @warning   
 */
 void CDeltaGraphView::ShowGraph( ENUM_SUB_GRAPH enSubGraph, int iFileIndex )
{
	ENUM_DataType enDataType;

	int i, j;
	UINT uiPDWDataItems;

	char *pcDV, *pcType;
	float *pfTOA, *pfDTOA;
	float *pfAOA, *pfFreq, *pfPA, *pfPW;
	float *pfPh1, *pfPh2, *pfPh3, *pfPh4;
	float *pfI, *pfQ, *pfIP, *pfFFT;
	_TOA *pllTOA;
	CString strVal;

	bool bPhaseData;

	void *pData;
	STR_PDW_DATA *pPDWData=NULL;
	STR_IQ_DATA *pIQData=NULL;

	uiPDWDataItems = m_pDoc->GetPDWDataItems();

	m_CListRawData.DeleteAllItems();

	if( uiPDWDataItems != 0 ) {
		bPhaseData = m_pDoc->IsPhaseData();
		enDataType = m_pDoc->GetDataType();
		pData = m_pDoc->GetData();

		Log( enNormal, _T("���â�� ������ ���� �����մϴ�.") );

		if (enDataType == en_PDW_DATA) {
			pPDWData = (STR_PDW_DATA *) pData;
			if( pPDWData != NULL ) {
				pfTOA = pPDWData->pfTOA;
				pfDTOA = pPDWData->pfDTOA;
				pfAOA = pPDWData->pfAOA;
				pfFreq = pPDWData->pfFreq;
				pfPA = pPDWData->pfPA;
				pfPW = pPDWData->pfPW;
				pcDV = pPDWData->pcDV;
				pllTOA = pPDWData->pullTOA;
				pcType = pPDWData->pcType;
				pfPh1 = pPDWData->pfPh1;
				pfPh2 = pPDWData->pfPh2;
				pfPh3 = pPDWData->pfPh3;
				pfPh4 = pPDWData->pfPh4;
				for( i=0 ; i < (int) uiPDWDataItems ; ++i ) {
					j = 1;

					strVal.Format( _T("%7d") , (m_pDoc->GetFileIndex()*PDW_ITEMS)+i+1 );
					//m_CListPDW.InsertItem( i, strVal );
					m_CListRawData.AddItem(strVal);

					strVal.Format( _T("%d") , *pcType );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					strVal.Format( _T("%12.3f/%llu") , *pfTOA*1., *pllTOA );
					//strVal.Format( _T("%12.3f") , *pfTOA*1. );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					strVal.Format( _T("%12.3f") , *pfDTOA*1. );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					if( *pcDV == _spOne ) {
						m_CListRawData.SetItemText( i, j++, _T("O") ); 
					}
					else {
						m_CListRawData.SetItemText( i, j++, _T("X") ); 
					}

					strVal.Format( _T("%4.1f") , *pfAOA );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					strVal.Format( _T("%8.3f") , *pfFreq );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					strVal.Format( _T("%5.2f") , *pfPA );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					strVal.Format( _T("%5.1f") , *pfPW );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					if( bPhaseData == true ) {
						//strVal.Format( _T("%7.2f/%7.2f/%7.2f/%7.2f") , *pfPh1, *pfPh2, *pfPh3, *pfPh4 );
						//m_pListCtrl->SetItemText( i, j++, strVal ); 
					}

					++ pfTOA;
					++ pfDTOA;
					++ pfAOA;
					++ pfFreq;
					++ pfPA;
					++ pfPW;

					++ pllTOA;

					++ pcDV;
					++ pcType;

					++ pfPh1;
					++ pfPh2;
					++ pfPh3;
					++ pfPh4;

				}
			}

			m_CListRawData.Complete();
			Log( enNormal, _T("���â�� ������ ���� �Ϸ� �մϴ�.") );
		}
		else {
			pIQData = (STR_IQ_DATA *) pData;
			if( pIQData != NULL ) {
				pfI = pIQData->pfI;
				pfQ = pIQData->pfQ;
				pfPA = pIQData->pfPA;
				pfIP = pIQData->pfIP;
				pfFFT = pIQData->pfFFT;
 
 				for( i=0 ; i < (int) uiPDWDataItems && i < 1000 /* MAX_LIST_IQ */ ; ++i ) {
					j = 1;

					strVal.Format( _T("%7d") , i+1 );
					m_CListRawData.AddItem( strVal );

					strVal.Format( _T("%8.0f") , *pfI );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					strVal.Format( _T("%8.0f") , *pfQ );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					strVal.Format( _T("%8.1f") , *pfPA );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					strVal.Format( _T("%8.1f") , *pfIP );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					strVal.Format( _T("%10.1f") , *pfFFT );
					m_CListRawData.SetItemText( i, j++, strVal ); 

					++ pfI;
					++ pfQ;
					++ pfPA;
					++ pfIP;
					++ pfFFT;

 				}
 			}
			m_CListRawData.Complete();
			Log( enNormal, _T("���â�� ������ ���� �Ϸ� �մϴ�.") );

		}
	}
}

// void CDeltaGraphView::OnSizing(UINT fwSide, LPRECT pRect)
// {
// 	__super::OnSizing(fwSide, pRect);
// 
// 	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
// 	EASYSIZE_MINSIZE(280,250,fwSide,pRect);
// }


/**
 * @brief     
 * @return    void
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/12 0:45:50
 * @warning   
 */
void CDeltaGraphView::OnBnClickedButtonPrevious()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iFileIndex=m_pDoc->GetFileIndex();

	m_pDoc->ReadDataFile( iFileIndex-1 );
	ShowGraph();

	GetDlgItem(IDC_BUTTON_PREVIOUS)->EnableWindow( m_pDoc->GetFileIndex() != 0 );
}


/**
 * @brief     
 * @return    void
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/12 0:45:48
 * @warning   
 */
void CDeltaGraphView::OnBnClickedButtonNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iFileIndex=m_pDoc->GetFileIndex();

	m_pDoc->ReadDataFile( iFileIndex+1 );
	ShowGraph();

	GetDlgItem(IDC_BUTTON_PREVIOUS)->EnableWindow( m_pDoc->GetFileIndex() != 0 );
}


void CDeltaGraphView::OnLvnGetdispinfoListPdw(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;

	if(pItem == NULL) return;


	int nRow = pItem->iItem;

	int nCol = pItem->iSubItem;



	if (nRow<0 || nRow >= PDW_ITEMS/*��ü ����Ʈ ����*/)

		return;





	//m_List.GetItemText(i, 1);   //<-�ڵ�� ������ ����Ŵ.



	if(pItem->pszText) //�̰��� �η� �� ���� �翬�� ����.

	{

		switch(nCol)

		{

		case 0:

			lstrcpy(pItem->pszText, _T("")/*nRow, 0�� ���� �� ���ڿ�*/);

			break;

		case 1:

			lstrcpy(pItem->pszText, _T("")/*nRow, 1�� ���� �� ���ڿ�*/);

			break;

			//... �� ��ȣ���� �ۼ�

		}

	}

	*pResult = 0;
}
