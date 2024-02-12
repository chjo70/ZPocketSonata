/**

    @file      clog.h
    @brief
    @details   ~
    @author    조철희
    @date      30.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#include "../Anal/INC/PDW.h"

#include "../Include/system.h"

class CLogName {
private:
    static char m_szName[enETC_ANAL + 1][10];

    const char *m_pThreadName;

    ENUM_ANAL_TYPE m_enAnalType;

protected:
    CLogName();
    CLogName( const char *pThreadName );
    virtual ~CLogName();

    /**
     * @brief     GetThreadName
     * @return    const char *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-23 09:36:34
     * @warning
     */
    const char *GetThreadName() const
    {
        return m_pThreadName;
    }

    /**
     * @brief     SetThreadName
     * @param     const char * pThreadName
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-23 09:36:31
     * @warning
     */
    void SetThreadName( const char *pThreadName )
    {
        m_pThreadName = pThreadName;
    }

    /**
     * @brief     GetAnalType
     * @return    const ENUM_ANAL_TYPE
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-23 10:09:13
     * @warning
     */
    const ENUM_ANAL_TYPE GetAnalType() const
    {
        return m_enAnalType;
    }

    /**
     * @brief     SetAnalType
     * @param     ENUM_ANAL_TYPE enAlanType
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-23 09:36:29
     * @warning
     */
    void SetAnalType( ENUM_ANAL_TYPE enAlanType )
    {
        m_enAnalType = enAlanType;
    }

    /**
     * @brief     IsLogAnalType
     * @return    bool
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-23 09:38:47
     * @warning
     */
    bool IsLogAnalType( LogType enLogType ) const
    {
        bool bRet = true;

        if( enLogType == enError || enLogType == enNormal || g_enLogAnalType == enALL ) {
        }
        else {
            if( g_enLogAnalType == enCLEAR_ANAL ) {
                bRet = false;
            }
            else {
                ENUM_ANAL_TYPE enAnalType = GetAnalType();

                if( enAnalType == enETC_ANAL ) {
                }
                else {

                    bRet = ( enAnalType & g_enLogAnalType ) > 0 ? true : false;
                }
            }
        }

        return bRet;
    }

    /**
     * @brief     GetAnalName
     * @return    char *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-10-25 13:27:51
     * @warning
     */
    char *GetAnalName()
    {

        return m_szName[ (unsigned int) GetAnalType()];
    }

};

