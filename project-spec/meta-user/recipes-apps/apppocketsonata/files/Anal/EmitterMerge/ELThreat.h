﻿/**
 * @file      ELThreat.h
 * @brief     모든 위협에 대한 인덱스를 트리 구조로 만들어 관리한다.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-05, 오후 4:17 
 * @warning   
 */

#pragma once

#include "Stack.h"

#define INVALID_INDEX			(0)

struct SELINDEX {
	UINT uiAET;
	UINT uiABT;
	UINT uiLOB;

    SELINDEX() : uiAET(INVALID_INDEX), uiABT(INVALID_INDEX), uiLOB(INVALID_INDEX)
	{

	}

};

typedef enum {
	ENUM_ROOT_TRAVERSE= 0, 
	ENUM_AET_TRAVERSE= 1, 
	ENUM_ABT_TRAVERSE, 
	ENUM_LOB_TRAVERSE

} ENUM_THREAT_TRAVERSE;

typedef enum {
	ENUM_UNK_THREAT = -1,

	ENUM_LOB_THREAT = 0,
	ENUM_ABT_THREAT,
	ENUM_AET_THREAT

} ENUM_THREAT_TYPE;


//////////////////////////////////////////////////////////////////////////
// 위협 관리 관련 정의문
#define TOTAL_ITEMS_OF_THREAT_NODE			(10000)						// 최대 위협 개수

/**
* [식별자 : CLS-GMU-EL-L-SAC]
*
* [추적성 : SRS-G-SAFR-005]
*
* @class	CELThreat
* @brief	위협 객체 클래스
*
* (1) 클래스 설명
* - 본 클래스는 위협 객체를 생성, 추가, 변경, 삭제 (관리)하기 위한 클래스이다.
*
* (2) 설계결정사항
* - 빔 병합, LOB 클러스터링을 처리한다.
*
* (3) 제한 및 예외처리
* - 해당사항 없음
*/
class CELThreat
{
private:
	static int m_CoInstance;										///< 객체 총 개수

	CELThreat *m_pLeftChild;										///< 트리 구조의 좌측 포인터
	CELThreat *m_pRightChild;										///< 트리 구조의 우측 포인터

	static Queue<int> m_QueIndex;								///< 위협의 큐 포인터

public:
	SELINDEX m_Idx;															///< 위협의 방사체/빔/LOB 번호

	int m_nIndex;																///< 위협 인덱스

public:
	CELThreat(void);
	~CELThreat(void);
	bool Remove( SELINDEX *pIndex );
	CELThreat *GetLastThreat( CELThreat *pThreat );

	CELThreat& operator= (const CELThreat& p);

	CELThreat( UINT nAET, UINT nABT, UINT nLOB )
	{
		m_pLeftChild = NULL;
		m_pRightChild = NULL;

		m_Idx.uiAET = nAET;
		m_Idx.uiABT = nABT;
		m_Idx.uiLOB = nLOB;

		if( false == m_QueIndex.Pop( & m_nIndex ) ) {
			m_nIndex = INVALID_INDEX;
		}
// 		else {
// 			//TRACE( "\n 생성 : I%d, A%d, B%d" , m_nIndex, m_Idx.nAET, m_Idx.nABT );
// 		}

		++ m_CoInstance;
	}

/*
	CELThreat( SELINDEX *pID )
	{
		m_pLeftChild = NULL;
		m_pRightChild = NULL;

		memcpy( & this->m_Idx, & m_Idx, sizeof(SELINDEX) );

		if( false == m_QueIndex.Pop( & m_nIndex ) ) {
			m_nIndex = INVALID_INDEX;
		}

		if( m_nIndex > TOTAL_ITEMS_OF_THREAT_NODE+10 ) {
			TRACE( "\n ############# Index[%d]" , m_nIndex );
		}

    }       */

		/**
		* @brief     트리의 모든 노드들을 삭제한다.
		* @param     void
		* @return    bool
		* @exception 
		* @author    조철희 (churlhee.jo@lignex1.com)
		* @version   0.0.1
		* @date      2016-03-21, 오후 10:25 
		* @warning   
	*/
	void RemoveAll();
	bool RemoveThreat( int nIndex, CELThreat *pPrevThreat );
	bool RemoveAET( int nAET, CELThreat *pPrevThreat );
	bool RemoveABT( int nAET, int nABT );
	void Link( CELThreat *pABTThreat, CELThreat *pAETThreat=NULL );
	void UnLink( CELThreat *pUnLinkABT );
	
	/**
		* @brief     Traverse
		* @param     int nDepth
		* @param     int nLimit
		* @return    void
		* @exception 
		* @author    조철희 (churlhee.jo@lignex1.com)
		* @version   0.0.1
		* @date      2017-03-23, 오후 1:46 
		* @warning   
	 */
	void Traverse( int nDepth, int nLimit )
	{

		if( nDepth <= nLimit ) {
			if( m_pLeftChild != NULL )
				m_pLeftChild->Traverse( nDepth+1, nLimit );
			if( m_pRightChild != NULL )
				m_pRightChild->Traverse( nDepth, nLimit );
		}
	}

	/**
		* @brief     AppendChildNode
		* @param     CELThreat * pChild 추가할 객체
		* @return    void
		* @exception 
		* @author    조철희 (churlhee.jo@lignex1.com)
		* @version   0.0.1
		* @date      2017-03-23, 오후 1:46 
		* @warning   
	 */
	void AppendChildNode( CELThreat *pChild ) {

		if( pChild != NULL ) {
			if( m_pLeftChild == NULL ) {
				m_pLeftChild = pChild;
			}
			else {
				CELThreat *pThreat = m_pLeftChild;
				while( pThreat->m_pRightChild != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
					pThreat = pThreat->m_pRightChild;
				}
				pThreat->m_pRightChild = pChild;
			}
		}

	}

	/**
		* @brief     IsCheckDepth
		* @param     ENUM_THREAT_TRAVERSE enTraverse
		* @param     CELThreat * pChild
		* @return    bool
		* @exception 
		* @author    조철희 (churlhee.jo@lignex1.com)
		* @version   0.0.1
		* @date      2017-03-23, 오후 1:45 
		* @warning   
	 */
	bool IsCheckDepth( ENUM_THREAT_TRAVERSE enTraverse, CELThreat *pChild ) {
		bool bRet = false;
		switch( enTraverse ) {
			case ENUM_AET_TRAVERSE :
				if( pChild->m_Idx.uiAET != 0 && pChild->m_Idx.uiABT == 0 && pChild->m_Idx.uiLOB == 0 )
					bRet = true;
				break;

			case ENUM_ABT_TRAVERSE :
				if( pChild->m_Idx.uiAET != 0 && pChild->m_Idx.uiABT != 0 && pChild->m_Idx.uiLOB == 0 )
					bRet = true;
				break;

			case ENUM_LOB_TRAVERSE :
				if( pChild->m_Idx.uiAET != 0 && pChild->m_Idx.uiABT != 0 && pChild->m_Idx.uiLOB != 0 )
					bRet = true;
				break;

			case ENUM_ROOT_TRAVERSE :
			default :
				{ //DTEC_Else

				}
				break;
				
		}
		return bRet;
	}


	/**
		* @brief     트리에서 AET 번호를 찾아서 해당 포인터를 리턴한다. 못 찾으면 NULL 로 리턴한다.
		* @param     int nAET
		* @return    CELThreat *
		* @exception 
		* @author    조철희 (churlhee.jo@lignex1.com)
		* @version   0.0.1
		* @date      2016-03-21, 오후 10:24 
		* @warning   
	*/
	CELThreat *Find( UINT nAET ) {
		CELThreat *pThreat=NULL;

		// 1. AET 찾기
		pThreat = m_pLeftChild;
		while( pThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
			if( pThreat->m_Idx.uiAET == nAET ) {
				break;
			}
			pThreat = pThreat->m_pRightChild;
		}
		return pThreat;

	}

	/**
		* @brief     트리에서 AET/ABT 번호를 찾아서 해당 포인터를 리턴한다. 못 찾으면 NULL 로 리턴한다.
		* @param     int nAET
		* @param     int nABT
		* @return    CELThreat *
		* @author    조철희 (churlhee.jo@lignex1.com)
		* @version   0.0.1
		* @date      2016-11-01, 오후 1:43 
		* @warning   
	 */
	CELThreat *Find( UINT nAET, UINT nABT ) {
		CELThreat *pTheAETThreat;
		CELThreat *pTheABTThreat=NULL;

		pTheAETThreat = Find( nAET );
		if( pTheAETThreat != NULL ) {
			pTheABTThreat = pTheAETThreat->m_pLeftChild;
			while( pTheABTThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
				if( pTheABTThreat->m_Idx.uiABT == nABT ) {
					break;
				}
				pTheABTThreat = pTheABTThreat->m_pRightChild;
			}

		}
		return pTheABTThreat;

	}

	CELThreat *Find( SELINDEX *pIndex )		
	{ //#FA_Q_4020_T1 (Multiple exit points found)
		UINT nIdx;

		CELThreat *pThreat=NULL;

		// 1. AET 찾기
		nIdx = pIndex->uiAET;
		pThreat = m_pLeftChild;
		while( pThreat != NULL ) {
			if( nIdx == pThreat->m_Idx.uiAET ) {
				// 중지 여부 결정		
				if( pIndex->uiABT == INVALID_INDEX ) {
					break;
					// return pThreat;
				}

				// 2. ABT 찾기
				//nIdx = pIndex->nABT;
				pThreat = pThreat->m_pLeftChild;
				while( pThreat != NULL ) {
					if( pIndex->uiABT == pThreat->m_Idx.uiABT ) {
						// 중지 여부 결정		
						if( pIndex->uiLOB == INVALID_INDEX ) {
							return pThreat;
						}
						
						// 3. LOB 찾기
						// nIdx = pIndex->nLOB;
						pThreat = pThreat->m_pLeftChild;
						while( pThreat != NULL ) {
							if( pIndex->uiLOB == pThreat->m_Idx.uiLOB ) {
								return pThreat;
							}
							pThreat = pThreat->m_pRightChild;
						}
						/* if( pThreat == NULL ) */
						return NULL;
					}
					pThreat = pThreat->m_pRightChild;
				}
				//if( pThreat == NULL )
				return NULL;
			}
	
			pThreat = pThreat->m_pRightChild;
		}
		
		return pThreat;
		//return NULL;
	}

	CELThreat *GetLeftChild() {
		return m_pLeftChild;
	}

	CELThreat *GetRightChild() {
		return m_pRightChild;
	}

	SELINDEX *GetID() {
		return & m_Idx;
	}

	bool IsRoot() {
		bool bRet = false;
		if( m_Idx.uiAET == INVALID_INDEX && m_Idx.uiABT == INVALID_INDEX ) {
			bRet = true; 
		}
		return bRet;
	}

	bool IsAET() {
		bool bRet = false;
		if( m_Idx.uiAET != INVALID_INDEX && m_Idx.uiABT == INVALID_INDEX ) {
			bRet = true; 
		}
		return bRet;
	}
	
	bool IsABT() {
		bool bRet = false;
		if( m_Idx.uiAET != INVALID_INDEX && m_Idx.uiABT != INVALID_INDEX ) {
			bRet = true; 
		}
		return bRet;		
	}
	
// 	bool IsLOB() { 
// 		bool bRet = false;
// 		if( m_Idx.uiAET != INVALID_INDEX && m_Idx.uiABT != INVALID_INDEX && m_Idx.uiLOB != INVALID_INDEX )
// 			bRet = true; 
// 		return bRet;		
// 	}


};

