// SDefine.h: interface for the 스캔분석판 소프트웨어의 정의
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDEFINE_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_SDEFINE_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _MSC_VER
//#define	M_PI									(3.1415926535)
#endif

#define	_spPaHistBinSize                (256)
#define	_spDtoaHistBinSize              (1024)

#define	_spMaxSample                    (600*2)
#define	_spCoSteadyCollect              (4)

#define	_spCoBreakPulse                 (3)				// debug, 99-11-06 15:22:09

#define	_spMinPrd						(3)

#define	_spFlatness						(1.0)
#define	_spSkewness						(1.0)

#define	_spMinMSEThr					(0.5)

#define _spScnPrdErrRat				    (0.05)		// 5 % error of scan period

#define _spMinCoUnderThr			    (5) 			// under threshold

#define _spMinPeaksInSpanTime	        (3)
#define _spMinPeakRatio				    (0.9)

#define	_spFilterRatio				    (0.95)					// 필터링의 전체 개수의 필터링율의 Threshold
//#define	_spNeighborTh					(3./_spAMPres)	// Neighbor Threshold


#define SEADY_PA_MARGIN                 UDIV( 3.0, _spAMPres )         // 3dBm
#define SEADY_PA_DEVIATION              UDIV( 1.0, _spAMPres )         // 3dBm


#endif // !defined(AFX_SDEFINE_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)

