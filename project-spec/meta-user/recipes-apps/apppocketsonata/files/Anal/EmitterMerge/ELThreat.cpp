/**
 * @file      ELThreat.cpp
 * @brief
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-20, 오후 8:17
 * @warning
 */

#include "stdafx.h"

#include "../../BootShell/Macros.h"

#include "ELThreat.h"

Queue<unsigned int> CELThreat::m_QueIndex;
Queue<unsigned int> CELThreat::m_QueAETID;
Queue<unsigned int> CELThreat::m_QueABTID;

//CELThreat *m_pTheThreatRoot;							///< 위협 노드 중에서 ROOT 노드

int CELThreat::m_CoInstance=0;
//int CELThreat::m_iTotalOfABT = 0;
//int CELThreat::m_iTotalOfAET = 0;

unsigned int CELThreat::m_uiBoardID = 0;

CELThreat *CELThreat::m_pRootThreat = NULL;


/**
 * @brief     생성자에 AET, ABT 저장소 인덱스를 얻고 초기 생성자에 인덱스를 초기화 한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-07, 오후 12:10
 * @warning
 */
CELThreat::CELThreat( unsigned int uiBoardID )
{
    unsigned int ui; // , ui;

    m_uiBoardID = uiBoardID;

	m_pLeftChild = NULL;
	m_pRightChild = NULL;

    m_Idx.uiAETID = 0;
    m_Idx.uiABTID = 0;
    m_Idx.uiLOBID = 0;

	if( m_CoInstance == 0 ) {
        m_pRootThreat = this;

		m_QueIndex.Init( TOTAL_ITEMS_OF_THREAT_NODE );
		for( ui=0 ; ui < TOTAL_ITEMS_OF_THREAT_NODE ; ++ui ) {

            //ui = (unsigned int) ( g_enBoardId << 28 ) | i;
			m_QueIndex.Push( ui );
		}
        // /m_QueIndex.Print();

        if( uiBoardID <= (unsigned int) 1 ) {
            m_QueAETID.Init( AETID_OFFSET - 1 );
        }
        else {
            m_QueAETID.Init( AETID_OFFSET );
        }

        m_QueABTID.Init( MAX_ABTID );

        ClearAETID();
        ClearABTID();

	}

	if( false == m_QueIndex.Pop( & m_uiIndex ) ) {
		m_uiIndex = INVALID_INDEX;

        //m_QueIndex.Print();
	}
    else {
        //TRACE( "\n m_QueIndex.Pop[%d]", m_uiIndex );

        //m_QueIndex.Print();
    }

	++ m_CoInstance;

}

/**
 * @brief     CELThreat
 * @param     UINT nAET
 * @param     UINT nABT
 * @param     UINT nLOB
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-06 19:20:16
 * @warning
 */
CELThreat::CELThreat( UINT nAET, UINT nABT, UINT nLOB )
{
    m_pLeftChild = NULL;
    m_pRightChild = NULL;

    m_Idx.uiAETID = nAET;
    m_Idx.uiABTID = nABT;
    m_Idx.uiLOBID = nLOB;

    m_uiIndex = 0;

    if( false == m_QueIndex.Pop( & m_uiIndex ) ) {
        m_uiIndex = INVALID_INDEX;
    }
    else {
        //TRACE( "\n 생성 : I%d, A%d, B%d" , m_nIndex, m_Idx.nAET, m_Idx.nABT );
        //TRACE( "\nm_QueIndex.Pop[%d]", m_uiIndex );
        //m_QueIndex.Print();
    }

    if( m_uiIndex != INVALID_INDEX ) {
        if( m_Idx.uiABTID == INVALID_INDEX ) {
            //++m_iTotalOfAET;
        }
        else {
            //++m_iTotalOfABT;
            //TRACE( "\n m_iTotalOfABT[%d", m_iTotalOfABT );
        }
    }

    ++ m_CoInstance;
}

/**
 * @brief     CELThreat
 * @param     UINT & puiAET
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-02-01 11:26:08
 * @warning
 */
CELThreat::CELThreat( unsigned int *puiAET )
{
    m_pLeftChild = NULL;
    m_pRightChild = NULL;

    m_Idx.uiAETID = INVALID_INDEX;
    m_Idx.uiABTID = INVALID_INDEX;
    m_Idx.uiLOBID = INVALID_INDEX;

    m_uiIndex = INVALID_INDEX;

    if( false == m_QueIndex.Pop( & m_uiIndex ) ) {
    }
    else {
        //TRACE( "\n 생성 : I%d, A%d, B%d" , m_nIndex, m_Idx.nAET, m_Idx.nABT );
        //TRACE( "\nm_QueIndex.Pop[%d]", m_uiIndex );
        //m_QueIndex.Print();

        if( m_uiIndex != INVALID_INDEX ) {
            m_Idx.uiAETID = NextAETID();

        }
        else {
        }

    }

    ++ m_CoInstance;

    *puiAET = m_Idx.uiAETID;

}

/**
 * @brief     CELThreat
 * @param     unsigned int uiAET
 * @param     unsigned int * puiABT
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-02-01 11:46:41
 * @warning
 */
CELThreat::CELThreat( unsigned int uiAET, unsigned int *puiABT )
{
    m_pLeftChild = NULL;
    m_pRightChild = NULL;

    m_Idx.uiAETID = uiAET;
    m_Idx.uiABTID = INVALID_INDEX;
    m_Idx.uiLOBID = INVALID_INDEX;

    m_uiIndex = INVALID_INDEX;

    if( false == m_QueIndex.Pop( & m_uiIndex ) ) {
    }
    else {
        //TRACE( "\n 생성 : I%d, A%d, B%d" , m_nIndex, m_Idx.nAET, m_Idx.nABT );
        //TRACE( "\nm_QueIndex.Pop[%d]", m_uiIndex );
        //m_QueIndex.Print();

        if( m_uiIndex != INVALID_INDEX ) {
            m_Idx.uiABTID = NextABTID();

        }
        else {
        }

    }

    ++ m_CoInstance;

    *puiABT = m_Idx.uiABTID;

}

/**
 * @brief     ~CELThreat 소멸자에 할당한 AET, ABT 저장소 인덱스를 반환하여 재사용하도록 한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-07, 오후 12:09
 * @warning
 */
CELThreat::~CELThreat(void)
{

	// 메모리 해지한다.
	if( m_uiIndex > INVALID_INDEX ) {
        //TRACE( "\n m_QueIndex.Push[%d]", m_uiIndex );
		m_QueIndex.Push( m_uiIndex );
        //m_QueIndex.Print();
	}
    else {

    }

	-- m_CoInstance;

}

/**
 * @brief     특정 에미터의 노드를 삭제한다.
 * @param     int nAET
 * @param     CELThreat * pPrevThreat
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-24, 오후 3:35
 * @warning
 */
bool CELThreat::RemoveAET( unsigned int uiAETID, CELThreat *pPrevThreat )
{
	int i=0;
	bool bRet = false;
	CELThreat *pThreat;

	// 1. AET 찾기
	pThreat = m_pLeftChild;
	while( pThreat != NULL ) {
		if( pThreat->m_Idx.uiAETID == uiAETID ) {
			// 1. 자식 객체들 모두 삭제
			if( pThreat->m_pLeftChild != NULL ) {
				pThreat->m_pLeftChild->RemoveAll();
			}

			// 2. 트리 연결
			if( i == 0 ) {
				pPrevThreat->m_pLeftChild = pThreat->m_pRightChild;
			}
			else {
				pPrevThreat->m_pRightChild = pThreat->m_pRightChild;
			}

			// 3. 자신 객체 삭제
			delete pThreat;
			pThreat = NULL;
			bRet = true;

            m_QueAETID.Push( uiAETID );
            //m_QueAETID.Print();

			break;
		}

		pPrevThreat = pThreat;
		pThreat = pThreat->m_pRightChild;

		// 플레그
		++ i;

	}

	// AET 번호로 검색이 안 될 떄 때는 FALSE 로 리턴함.
	return bRet;

}

/**
 * @brief     특정 빔 노드를 삭제한다.
 * @param     int nABT
 * @param     CELThreat * pPrevThreat
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-24, 오후 3:35
 * @warning
 */
bool CELThreat::RemoveABT( unsigned int uiAETID, unsigned int uiABTID )
{
	int i=0;
    bool bRet=false;
	CELThreat *pThreat, *pPrevThreat, *pPrevAET=m_pRootThreat;

	// 1. AET 찾기
	pThreat = m_pLeftChild;
	while( pThreat != NULL ) {
		if( pThreat->m_Idx.uiAETID == uiAETID ) {
			pPrevThreat = pThreat;
			pThreat = pThreat->m_pLeftChild;
			while( pThreat != NULL ) {
				if( ( uiABTID > 0 ) && ( pThreat->m_Idx.uiABTID == uiABTID ) ) {
					// 1. 링크 연결
					if( i == 0 ) {
						pPrevThreat->m_pLeftChild = pThreat->m_pRightChild;
					}
					else {
						pPrevThreat->m_pRightChild = pThreat->m_pRightChild;
					}

					// 2. 해당 ABT 삭제
					delete pThreat;
                    pThreat = NULL;

					bRet = true;

//                     --m_iTotalOfABT;
//                     if( m_iTotalOfABT < 0 ) {
//                         TRACE( "\n m_iTotalOfABT[%d", m_iTotalOfABT );
//                     }
				}
                else {
				    pPrevThreat = pThreat;
				    pThreat = pThreat->m_pRightChild;
                }

				// 플레그
				++ i;
			}

            if( pPrevThreat != NULL ) {
                if( ( pPrevThreat->m_pLeftChild == NULL && pPrevThreat->m_Idx.uiABTID == 0 ) ) {
                    CELThreat *pPrevThreat_RightChild;

                    pPrevThreat_RightChild = pPrevThreat->m_pRightChild;

                    //TRACE( "\n 빔 목록이 없어서 해당 방사체 번호[%d]를 삭제합니다 !", nAET );

                    // 1. 트리 연결
                    if( pPrevAET != NULL /* && pPrevThreat != NULL */ ) {
                        if( i == 0 ) {
                            pPrevAET->m_pLeftChild = pPrevThreat_RightChild;
                        }
                        else {
                            if( pPrevAET != m_pRootThreat ) {
                                pPrevAET->m_pRightChild = pPrevThreat_RightChild;
                            }
                            else {
                                pPrevAET->m_pLeftChild = pPrevThreat_RightChild;
                            }
                        }

                        // 2. 자신 객체 삭제
                        delete pPrevThreat;
                        pPrevThreat = NULL;

                        m_QueAETID.Push( uiAETID );
                        //m_QueAETID.Print();

//                         --m_iTotalOfAET;
//                         if( m_iTotalOfAET < 0 ) {
//                             TRACE( "\n m_iTotalOfAET[%d", m_iTotalOfAET );
//                         }

                    }
                }

                // break;
            }

            break;

		}
        else {
            pPrevAET = pThreat;

#if 0
		    if( pThreat != NULL ) {
		        pThreat = pThreat->m_pRightChild;
		    }
#else
            pThreat = pThreat->m_pRightChild;
        }
#endif

	}

	return bRet;
}

/**
 * @brief     Remove
 * @param     SELINDEX * pIndex
 * @param     CELThreat * pPrevThreat
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-08, 오후 9:15
 * @warning
 */
// bool CELThreat::Remove( SELINDEX *pIndex, CELThreat *pPrevThreat ) {
// 	bool bRet = false;
//
// 	if( m_pLeftChild != NULL ) {
// 		m_pLeftChild->Remove( pIndex, this );
// 		m_pLeftChild = NULL;
// 	}
// 	if( m_pRightChild != NULL ) {
// 		m_pRightChild->Remove( pIndex, this );
// 		m_pRightChild = NULL;
// 	}
//
// 	if( pIndex->nAET == m_Idx.nAET && m_Idx.nAET != INVALID_INDEX ) {
// 		delete this;
// 		bRet = true;
// 	}
//
// 	return false;
//
// }

/**
 * @brief     모든 위협 의 노드들을 메모리 해지한다.
 * @param     void
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-08, 오후 9:16
 * @warning
 */
void CELThreat::RemoveAll()
{

	if( m_pLeftChild != NULL ) {
		m_pLeftChild->RemoveAll();
		m_pLeftChild = NULL;
	}
	if( m_pRightChild != NULL ) {
		m_pRightChild->RemoveAll();
		m_pRightChild = NULL;
	}

    //! #추후 : m_iTotalOfAET  이 값이 - 값이 나오는 경우가 있음.
    //m_iTotalOfAET = 0;
    //m_iTotalOfABT = 0;

	// 루트는 삭제 하지 않기 하기 위함.
	if( /*m_uiIndex != INVALID_INDEX &&*/ m_pRootThreat != this ) {
		// TRACE( "\n 삭제 : I%d, A%d, B%d" , m_nIndex, m_Idx.nAET, m_Idx.nABT );
		delete this;
	}

	return;

}

/**
 * @brief     AET 노드로부터 ABT 노드들 중에서 마지막 포인터를 리턴한다.
 * @param     CELThreat * pThreat
 * @return    CELThreat *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-04-07, 오후 2:06
 * @warning
 */
CELThreat *CELThreat::GetLastThreat( CELThreat *pThreat )
{
	CELThreat *pLastThreat=NULL;

	if( pThreat->IsAET() == true ) {
		pLastThreat = pThreat->m_pLeftChild;
	}
	else if( pThreat->IsABT() == true ) {
		pLastThreat = pThreat;
	}
	else {
		pLastThreat = NULL;
	}

	// 빔 노드일때 오른쪽 노드로 객체를 이동한다.
	if( pLastThreat != NULL ) {
		while( pLastThreat->m_pRightChild != NULL ) {
			pLastThreat = pLastThreat->m_pRightChild;

		}
	}

	return pLastThreat;

}

/**
 * @brief     위협 노드 간을 연결한다.
 * @param     CELThreat * pThreat
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-04-08, 오후 3:35
 * @warning
 */
void CELThreat::Link( CELThreat *pAddeThreatABT )
{
	CELThreat *pLinkThreat;

	// 루트 인 경우에는 LEFT 포인터를 변경
	if( IsRoot() == true ) {
		TRACE( "\n[경고] Link 함수[%d,%d]를 잘못 호출했습니다 !!!" , m_Idx.uiAETID, m_Idx.uiABTID );
	}
	else if( IsAET() == true ) {
		pLinkThreat = GetLastThreat( this );
        pLinkThreat->m_pRightChild = pAddeThreatABT;

        pAddeThreatABT->m_Idx.uiAETID = this->m_Idx.uiAETID;

	}
	else if( IsABT() == true ) {
		TRACE( "\n[경고] Link 함수를 [%04d/%04d]를 잘못 호출했습니다 !!!" , m_Idx.uiAETID, m_Idx.uiABTID );
	}
    else {
    }

}

/**
 * @brief     Move
 * @param     CELThreat * pMovingThreatAET
 * @param     CELThreat * pMovingThreatABT
 * @param     CELThreat * pMergedThreatAET
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-02-01 14:54:54
 * @warning
 */
void CELThreat::Move( CELThreat *pMovingThreatAET, CELThreat *pMovingThreatABT, CELThreat *pMergedThreatAET )
{

    // 1. 노드 연결
    pMovingThreatAET->UnLink( pMovingThreatABT );

    // 1.1 방사체에 하위 빔이 없으면 노드를 삭제해야 함.
    if( pMovingThreatAET->m_pLeftChild == NULL ) {
        m_pRootThreat->RemoveThreat( pMovingThreatAET->m_Idx.uiAETID );
    }

    //CELThreat::PrintAllThreat();

    pMergedThreatAET->Link( pMovingThreatABT );
    //CELThreat::PrintAllThreat();

}

/**
 * @brief     위협 노드의 링크 연결을 해지한다.
 * @param     CELThreat * pUnLinkABT
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-24, 10:31
 * @warning
 */
void CELThreat::UnLink( CELThreat *pUnLinkABT )
{
	CELThreat *pBeforeDeleteABT;

	// 루트 인 경우에는 LEFT 포인터를 변경
	if( IsRoot() == true ) {
		TRACE( "\n[경고] UnLink 함수[%d,%d]를 잘못 호출했습니다 !!!" , m_Idx.uiAETID, m_Idx.uiABTID );
	}
	else if( IsAET() == true ) {
		pBeforeDeleteABT = this->m_pLeftChild;

		// 첫번째 빔을 Unlink 할 경우
		if( pBeforeDeleteABT == pUnLinkABT ) {
			this->m_pLeftChild = pUnLinkABT->m_pRightChild;

			// 마지막 처리-빔 끊을 것의 다음 빔은 널로 함.
			pUnLinkABT->m_pRightChild = NULL;
		}
		else {
			// 두번째 빔을 Unlink 할 경우
			if( pBeforeDeleteABT != NULL ) {
				while( pBeforeDeleteABT->m_pRightChild != NULL && pBeforeDeleteABT->m_pRightChild != pUnLinkABT ) {
					pBeforeDeleteABT = pBeforeDeleteABT->m_pRightChild;
				}

				if( pBeforeDeleteABT->m_pRightChild == pUnLinkABT ) {
					pBeforeDeleteABT->m_pRightChild = pBeforeDeleteABT->m_pRightChild->m_pRightChild;

					// 마지막 처리-빔 끊을 것의 다음 빔은 널로 함.
					pUnLinkABT->m_pRightChild = NULL;
				}
				// 이전 빔이 없으면 연결할 빔 객체를 끊는다.
				else {
					TRACE( "\n [경고] Unlink 할 객체가 존재하지 않습니다 !!!" );
				}

			}
			else {
				TRACE( "\n [경고] 위협 관리 노드가 잘못 됐습니다 !!!" );
			}
		}
	}
	else if( IsABT() == true ) {
        TRACE( "\n[경고] UnLink 함수[%d,%d]를 잘못 호출했습니다 !!!", m_Idx.uiAETID, m_Idx.uiABTID );
	}
    else {

    }

}

