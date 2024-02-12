
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

//#define IPACNV(A)    (unsigned int) ( ( A + ( float ) PDW_PA_RANGE ) / POCKETSONATA::_fPARes + A )
#define IPACNV(A)       CPOCKETSONATAPDW::EncodePA( A )

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

	//m_CSpinPage.SetDecimalPlaces(0);
	//m_CSpinPage.SetTrimTrailingZeros(FALSE);
	//m_CSpinPage.SetRangeAndDelta( 0, 10000, 10.0 );
	//m_CSpinPage.SetPos( (double) 0 );

}

#define TEXT_WIDTH			(10)
#define _COLUMNS_OF_LIST_   (20)
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

	if( m_pDoc->GetDataType() == en_PDW_DATA || m_pDoc->GetDataType() == en_PDW_DATA_CSV ) {
		if( bInit == true ) {
            int i;
            char szList[_COLUMNS_OF_LIST_][40] = { "����#", "Normal/CW", " PMOP", "FMOP/Dir/BW[MHz]", "      TOA[s]/TOA[s]", "    DTOA[us]", " DI", "����[��]  ", "���ļ�[MHz]    ", "��ȣ����[dBm]", "�޽���[ns]    ", "ä��#", "FalsePDW", "Edge    " };

            //CFont font;
            //font.CreatePointFont( 70, "D2Coding" );

			m_CListRawData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | 0x00004000);
            //m_CListRawData.SetFont( & font );

            m_CListRawData.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

            for( i = 0; i < _COLUMNS_OF_LIST_; ++i ) {
			    m_CListRawData.InsertColumn( j++, _T( szList[i] ), LVCFMT_RIGHT, TEXT_WIDTH*strlen(_T( szList[i])), -1 );
            }

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
	float *pfDTOA;
	float *pfAOA, *pfFreq, *pfPA, *pfPW;
	//float *pfPh1, *pfPh2, *pfPh3, *pfPh4;
	float *pfI, *pfQ, *pfIP, *pfFFT;

    unsigned int *puiIndex;

    double *pdTOA;

	_TOA *pllTOA;
	CString strVal;

	void *pRealData, *pData;
	STR_PDWREALDATA *pPDWRealData =NULL;

    STR_PDWDATA *pPDWData;
    _PDW *pPDW;

	STR_IQ_DATA *pIQData=NULL;

    char szFmopDir[4][10] = { "�ﰢ", "������", "�ٿ���", "��" };
    char szSignalType[20][20] = { "Normal", "CW", "CHIRP-TRI", "CHIRP-UP", "CHIRP-DN", "CHIRP-UK", "CW[CHIRP-TRI]", "CW[CHIRP-UP]", "CW[CHIRP-UK]", "PMOP", "CW[PMOP]" };

    char szOX[2][10] = { "O", "X" };
    char szInBand[2][10] = { "In-Band", "Out-Band" };

	uiPDWDataItems = m_pDoc->GetPDWDataItems();

	m_CListRawData.DeleteAllItems();

	if( uiPDWDataItems != 0 ) {
		//bPhaseData = m_pDoc->IsPhaseData();
		enDataType = m_pDoc->GetDataType();
        pData = m_pDoc->GetData();
		pRealData = m_pDoc->GetRealData();

		Log( enNormal, _T("���â�� ������ ���� �����մϴ�.") );

		if (enDataType == en_PDW_DATA || enDataType == en_PDW_DATA_CSV ) {
            pPDWData = ( STR_PDWDATA * ) pData;
            pPDW = pPDWData->pstPDW;
            pPDWRealData = (STR_PDWREALDATA *) pRealData;

			if( pPDWRealData != NULL ) {
				pdTOA = pPDWRealData->pdTOA;
				pfDTOA = pPDWRealData->pfDTOA;
				pfAOA = pPDWRealData->pfAOA;
				pfFreq = pPDWRealData->pfFreq;
				pfPA = pPDWRealData->pfPA;
				pfPW = pPDWRealData->pfPW;
				pcDV = pPDWRealData->pcDV;
				pllTOA = pPDWRealData->pullTOA;
				pcType = pPDWRealData->pcType;
                puiIndex = pPDWRealData->puiIndex;
// 				pfPh1 = pPDWData->pfPh1;
// 				pfPh2 = pPDWData->pfPh2;
// 				pfPh3 = pPDWData->pfPh3;
// 				pfPh4 = pPDWData->pfPh4;

				for( i=0 ; i < (int) uiPDWDataItems ; ++i, ++pPDW ) {
					j = 1;

					//strVal.Format( _T("%7d") , (m_pDoc->GetFileIndex()*PDW_ITEMS)+i );
                    strVal.Format( _T("%7u") , *puiIndex );
					//m_CListPDW.InsertItem( i, strVal );
					m_CListRawData.AddItem(strVal);

                    strVal.Format( _T( "%s" ), szSignalType[pPDW->GetCWPulse() & 1] );
					m_CListRawData.SetItemText( i, j++, strVal );

                    strVal.Format( _T( "%s" ), szOX[(int)(pPDW->GetPMOP()==0)] );
                    m_CListRawData.SetItemText( i, j++, strVal );

                    strVal.Format( _T( "%s/%s/%08.1f" ), szOX[( int ) ( pPDW->GetFMOP() == 0 )], szFmopDir[pPDW->GetFMOPDir() & 0x03 ], CPOCKETSONATAPDW::DecodeFMOPBW( pPDW->GetFMOPBW() ) );
                    m_CListRawData.SetItemText( i, j++, strVal );

					strVal.Format( _T("%12.6f/%llu") , *pdTOA*1., *pllTOA );
					m_CListRawData.SetItemText( i, j++, strVal );

					strVal.Format( _T("%12.3f") , FMUL( *pfDTOA, 1000000. ) );
					m_CListRawData.SetItemText( i, j++, strVal );

                    strVal.Format( _T( "%s" ), szOX[pPDW->GetDI() & 0x01] );
                    m_CListRawData.SetItemText( i, j++, strVal );

					strVal.Format( _T("%05.1f/0x%04X") , *pfAOA, pPDW->GetAOA() );
					m_CListRawData.SetItemText( i, j++, strVal );

					strVal.Format( _T("%8.3f/%8u") , *pfFreq/1000000., pPDW->GetFrequency() );
					m_CListRawData.SetItemText( i, j++, strVal );

					strVal.Format( _T("%5.2f/%5d") , *pfPA, pPDW->GetPulseamplitude() );
					m_CListRawData.SetItemText( i, j++, strVal );

					strVal.Format( _T("%5.1f/%5d") , *pfPW*1000000000., pPDW->GetPulsewidth() );
					m_CListRawData.SetItemText( i, j++, strVal );

                    strVal.Format( _T( "%d" ), pPDW->GetChannel() );
                    m_CListRawData.SetItemText( i, j++, strVal );

                    strVal.Format( _T( "%s" ), szOX[pPDW->GetFalsePDW() & 0x1 ] );
                    m_CListRawData.SetItemText( i, j++, strVal );

                    strVal.Format( _T( "%s" ), szInBand[pPDW->GetEdge() & 0x01 ] );
                    m_CListRawData.SetItemText( i, j++, strVal );

					++ pdTOA;
					++ pfDTOA;
					++ pfAOA;
					++ pfFreq;
					++ pfPA;
					++ pfPW;

					++ pllTOA;

					++ pcDV;
					++ pcType;

                    ++puiIndex;

// 					++ pfPh1;
// 					++ pfPh2;
// 					++ pfPh3;
// 					++ pfPh4;

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
