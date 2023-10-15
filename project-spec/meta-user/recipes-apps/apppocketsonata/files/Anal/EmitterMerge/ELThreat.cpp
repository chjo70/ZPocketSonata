/**
 * @file      ELThreat.cpp
 * @brief
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-20, 오후 8:17
 * @warning
 */

#include "stdafx.h"


#include "ELThreat.h"

Queue<unsigned int> CELThreat::m_QueIndex;
int CELThreat::m_CoInstance=0;
int CELThreat::m_iTotalOfABT = 0;
int CELThreat::m_iTotalOfAET = 0;

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
CELThreat::CELThreat(void)
{
    unsigned int i; // , ui;

	m_pLeftChild = NULL;
	m_pRightChild = NULL;

    m_Idx.uiAET = 0;
    m_Idx.uiABT = 0;
    m_Idx.uiLOB = 0;

	if( m_CoInstance == 0 ) {
		m_QueIndex.Init( TOTAL_ITEMS_OF_THREAT_NODE );
		for( i=0 ; i < TOTAL_ITEMS_OF_THREAT_NODE ; ++i ) {

            //ui = (unsigned int) ( g_enBoardId << 28 ) | i;
			m_QueIndex.Push( i );
		}
	}

	if( false == m_QueIndex.Pop( & m_uiIndex ) ) {
		m_uiIndex = INVALID_INDEX;
	}

	++ m_CoInstance;

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
		m_QueIndex.Push( m_uiIndex );
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
bool CELThreat::RemoveAET( int nAET, CELThreat *pPrevThreat )
{
	int i=0;
	bool bRet = false;
	CELThreat *pThreat;

	// 1. AET 찾기
	pThreat = m_pLeftChild;
	while( pThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
		if( pThreat->m_Idx.uiAET == (UINT) nAET ) {
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

            --m_iTotalOfAET;

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
bool CELThreat::RemoveABT( int nAET, int nABT )	//#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found.)
{
	int i=0;
    bool bRet=false;
	CELThreat *pThreat, *pPrevThreat, *pPrevAET=m_pRootThreat;

	// 1. AET 찾기
	pThreat = m_pLeftChild;
	while( pThreat != NULL ) {
		if( pThreat->m_Idx.uiAET == (UINT) nAET ) {
			pPrevThreat = pThreat;
			pThreat = pThreat->m_pLeftChild;
			while( pThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
				if( ( nABT > 0 ) && ( pThreat->m_Idx.uiABT == (UINT) nABT ) ) {
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

                    --m_iTotalOfABT;

                    /*! \debug  삭제 했으면 빠져 나온다.
                    	\author 조철희 (churlhee.jo@lignex1.com)
                    	\date 	2023-06-26 09:49:45
                    */
                    // break;
				}
                else {
				    pPrevThreat = pThreat;
				    pThreat = pThreat->m_pRightChild;
                }

				// 플레그
				++ i;
			}

            if( pPrevThreat != NULL && ( pPrevThreat->m_pLeftChild == NULL && pPrevThreat->m_Idx.uiABT == 0 ) ) {
                CELThreat *pPrevThreat_RightChild;

                TRACE( "\n 빔 목록이 없어서 해당 방사체 번호[%d]를 삭제합니다 !", nAET );

                // RemoveThreat( nAET );

                pPrevThreat_RightChild = pPrevThreat->m_pRightChild;

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

                    --m_iTotalOfAET;
                }

                break;
            }

		}

        pPrevAET = pThreat;

		if( pThreat != NULL ) {
			pThreat = pThreat->m_pRightChild;
		}

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

    m_iTotalOfAET = 0;
    m_iTotalOfABT = 0;

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
		while( pLastThreat->m_pRightChild != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
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
void CELThreat::Link( CELThreat *pDeleteABT, CELThreat *pDeleteAET )
{
	CELThreat *pLinkThreat, *pBeforeDeleteABT;

	// 루트 인 경우에는 LEFT 포인터를 변경
	if( IsRoot() == true ) {
		TRACE( "\n[경고] 링크 노드[%d,%d]를 잘못 호출했습니다 !!!" , m_Idx.uiAET, m_Idx.uiABT );
	}
	else if( IsAET() == true ) {
		if( pDeleteAET == NULL ) {
			this->m_pLeftChild = pDeleteABT;
			pDeleteABT->m_Idx.uiAET = m_Idx.uiAET;
		}
		else {
			//
			pLinkThreat = GetLastThreat( this );
			if( pLinkThreat != NULL ) {
				// 1. 현재 빔 노드 마지막에 링크할 노드를 연결한다.
				pLinkThreat->m_pRightChild = pDeleteABT;

				// 2. 삭제할 빔의 이전 빔 노드를 찾는다.
				pBeforeDeleteABT = pDeleteAET->m_pLeftChild;
				if( pBeforeDeleteABT != NULL ) {

					if( pBeforeDeleteABT != pDeleteABT ) {
						while( pBeforeDeleteABT->m_pRightChild != NULL && pBeforeDeleteABT->m_pRightChild != pDeleteABT ) {
							pBeforeDeleteABT = pBeforeDeleteABT->m_pRightChild;
						}
						// 이전 빔이 있으면 삭제할 빔을 생략하고 링크를 연결한다.
						if( pBeforeDeleteABT->m_pRightChild == pDeleteABT ) {
							pBeforeDeleteABT->m_pRightChild = pDeleteABT->m_pRightChild;
						}
						// 이전 빔이 없으면 연결할 빔 객체를 끊는다.
						else {
							pDeleteAET->m_pLeftChild = NULL;
						}
					}
					else {
						pDeleteAET->m_pLeftChild = pDeleteAET->m_pLeftChild->m_pRightChild;
					}
				}
				else {
					TRACE( "\n[경고] 삭제할 노드의 빔객체가 잘못됐습니다 !!!" );
				}

				// 삭제할 빔 노드의 다음번재 노드는 NULL 로 마킹한다.
				pDeleteABT->m_pRightChild = NULL;

				// 방사체 번호 변경
				pDeleteABT->m_Idx.uiAET = m_Idx.uiAET;
			}
			else {
				TRACE( "\n [경고] 위협 관리 노드가 잘못 됐습니다 !!!" );
			}
// 			if( pDeleteAET != NULL ) {
// 				pDeleteAET->m_pLeftChild = NULL;
// 			}

		}
	}
	else if( IsABT() == true ) {
		TRACE( "\n[경고] 링크 노드[%d,%d]를 잘못 호출했습니다 !!!" , m_Idx.uiAET, m_Idx.uiABT );
	}
    else {
    }

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
		TRACE( "\n[경고] 링크 노드[%d,%d]를 잘못 호출했습니다 !!!" , m_Idx.uiAET, m_Idx.uiABT );
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
		TRACE( "\n [경고] 빔을 제거할 수 없습니다 !!!!, 잘못 호출했습니다." );
	}
    else {

    }

}

