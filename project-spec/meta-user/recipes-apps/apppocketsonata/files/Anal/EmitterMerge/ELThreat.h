/**
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
	UINT uiAETID;
	UINT uiABTID;
	UINT uiLOBID;

};




//////////////////////////////////////////////////////////////////////////
// 위협 관리 관련 정의문
#ifdef _POCKETSONATA_
#define TOTAL_ITEMS_OF_THREAT			    (300)						    // 최대 위협 개수
#define TOTAL_ITEMS_OF_THREAT_NODE			(2*TOTAL_ITEMS_OF_THREAT)	    // 방사체/빔 개수

#define AETID_OFFSET                        (1000)
#define MAX_ABTID                           (9999)

#elif _712_
#define TOTAL_ITEMS_OF_THREAT			    (1000)						    // 최대 위협 개수
#define TOTAL_ITEMS_OF_THREAT_NODE			(2*TOTAL_ITEMS_OF_THREAT)	    // 방사체/빔 개수
#define AETID_OFFSET                        (0)
#define MAX_ABTID                           (9999)

#else
#define TOTAL_ITEMS_OF_THREAT			    (500)							    // 최대 위협 개수
#define TOTAL_ITEMS_OF_THREAT_NODE			(2*TOTAL_ITEMS_OF_THREAT)	    // 방사체/빔 개수

#define AETID_OFFSET                        (1000)
#define MAX_ABTID                           (9999)

#endif

#if AETID_OFFSET != 0 && AETID_OFFSET <= TOTAL_ITEMS_OF_THREAT
#error  "프로세서판 별로 위협 OFFSET 값이 위협 개수보다 크게 설정해야 합니다."
#endif

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
	static int m_CoInstance;                                                    //< 객체 총 개수

    static unsigned int m_uiBoardID;                                            //< 보드 ID

	static Queue<unsigned int> m_QueIndex;                                      //< 위협의 큐 포인터
    static Queue<unsigned int> m_QueAETID;                                      //< 방사체 번호의 큐 포인터
    static Queue<unsigned int> m_QueABTID;                                      //< 방사체 번호의 큐 포인터

    //static int m_iTotalOfABT;                                                   //< 위협의 큐 포인터
    //static int m_iTotalOfAET;                                                   //< 위협의 큐 포인터

    static CELThreat *m_pRootThreat;                                            //< 트리 구조의 좌측 포인터

	CELThreat *m_pLeftChild;                                                    //< 트리 구조의 좌측 포인터
	CELThreat *m_pRightChild;                                                   //< 트리 구조의 우측 포인터


public:
	SELINDEX m_Idx;                                                             //< 위협의 방사체/빔/LOB 번호

	unsigned int m_uiIndex;                                                     //< 위협 인덱스

public:
	CELThreat(unsigned int iBoardID );
    CELThreat &operator= ( const CELThreat &p );

    CELThreat( UINT uiAET, UINT uiABT, UINT uiLOB );
    CELThreat( unsigned int *puiAET );
    CELThreat( unsigned int uiAET, unsigned int *puiABT );
	~CELThreat(void);

	bool Remove( SELINDEX *pIndex );
	CELThreat *GetLastThreat( CELThreat *pThreat );

	void RemoveAll();
	bool RemoveThreat( int nIndex, CELThreat *pPrevThreat );
	bool RemoveAET( unsigned int uiAETID, CELThreat *pPrevThreat );
	bool RemoveABT( unsigned int uiAETID, unsigned int uiABTID );

    static void Move( CELThreat *pMovingThreatAET, CELThreat *pMovingThreatABT, CELThreat *pMergedThreatAET );

    void Link( CELThreat *pAddeThreatABT );
	//void Link( CELThreat *pABTThreat, CELThreat *pAETThreat=NULL );
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
			if( m_pLeftChild != NULL ) {
                if( m_Idx.uiAETID != 0 ) {
                    TRACE( "---- 방사체 AET[%d]\n", m_Idx.uiAETID );
                }
				m_pLeftChild->Traverse( nDepth+1, nLimit );
			}
            else {
                if( m_Idx.uiAETID != 0 ) {
                    TRACE( "AET[%04d], ABT[%04d]\n", m_Idx.uiAETID, m_Idx.uiABTID );
                }
                else {
                    TRACE( "위협 노드가 없습니다 !\n" );
                }
            }

			if( m_pRightChild != NULL ) {
				m_pRightChild->Traverse( nDepth, nLimit );
			}
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
				while( pThreat->m_pRightChild != NULL ) {
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
// 	bool IsCheckDepth( ENUM_THREAT_TRAVERSE enTraverse, CELThreat *pChild ) {
// 		bool bRet = false;
// 		switch( enTraverse ) {
// 			case ENUM_AET_TRAVERSE :
// 				if( pChild->m_Idx.uiAET != 0 && pChild->m_Idx.uiABT == 0 && pChild->m_Idx.uiLOB == 0 )
// 					bRet = true;
// 				break;
//
// 			case ENUM_ABT_TRAVERSE :
// 				if( pChild->m_Idx.uiAET != 0 && pChild->m_Idx.uiABT != 0 && pChild->m_Idx.uiLOB == 0 )
// 					bRet = true;
// 				break;
//
// 			case ENUM_LOB_TRAVERSE :
// 				if( pChild->m_Idx.uiAET != 0 && pChild->m_Idx.uiABT != 0 && pChild->m_Idx.uiLOB != 0 )
// 					bRet = true;
// 				break;
//
// 			case ENUM_ROOT_TRAVERSE :
// 			default :
// 				{ //DTEC_Else
//
// 				}
// 				break;
//
// 		}
// 		return bRet;
// 	}


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
		while( pThreat != NULL ) {
			if( pThreat->m_Idx.uiAETID == nAET ) {
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
			while( pTheABTThreat != NULL ) {
				if( pTheABTThreat->m_Idx.uiABTID == nABT ) {
					break;
				}
				pTheABTThreat = pTheABTThreat->m_pRightChild;
			}

		}
		return pTheABTThreat;

	}

// 	CELThreat *Find( SELINDEX *pIndex )
// 	{
// 		UINT nIdx;
//
// 		CELThreat *pThreat=NULL;
//
// 		// 1. AET 찾기
// 		nIdx = pIndex->uiAET;
// 		pThreat = m_pLeftChild;
// 		while( pThreat != NULL ) {
// 			if( nIdx == pThreat->m_Idx.uiAET ) {
// 				// 중지 여부 결정
// 				if( pIndex->uiABT == INVALID_INDEX ) {
//                     pThreat = NULL;
// 					break;
// 				}
//
// 				// 2. ABT 찾기
// 				//nIdx = pIndex->nABT;
// 				pThreat = pThreat->m_pLeftChild;
// 				while( pThreat != NULL ) {
// 					if( pIndex->uiABT == pThreat->m_Idx.uiABT ) {
// 						// 중지 여부 결정
// 						if( pIndex->uiLOB == INVALID_INDEX ) {
// 							return pThreat;
// 						}
//
// 						// 3. LOB 찾기
// 						// nIdx = pIndex->nLOB;
// 						pThreat = pThreat->m_pLeftChild;
// 						while( pThreat != NULL ) {
// 							if( pIndex->uiLOB == pThreat->m_Idx.uiLOB ) {
// 								return pThreat;
// 							}
// 							pThreat = pThreat->m_pRightChild;
// 						}
// 						/* if( pThreat == NULL ) */
// 						return NULL;
// 					}
// 					pThreat = pThreat->m_pRightChild;
// 				}
//                 pThreat = NULL;
//                 break;
// 			}
//
// 			pThreat = pThreat->m_pRightChild;
// 		}
//
// 		return pThreat;
// 	}

	/**
	 * @brief     노드의 좌측 포인터를 리턴한다.
	 * @return    CELThreat *
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-06-05, 13:41
	 * @warning
	 */
	CELThreat *GetLeftChild() {
		return m_pLeftChild;
	}

	/**
	 * @brief     노드의 우측 포인터를 리턴한다.
	 * @return    CELThreat *
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-06-05, 13:41
	 * @warning
	 */
	CELThreat *GetRightChild() {
		return m_pRightChild;
	}

	/**
	 * @brief     노드의 ID 정보를 리턴한다.
	 * @return    SELINDEX *
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-06-05, 13:41
	 * @warning
	 */
	SELINDEX *GetID() {
		return & m_Idx;
	}

	/**
	 * @brief     루트 노드 여부를 확인한다.
	 * @return    bool
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-06-05, 13:42
	 * @warning
	 */
	bool IsRoot() {
		bool bRet = false;
		if( m_Idx.uiAETID == INVALID_INDEX && m_Idx.uiABTID == INVALID_INDEX ) {
			bRet = true;
		}
		return bRet;
	}

	/**
	 * @brief     에미터 노드 여부를 확인한다.
	 * @return    bool
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-06-05, 13:42
	 * @warning
	 */
	bool IsAET() {
		bool bRet = false;
		if( m_Idx.uiAETID != INVALID_INDEX && m_Idx.uiABTID == INVALID_INDEX ) {
			bRet = true;
		}
		return bRet;
	}

	/**
	 * @brief     빔 노드 여부를 확인한다.
	 * @return    bool
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-06-05, 13:42
	 * @warning
	 */
	bool IsABT() {
		bool bRet = false;
		if( m_Idx.uiAETID != INVALID_INDEX && m_Idx.uiABTID != INVALID_INDEX ) {
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

    /**
     * @brief     GetRootThreat
     * @return    CELThreat *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2024-02-01 17:55:58
     * @warning
     */
    static CELThreat *GetRootThreat()
    {
        return m_pRootThreat;
    }

    /**
     * @brief     Traverse
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2024-02-01 17:55:52
     * @warning
     */
    static void PrintAllThreat()
    {
        TRACE( "===== 총 위협 개수[%d/%d] 정보 전시 ===\n" , m_QueAETID.RCount(), m_QueABTID.RCount() );
        m_pRootThreat->Traverse( 0, 0xffffff );
        TRACE( "==========================================\n" );

    }

    /**
     * @brief     NextAETID
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-05 15:20:17
     * @warning
     */
    static unsigned int NextAETID()
    {
        unsigned int uiAETID=(unsigned int) INVALID_INDEX;

        if( m_QueAETID.Pop( & uiAETID ) == false ) {
            uiAETID = (unsigned int) INVALID_INDEX;
        }
        else {
            //++ m_iTotalOfAET;
            //m_QueAETID.Print();
        }

        return uiAETID;

    }

    /**
     * @brief     NextABTID
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2024-02-01 14:57:04
     * @warning
     */
    static unsigned int NextABTID()
    {
        unsigned int uiABTID = ( unsigned int ) INVALID_INDEX;

        if( m_QueABTID.Pop( & uiABTID ) == false ) {
            uiABTID = ( unsigned int ) INVALID_INDEX;
        }
        else {
            //++ m_iTotalOfAET;
            //m_QueAETID.Print();
        }

        return uiABTID;

    }

    /**
     * @brief     PushAETID
     * @param     unsigned int uiAETID
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-06 15:35:18
     * @warning
     */
    static bool PushAETID( unsigned int uiAETID )
    {
        bool bRet = m_QueAETID.Push( uiAETID );
        //m_QueAETID.Print();
        return bRet;

    }

    /**
     * @brief     PushABTID
     * @param     unsigned int uiABTID
     * @return    bool
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2024-02-01 13:32:01
     * @warning
     */
    static bool PushABTID( unsigned int uiABTID )
    {
        bool bRet = m_QueABTID.Push( uiABTID );
        //m_QueABTID.Print();
        return bRet;

    }

    /**
     * @brief     ClearAETID
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-05 15:20:16
     * @warning
     */
    static void ClearAETID()
    {
        unsigned int ui;

        m_QueAETID.Reset();

        if( m_uiBoardID <= 1 ) {
            for( ui = 1; ui < AETID_OFFSET ; ++ui ) {
                m_QueAETID.Push( ui );
            }
        }
        else {
            for( ui = ( AETID_OFFSET * ( m_uiBoardID - 1 ) ) ; ui < (unsigned int) ( AETID_OFFSET * m_uiBoardID ); ++ui ) {
                m_QueAETID.Push( ui );
            }

        }

        //m_QueAETID.Print();

        return;

    }

    /**
     * @brief     ClearABTID
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2024-02-01 11:51:29
     * @warning
     */
    static void ClearABTID()
    {
        unsigned int ui;

        m_QueABTID.Reset();

        for( ui = 1; ui <= MAX_ABTID ; ++ui ) {
            m_QueABTID.Push( ui );

        }

        // m_QueABTID.Print();

        return;

    }

    /**
     * @brief     PrintAETID
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2024-01-24 10:07:53
     * @warning
     */
    static void PrintAETID()
    {

        m_QueAETID.Print();

    }

    /**
     * @brief     PrintABTID
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2024-02-01 13:16:43
     * @warning
     */
    static void PrintABTID()
    {

        m_QueABTID.Print();

    }

    /**
     * @brief     SizeOfAETID
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2024-01-24 10:46:53
     * @warning
     */
    static int SizeOfAETID()
    {
        return m_QueAETID.Count();

    }

    /**
     * @brief     SizeOfABTID
     * @return    int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2024-02-01 13:17:14
     * @warning
     */
    static int SizeOfABTID()
    {
        return m_QueABTID.Count();

    }


    /**
     * @brief     모든 노드 총 개수를 리턴한다.
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-06-05, 13:44
     * @warning
     */
    inline int GetAllNode() {
        return m_CoInstance;
    }

    /**
     * @brief     총 에미터 개수를 리턴한다.
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-06-05, 14:40
     * @warning
     */
    inline int GetTotalOfAET() {
        return m_QueAETID.RCount(); /* m_iTotalOfAET;*/
    }

    /**
     * @brief     총 빔 개수를 리턴한다.
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-06-05, 14:41
     * @warning
     */
    inline int GetTotalOfABT() {
        return m_QueABTID.RCount(); /* m_iTotalOfABT;*/
    }

	inline unsigned int GetAETID() { return m_Idx.uiAETID; }
	inline unsigned int GetABTID() { return m_Idx.uiABTID; }
	inline unsigned int GetLOBID() { return m_Idx.uiLOBID; }

    inline bool RemoveThreat( unsigned int uiAETID ) { return m_pRootThreat->RemoveAET( uiAETID, m_pRootThreat ); }
    inline bool RemoveThreat( unsigned int uiAETID, unsigned int uiABTID ) { return m_pRootThreat->RemoveABT( uiAETID, uiABTID ); }

};

