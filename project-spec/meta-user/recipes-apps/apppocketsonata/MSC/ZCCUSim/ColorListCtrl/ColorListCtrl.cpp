// ColorListCtrl.cpp : implementation file
//

#include "pch.h"
//#include "GenDlg.h"
#include "ColorListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl

IMPLEMENT_DYNCREATE(CColorListCtrl, CListCtrl)

CColorListCtrl::CColorListCtrl()
{
	GridMode = false;
	AltRowMode = false;
	MaskMode = false;

    m_bEndScroll = true;
}

CColorListCtrl::~CColorListCtrl()
{
}


BEGIN_MESSAGE_MAP(CColorListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CColorListCtrl)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	ON_NOTIFY_REFLECT(LVN_DELETEALLITEMS, OnDeleteallitems)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, CustDraw)
	ON_NOTIFY_REFLECT(LVN_INSERTITEM, OnInsertitem)
    ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//BEGIN_MESSAGE_MAP(CColorListCtrl, CListView)
//END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl drawing


/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl diagnostics

#ifdef _DEBUG
void CColorListCtrl::AssertValid() const
{
	CListCtrl::AssertValid();
}

void CColorListCtrl::Dump(CDumpContext& dc) const
{
	CListCtrl::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl message handlers
void CColorListCtrl::CustDraw(NMHDR *pNotifyStruct, LRESULT *result)
{
	LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW) pNotifyStruct; // cast our generic structure to bigger/specialized strc
	int i = 0;
	long iRow = 0;
	long iCol = 0;
	long iCIndex = 0;
	long iCelIndex = 0;
	long iRIndex = 0;
	switch(lplvcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*result  = CDRF_NOTIFYITEMDRAW|CDRF_NOTIFYSUBITEMDRAW;	// request notifications for individual items
		break;

	case CDDS_ITEMPREPAINT:
		*result = CDRF_NOTIFYSUBITEMDRAW;
		break;

	case CDDS_ITEMPREPAINT|CDDS_SUBITEM:	// drawing subitem
		iRow = lplvcd->nmcd.dwItemSpec;
		iCol = lplvcd->iSubItem;

		if(GridMode)		// grid mode
		{
			if( iRow %2 == 1){
				if( iCol %2 == 0)
					lplvcd->clrTextBk = Gx;
				else
					lplvcd->clrTextBk = Gy;
			}
			else{
				if( iCol %2 == 0)
					lplvcd->clrTextBk = Gy;
				else
					lplvcd->clrTextBk = Gx;
			}
		}

		if(AltRowMode)	//alternate row mode
		{
			if( iRow %2 == 1)
				lplvcd->clrTextBk = Rx;
			else
				lplvcd->clrTextBk = Ry;
		}

		iRIndex = findDetails(iRow,ROW);	// individual cell,coloumn,row color setting
		iCIndex = findDetails(iCol,COL);
		iCelIndex = findDetails(iRow,CELL,iCol);

		if(iRIndex == -1 && iCIndex == -1 && iCelIndex == -1 ){
			if(!GridMode && !AltRowMode)
				lplvcd->clrTextBk = GetBkColor();
		}
		else{
			if( iCelIndex != -1)
				lplvcd->clrTextBk = CellColors[iCelIndex].cf;
			else{
				if(iRIndex != -1)
					lplvcd->clrTextBk = RowColors[iRIndex].cf;
				else
					lplvcd->clrTextBk = ColColors[iCIndex].cf;
			}

		}

		if(MaskMode)		// text mask mode
			lplvcd->clrText = InvertColor(lplvcd->clrTextBk);
		*result = CDRF_NEWFONT;

		break;
	default:
		*result = CDRF_DODEFAULT;
	}

}

void CColorListCtrl::SetRowColor(COLORREF cf,long row)
{
	ColorStruct cs;
	cs.cf = cf;
	cs.id = row;
	RowColors.push_back(cs);
	RedrawWindow(NULL,NULL,RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

void CColorListCtrl::SetColColor(COLORREF cf,long col)
{
	ColorStruct cs;
	cs.cf = cf;
	cs.id = col;
	ColColors.push_back(cs);
	RedrawWindow(NULL,NULL,RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

void CColorListCtrl::SetCellColor(COLORREF cf,long row,long col)
{
	ColorStruct cs;
	cs.cf = cf;
	cs.id = row;
	cs.subId = col;
	CellColors.push_back(cs);
	RedrawWindow(NULL,NULL,RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

long CColorListCtrl::findDetails(long id,RecType rt,long subId)
{
	if( rt == ROW)
	{
		for(int i=0;i< RowColors.size(); i++)
		{
			if(RowColors[i].id == id)
				return i;
		}
	}

	if( rt == COL)
	{
		for(int i=0;i< ColColors.size(); i++)
		{
			if(ColColors[i].id == id)
				return i;
		}
	}

	if( rt == CELL)
	{
		for(int i=0;i< CellColors.size(); i++)
		{
			if( subId >=0){
				if(CellColors[i].id == id && CellColors[i].subId == subId)
					return i;
			}
		}
	}
	return -1;
}

void CColorListCtrl::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult)
{
    int i;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	// TODO: Add your control notification handler code here
	long row  = pNMListView->iItem;
	long index = findDetails(row);

	for( i=0;i< RowColors.size();i++)
	{
		if(RowColors[i].id == row){
			RowColors.erase(RowColors.begin()+i);
			i--;
			continue;
		}
		if(RowColors[i].id > row){
			RowColors[i].id--;
		}
	}
	for(i=0;i< CellColors.size();i++)
	{
		if(CellColors[i].id == row){
			CellColors.erase(CellColors.begin()+i);
			i--;
			continue;
		}
		if(CellColors[i].id > row){
			CellColors[i].id--;
		}
	}
	*pResult = 0;
}

void CColorListCtrl::OnDeleteallitems(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	RowColors.clear();
	ColColors.clear();
	CellColors.clear();
	*pResult = 0;
}

void CColorListCtrl::OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult)
{
    int i;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	long row  = pNMListView->iItem;
	long col  = pNMListView->iSubItem;

	for(i=0;i< RowColors.size();i++)
	{
		if(RowColors[i].id > row){
			RowColors[i].id++;
		}
	}

	for(i=0;i< CellColors.size();i++)
	{
	if(CellColors[i].id > row){
			CellColors[i].id++;
		}
	}

	*pResult = 0;
}

void CColorListCtrl::SetGridMode(bool TurnOn,COLORREF x,COLORREF y)
{
	Gx = y;
	Gy = x;
	GridMode = TurnOn;
	RedrawWindow(NULL,NULL,RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

void CColorListCtrl::SetAltRowColors(bool TurnOn,COLORREF x,COLORREF y)
{
	Rx = x;
	Ry = y;
	AltRowMode = TurnOn;
	RedrawWindow(NULL,NULL,RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

void CColorListCtrl::SetTextMask(bool TurnOn)
{
	MaskMode = TurnOn;
	RedrawWindow(NULL,NULL,RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

void CColorListCtrl::ClrRowColor(long row)
{
	long index = findDetails(row);
	if(index != -1)
		RowColors.erase(RowColors.begin()+index);
	RedrawWindow(NULL,NULL,RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

void CColorListCtrl::ClrColColor(long col)
{
	long index = findDetails(col,COL);
	if(index != -1)
		ColColors.erase(ColColors.begin()+index);
	RedrawWindow(NULL,NULL,RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

void CColorListCtrl::ClrCellColor(long row,long col)
{
	long index = findDetails(row,CELL,col);
	if(index != -1)
		CellColors.erase(CellColors.begin()+index);
	RedrawWindow(NULL,NULL,RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

COLORREF CColorListCtrl::InvertColor(COLORREF cf)
{
	return RGB(abs(220-GetRValue(cf)),abs(220-GetGValue(cf)),abs(220-GetBValue(cf)));
}

void CColorListCtrl::ResetColors(void)
{
	RowColors.clear();
	ColColors.clear();
	CellColors.clear();
	GridMode = false;
	AltRowMode = false;
	MaskMode = false;
	RedrawWindow(NULL,NULL,RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

/**
 * @brief     OnVScroll
 * @param     UINT nSBCode
 * @param     UINT nPos
 * @param     CScrollBar * pScrollBar
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-20 09:36:34
 * @warning
 */
void CColorListCtrl::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar )
{
    //do some stuff here

    ScrollControl( nSBCode, nPos, *pScrollBar );//스크롤 메세지 처리

    CListCtrl::OnVScroll( nSBCode, nPos, pScrollBar );


}

/**
 * @brief     ScrollControl
 * @param     UINT nSBCode
 * @param     UINT nPos
 * @param     CScrollBar & pScrollBar
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-20 09:37:08
 * @warning
 */
void CColorListCtrl::ScrollControl( UINT nSBCode, UINT nPos, CScrollBar &pScrollBar )
{

    switch( nSBCode ) {
        case SB_LINEUP: //scrolls one line up (한 줄 위로 스크롤)
            //pScrollBar.SetScrollPos( pScrollBar.GetScrollPos() - 1 );
            TRACE( "\n SB_LINEUP" );
            break;

        case SB_LINEDOWN: //scrolls one line down( 한 줄 아래로 스크롤)
            //pScrollBar.SetScrollPos( pScrollBar.GetScrollPos() + 1 );
            TRACE( "\n SB_LINEDOWN" );
            break;

        case SB_PAGEUP://scrolls one page up( 유저가 스크롤 바의 바 위쪽을 누름)
            //pScrollBar.SetScrollPos( pScrollBar.GetScrollPos() - 2 );
            TRACE( "\n SB_PAGEUP" );
            break;

        case SB_PAGEDOWN://scrolls one page down(유저가 스크롤 바의 바 아래쪽을 누름)
            //pScrollBar.SetScrollPos( pScrollBar.GetScrollPos() + 2 );
            TRACE( "\n SB_PAGEDOWN" );
            break;

        case SB_TOP://scrolls to the upper left(제일 위쪽에 스크롤된다)
            //pScrollBar.SetScrollPos( 0 );
            TRACE( "\n SB_TOP" );
            break;

        case SB_BOTTOM: //scrolls to the lower right.(제일 아래쪽에 스크롤된다)
            //pScrollBar.SetScrollPos( pScrollBar.GetScrollLimit() );
            TRACE( "\n SB_BOTTOM" );
            break;

        case SB_THUMBTRACK: //The user is dragging the scroll box.( 유저가 스크롤을 드래그 한다.)
            //pScrollBar.SetScrollPos( nPos );
            TRACE( "\n SB_THUMBTRACK" );
            break;

        case SB_ENDSCROLL:
            TRACE( "\n SB_ENDSCROLL" );
            SendMessage( WM_VSCROLL, SB_BOTTOM );
            break;

        default:
            TRACE( "\n nSBCode[%0X]" , nSBCode );
            break;
    }
}
