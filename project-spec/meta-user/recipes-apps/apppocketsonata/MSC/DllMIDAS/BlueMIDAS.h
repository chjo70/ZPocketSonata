/**

    @file      DllMIDAS.h
    @brief
    @details   ~
    @author    조철희
    @date      5.06.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport)

#else
#define MATHFUNCSDLL_API __declspec(dllimport)
#endif


#include "../../files/Anal/MIDAS/sel_keyword_value.h"


//
// RADARDIR 프로젝트 내에서 최소 내용만 구조체 정의를 복사한 것임.


namespace BlueMIDAS
{
    // This class is exported from the MathFuncsDll.dll
    class BlueMIDAS {
    public:
        static MATHFUNCSDLL_API void Init( HWND hWnd = 0, bool bLocal = false );
        static MATHFUNCSDLL_API void SetMute( bool bEnable );
        static MATHFUNCSDLL_API void SWInit();

        static MATHFUNCSDLL_API bool PDW2MIDAS( char *pszSourceFilename, char *pszOutputFilename, SEL_KEYWORD_VALUE *pstValue );

        static MATHFUNCSDLL_API void Close();

#pragma data_seg( ".ioshare" )
        // static CLog *g_pTheLog;
#pragma data_seg()


    };

}



