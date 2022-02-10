echo off


REM ########################################################################
REM  작업실에서...
REM SET RADAR_DF_LIB=E:\GitHub\RADAR_DF\Debug
REM SET RADAR_DF_HEADER=E:\GitHub\RADAR_DF\ICAA

REM 아래는 회사에서...
SET RADAR_DF_LIB=E:\X 밴드\DevSrc\RADAR_DF\Debug
SET RADAR_DF_HEADER=E:\X 밴드\DevSrc\RADAR_DF\ICAA


REM ########################################################################
REM  작업실에서...
REM SET RADAR_RD_LIB=E:\GitHub\RADAR_RD\Debug
REM SET RADAR_RD_HEADER=E:\GitHub\RADAR_RD\ICAA

REM 아래는 회사에서...
SET RADAR_RD_LIB=E:\X 밴드\DevSrc\RADAR_RD\Debug
SET RADAR_RD_HEADER=E:\X 밴드\DevSrc\RADAR_RD\ICAA


REM X밴드 방탐기 ======================================
IF NOT EXIST "%RADAR_DF_LIB%" goto ERROR
echo ===== 레이더 분석 라이브러리 (%RADAR_DF_LIB%)
copy ..\DEBUG\RADARANL.lib "%RADAR_DF_LIB%"
copy ..\DEBUG\RADARANL.dll "%RADAR_DF_LIB%"
copy ..\DEBUG\RADARANL.pdb "%RADAR_DF_LIB%"

echo.
echo ===== 레이더 분석 헤더 파일 (%RADAR_DF_HEADER%)
copy RadarAnlAlgorithm.h "%RADAR_DF_HEADER%"

IF NOT EXIST "%RADAR_RD_LIB%" goto ERROR
echo ===== 레이더 분석 라이브러리 (%RADAR_RD_LIB%)
copy ..\DEBUG\RADARANL.lib "%RADAR_RD_LIB%"
copy ..\DEBUG\RADARANL.dll "%RADAR_RD_LIB%"
copy ..\DEBUG\RADARANL.pdb "%RADAR_RD_LIB%"

echo.
echo ===== 레이더 분석 헤더 파일 (%RADAR_RD_HEADER%)
copy RadarAnlAlgorithm.h "%RADAR_RD_HEADER%"

rem copy RADARANLAPP\RadarAnl.ini "\\192.168.0.41\Files\라이브러리\레이더 분석"

rem copy $(TargetDir)\$(TargetName).lib "z:\레이더 분석"
rem copy $(TargetDir)\$(TargetName).dll "z:\레이더 분석"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarAnlAlgorithm.h "z:/레이더 분석"

:DONE
echo.
Echo ***** 복사 완료 했습니다.
goto END

:ERROR
Echo 이동할 폴더(%RADAR_DF_FOLDER%)가 없어서 복사하지 못했습니다.
goto END

:END
