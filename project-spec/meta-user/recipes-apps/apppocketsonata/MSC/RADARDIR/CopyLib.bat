echo off

echo $(ConfigurationName)

SET CONFIGNAME=$(ConfigurationName)


REM ########################################################################

REM  작업실에서...


SET RADAR_DF_LIB="E:\GitHub\RADAR_DF\$(ConfigurationName)"
SET RADAR_DF_HEADER="E:\GitHub\RADAR_DF\ICAA"
SET RADAR_RD_LIB="E:\GitHub\RADAR_RD\$(ConfigurationName)"
SET RADAR_RD_HEADER="E:\GitHub\RADAR_RD\ICAA"

CALL CopyAll %RADAR_DF_LIB%, %RADAR_DF_HEADER%, %RADAR_RD_LIB%, %RADAR_RD_HEADER%, %CONFIGNAME%

REM ########################################################################
REM 아래는 회사에서...
SET RADAR_RD_LIB="E:\X 밴드\DevSrc\RADAR_RD\$(ConfigurationName)"
SET RADAR_RD_HEADER="E:\X 밴드\DevSrc\RADAR_RD\ICAA"

SET RADAR_DF_LIB="E:\X 밴드\DevSrc\RADAR_DF\$(ConfigurationName)"
SET RADAR_DF_HEADER="E:\X 밴드\DevSrc\RADAR_DF\ICAA"

CALL CopyAll %RADAR_DF_LIB%, %RADAR_DF_HEADER%, %RADAR_RD_LIB%, %RADAR_RD_HEADER%, %CONFIGNAME%

REM ########################################################################
REM 아래는 온품에서...
SET RADAR_RD_LIB="D:\RADAR\RADAR_RD\$(ConfigurationName)"
SET RADAR_RD_HEADER="D:\RADAR\RADAR_RD\ICAA"

SET RADAR_DF_LIB="D:\RADAR\RADAR_DF\$(ConfigurationName)"
SET RADAR_DF_HEADER="D:\RADAR\RADAR_DF\ICAA"

CALL CopyAll %RADAR_DF_LIB%, %RADAR_DF_HEADER%, %RADAR_RD_LIB%, %RADAR_RD_HEADER%, %CONFIGNAME%

REM echo errorlevel

REM If errorlevel 0 goto DONE
REM echo.
REM Echo 이동할 폴더(%RADAR_DF_FOLDER%)가 없어서 복사하지 못했습니다.
REM goto END

REM :DONE
REM echo.
REM Echo ***** 복사 완료 했습니다.

REM :END
