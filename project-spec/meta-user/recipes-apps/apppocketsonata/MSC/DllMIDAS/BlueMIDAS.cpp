
#include "pch.h"
#include "framework.h"

#define MATHFUNCSDLL_EXPORTS

#define _MAIN_GLOBALS_

using namespace std;

#include <io.h>
#include <fcntl.h>

#include "BlueMIDAS.h"

#include "../../Files/Anal/Collect/DataFile/DataFile.h"
#include "../../Files/Anal/MIDAS/Midas.h"

#include "../../Files/Utils/clogname.h"

CMIDASBlueFileFormat *g_pMIDAS;

// CLogName 에 있는 클래스의 전역 변수 선언 합니다.
char CLogName::m_szName[enETC_ANAL+1][10];


namespace BlueMIDAS
{

	/**
	 * @brief     Init
	 * @param     HWND hWnd
	 * @param     bool bLocal
	 * @return    void
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-06-05 10:12:12
	 * @warning
	 */
	void BlueMIDAS::Init( HWND hWnd, bool bLocal )
	{

        if( g_pMIDAS == NULL ) {
            g_pMIDAS = new CMIDASBlueFileFormat();
        }

		return;
	}

	/**
	 * @brief     SetMute
	 * @param     bool bEnable
	 * @return    void
	 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   1.0.0
	 * @date      2023-06-05 10:12:13
	 * @warning
	 */
	void BlueMIDAS::SetMute( bool bEnable )
	{

		return;
	}

    /**
     * @brief     PDW2MIDAS
     * @param     char * pszSourceFilename
     * @param     char * pszOutputFilename
     * @param     SEL_KEYWORD_VALUE * pstValue
     * @return    bool
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-06-06 16:54:06
     * @warning
     */
    bool BlueMIDAS::PDW2MIDAS( char *pszSourceFilename, char *pszOutputFilename, SEL_KEYWORD_VALUE *pstValue )
    {
        bool bRet=false;
        int iFile;

        if( g_pMIDAS != NULL ) {
            iFile = _open( (char *) pszSourceFilename, _O_RDONLY | _O_BINARY );
            if( iFile > 0 ) {
                //g_pMIDAS->InitIFMidas();
                g_pMIDAS->SaveMIDASFormat( pszOutputFilename, E_EL_SCDT_PDW, ( int ) iFile, (int) 0, pstValue, NULL, NULL );

//bool SaveMIDASFormat( char *pMidasFileName, EnumSCDataType enFileType, int i_pstReadFile, int i_nFileRawDataStartOffset, SEL_KEYWORD_VALUE * pstKeywordValue, char *pInputFilename, char *pTaskID );

                _close( iFile );
            }


            bRet = true;
        }

        return bRet;

    }

	/**
	 * @brief     탐지 분석 DLL 을 종료 처리한다. 반드시 마지막에 호출해야 한다.
	 * @return    void
	 * @exception
	 * @author    조철희 (churlhee.jo@lignex1.com)
	 * @version   0.0.1
	 * @date      2022-01-08, 13:23
	 * @warning
	 */
	void BlueMIDAS::Close()
	{
        if( g_pMIDAS != NULL ) {
            delete g_pMIDAS;
        }

		return;
	}



}


