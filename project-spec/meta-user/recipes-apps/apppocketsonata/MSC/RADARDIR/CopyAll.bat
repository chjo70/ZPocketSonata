echo off

echo
echo =================================================================
echo %1, %2, %3, %4, %5


REM 레이더 방탐기 복사 ===========================
IF NOT EXIST %1 goto ERROR
echo ===== 레이더 방탐 라이브러리 (%1)
copy ..\%5\RADARDIR.lib %1
copy ..\%5\RADARDIR.dll %1
copy ..\%5\RADARDIR.pdb %1

echo.
echo ===== 레이더 방탐 헤더 파일 (%2)
copy RadarDirAlgorithm.h %2

REM 레이더 분석기 복사 ===========================
IF NOT EXIST %3 goto ERROR
echo.
echo ===== 레이더 방탐 라이브러리 (%3)
copy ..\%5\RADARDIR.lib %3
copy ..\%5\RADARDIR.dll %3
copy ..\%5\RADARDIR.pdb %3

echo.
echo ===== 레이더 방탐 헤더 파일 (%4)
copy RadarDirAlgorithm.h %4

:DONE
Echo 라이브러리와 헤더 파일을 정상 복사했습니다.
rem SET errorlevel=0
GOTO END2

:ERROR
Echo 폴더가 존재하지 않아 복사하지 못했습니다.
rem SET errorlevel=1

:END2