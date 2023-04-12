// KDefine.h: interface for the 추적분석판 소프트웨어의 정의
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KDEFINE_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_KDEFINE_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 추적에서 새로운 에미터 총 개수
#define		CO_MAX_KSP_NEW_AET			(4)


#define DEFINE_ANAL_VAR_    \
    _TOA TOA[MAX_PDW];			/* PDW TOA 파라메터     */  \
    UINT AOA[MAX_PDW];			/* PDW AOA 파라메터     */  \
    UINT FREQ[MAX_PDW];		/* PDW FREQUENCY 파라메터   */ \
    UINT PW[MAX_PDW];			/* PDW PULSE WIDTH 파라메터 */  \
    int PA[MAX_PDW];			/* PDW PULSE AMPLITUDE 파라메터 */  \
    UCHAR PMOP[MAX_PDW];		/* PDW PMOP 파라메터        */      \
    UCHAR FMOP[MAX_PDW];		/* PDW FMOP 파라메터        */      \
    USHORT MARK[MAX_PDW];	/* PDW MARK ; selected pdw      */      \
    UCHAR BAND[MAX_PDW];		/* 주파수 밴드       */      \
    UCHAR STAT[MAX_PDW];		/* 주파수 밴드       */      \
    USHORT BKMK[MAX_PDW];		/* Mark 펄스열의 백업용    */  \
    USHORT RSMK[MAX_PDW];	/* MARK 백업용, 스태거 분석시에 사용함.  */  \
    UCHAR MAXCHANNEL[MAX_PDW];	/* PDW의 MaxChannel      */

#define DEFINE_ANAL_PVAR_    \
    _TOA *m_pTOA;                   \
    unsigned int *m_pAOA;			/* PDW AOA 파라메터  */ \
    unsigned int *m_pFREQ;          /* PDW FREQUENCY 파라메터   */ \
    unsigned int *m_pPW;			/* PDW PULSE WIDTH 파라메터 */ \
    int *m_pPA;                     /* PDW PULSE AMPLITUDE 파라메터 */ \
    unsigned char *m_pPMOP;         /* PDW PMOP 파라메터    */ \
    unsigned char *m_pFMOP;         /* PDW FMOP 파라메터    */ \
    unsigned short *m_pMARK;        /* PDW MARK ; selected pdw  */ \
    UCHAR *m_pBAND;         /* 주파수 밴드                  */ \
    UCHAR *m_pSTAT;         /* 펄스 상태          */          \
    unsigned short *m_pBKMK;		/* Mark 펄스열의 백업용    */          \
    unsigned short *m_pRSMK;        /* MARK 백업용, 스태거 분석시에 사용함.  */  \
    UCHAR *m_pMAXCHANNEL;	/* PDW의 MaxChannel      */

#define INIT_ANAL_VAR_(A)    \
    m_pTOA = & A->TOA[0];           \
    m_pAOA = & A->AOA[0];			/* PDW AOA 파라메터 */          \
    m_pFREQ = & A->FREQ[0];         /* PDW FREQUENCY 파라메터   */  \
    m_pPW = & A->PW[0];             /* PDW PULSE WIDTH 파라메터 */  \
    m_pPA = & A->PA[0];             /* PDW PULSE AMPLITUDE 파라메터 */  \
    m_pPMOP = & A->PMOP[0];         /* PDW PMOP 파라메터    */          \
    m_pFMOP = & A->FMOP[0];         /* PDW FMOP 파라메터    */          \
    m_pMARK = & A->MARK[0];         /* PDW MARK ; selected pdw  */         \
    m_pBAND = & A->BAND[0];         /* 주파수 밴드       */                  \
    m_pSTAT = & A->STAT[0];         /* 주파수 밴드       */      \
    m_pBKMK = & A->BKMK[0];         /* Mark 펄스열의 백업용        */      \
    m_pRSMK = & A->RSMK[0];         /* MARK 백업용, 스태거 분석시에 사용함.  */ \
    m_pMAXCHANNEL = & A->MAXCHANNEL[0];	// PDW의 MaxChannel

#define INIT_ANAL_VAR2_(A,B)    \
    A::m_pTOA = & B->TOA[0];           \
    A::m_pAOA = & B->AOA[0];			/* PDW AOA 파라메터 */          \
    A::m_pFREQ = & B->FREQ[0];         /* PDW FREQUENCY 파라메터   */  \
    A::m_pPW = & B->PW[0];             /* PDW PULSE WIDTH 파라메터 */  \
    A::m_pPA = & B->PA[0];             /* PDW PULSE AMPLITUDE 파라메터 */  \
    A::m_pPMOP = & B->PMOP[0];         /* PDW PMOP 파라메터    */          \
    A::m_pFMOP = & B->FMOP[0];         /* PDW FMOP 파라메터    */          \
    A::m_pMARK = & B->MARK[0];         /* PDW MARK ; selected pdw  */         \
    A::m_pBAND = & B->BAND[0];         /* 주파수 밴드       */                  \
    A::m_pSTAT = & B->STAT[0];         /* 주파수 밴드       */      \
    A::m_pBKMK = & B->BKMK[0];         /* Mark 펄스열의 백업용        */      \
    A::m_pRSMK = & B->RSMK[0];         /* MARK 백업용, 스태거 분석시에 사용함.  */ \
    A::m_pMAXCHANNEL = & B->MAXCHANNEL[0];	// PDW의 MaxChannel

#endif // !defined(AFX_KDEFINE_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
