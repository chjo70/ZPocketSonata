echo off

REM ########################################################################
REM  작업실에서...
SET RADAR_DF_LIB=E:\GitHub\RADAR_DF\Debug
SET RADAR_DF_HEADER=E:\GitHub\RADAR_DF\ICAA

REM 아래는 회사에서...
REM SET RADAR_DF_LIB=E:\X 밴드\DevSrc\RADAR_DF\Debug
REM SET RADAR_DF_HEADER=E:\X 밴드\DevSrc\RADAR_DF\ICAA


REM ########################################################################
REM  작업실에서...

echo $(ConfigurationName)
IF $(ConfigurationName)==Release echo "AAAA"

SET RADAR_RD_LIB=E:\GitHub\RADAR_RD\Debug
SET RADAR_RD_HEADER=E:\GitHub\RADAR_RD\ICAA

REM 아래는 회사에서...
REM SET RADAR_RD_LIB=E:\X 밴드\DevSrc\RADAR_RD\Debug
REM SET RADAR_RD_HEADER=E:\X 밴드\DevSrc\RADAR_RD\ICAA

REM X밴드 방탐기 ======================================
IF NOT EXIST "%RADAR_DF_LIB%" goto ERROR
echo ===== 레이더 방탐 라이브러리 (%RADAR_DF_LIB%)
copy ..\DEBUG\RADARDIR.lib "%RADAR_DF_LIB%"
copy ..\DEBUG\RADARDIR.dll "%RADAR_DF_LIB%"
copy ..\DEBUG\RADARDIR.pdb "%RADAR_DF_LIB%"

echo.
echo ===== 레이더 방탐 헤더 파일 (%RADAR_DF_HEADER%)
copy RadarDirAlgorithm.h "%RADAR_DF_HEADER%"

IF NOT EXIST "%RADAR_RD_LIB%" goto ERROR
echo.
echo ===== 레이더 방탐 라이브러리 (%RADAR_RD_LIB%)
copy ..\DEBUG\RADARDIR.lib "%RADAR_RD_LIB%"
copy ..\DEBUG\RADARDIR.dll "%RADAR_RD_LIB%"
copy ..\DEBUG\RADARDIR.pdb "%RADAR_RD_LIB%"

echo.
echo ===== 레이더 방탐 헤더 파일 (%RADAR_RD_HEADER%)
copy RadarDirAlgorithm.h "%RADAR_RD_HEADER%"

goto DONE

REM 인천 공항 ======================================
IF NOT EXIST \\192.168.0.41\Files\라이브러리\레이더 방탐 goto ERROR
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_RD\Debug"
copy ..\RadarDirAlgorithm.h "\\192.168.0.41\Files\라이브러리\레이더 방탐"
goto DONE
rem copy ..\DEBUG\RADARDIR.pdb "\\192.168.0.41\Files\라이브러리\레이더 방탐"
rem copy ..\RADARDIR\RadarDirAlgorithm.h "\\192.168.0.41\Files\라이브러리\레이더 방탐"

rem copy $(TargetDir)\$(TargetName).lib "z:\레이더 방탐"
rem copy $(TargetDir)\$(TargetName).dll "z:\레이더 방탐"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarDirAlgorithm.h "z:\레이더 방탐"

:ERROR
echo.
Echo 이동할 폴더(%RADAR_DF_FOLDER%)가 없어서 복사하지 못했습니다.
goto END

:DONE
echo.
Echo ***** 복사 완료 했습니다.

:END
