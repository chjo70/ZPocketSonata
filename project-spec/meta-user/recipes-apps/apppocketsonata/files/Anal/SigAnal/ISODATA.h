// ISODATA.h: interface for the CISODATA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CISODATA_H_)
#define _CISODATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../OFP_Main.h"


#ifdef __cplusplus

//////////////////////////////////////////////////////////////////////
/*!	\brief	최대 2차 특성을 가진 클러스터링 알고리즘 이다. 차수를 늘리려면 멤버 변수를 추가해야 한다.
    \author 조철희
    \date   2008-01-15 08:57:55
*/
class CISODATA
{
protected:
    unsigned int m_uiN;
    unsigned int m_uiClusters;

    // ISODATA 그룹화를 하기 위한 데이터 변수

    // 실제 PDW 값
    unsigned int **m_ppPDWParam;

    // 표준화 작업한 값
    float **m_ppfPDWParam;

    STR_CLUSTER *m_pCluster;


private:
    void InitOfISODATA( STR_PDWINDEX *pSrcIndex, UINT *pPDW1, UINT *pPDW2 );
    void MakeStandard( float *pfPDWParam, STR_MINMAX_SDEV *pstStat, UINT *pPDWParam, STR_PDWINDEX *pSrcIndex );

    bool IsSplitCluster( STR_CLUSTER *pCluster );
    bool SplitCenter( STR_CLUSTER *pCluster, STR_CLUSTER *pDstCluster );
    void SplitCenter( STR_CLUSTER *pDstCluster1, STR_CLUSTER *pDstCluster2, STR_CLUSTER *pSrcCluster );
    void CalcSplitCluster( STR_CLUSTER *pDstCluster1, STR_CLUSTER *pDstCluster2, STR_CLUSTER *pSrcCluster );
    void CopyCluster( STR_CLUSTER *pDstCluster, STR_CLUSTER *pSrcCluster );
    float CalcDistance( STR_CLUSTER *pDstCluster1, PDWINDEX usPDWIndex );

    void CalParamStat( STR_MINMAX_SDEV *pstStat, UINT *pPDWParam, STR_PDWINDEX *pSrcIndex );
    void CalAOAStat( STR_MINMAX_SDEV *pstStat, UINT *pPDWParam, STR_PDWINDEX *pSrcIndex );
    void CalClusterInfo( STR_CLUSTER *pCluster );
    void CalClusterInfo( STR_CLUSTER *pCluster, unsigned int uiN );

    // 디버깅 정보 출력
    void MarkPDWIndexByAllCluster( STR_CLUSTER *pDstCluster, STR_PDWINDEX *pSrcIndex );

public:
    void Run( STR_PDWINDEX *pSrcIndex, UINT *pPDW1, UINT *pPDW2 = NULL );

    CISODATA( unsigned int uiN, unsigned int uiCoMaxPDW=NEW_COLLECT_PDW );
	virtual ~CISODATA();

    /**
     * @brief     클러스터 시작 포인터를 리턴한다.
     * @return    STR_CLUSTER *
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-25, 17:16
     * @warning
     */
    inline STR_CLUSTER *GetCluster() {
        return m_pCluster;
    }

    /**
     * @brief     클러스터링 개수를 리턴한다.
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-25, 17:17
     * @warning
     */
    inline unsigned int GetCoCluster() {
        return m_uiClusters;
    }

};

#endif

#endif

