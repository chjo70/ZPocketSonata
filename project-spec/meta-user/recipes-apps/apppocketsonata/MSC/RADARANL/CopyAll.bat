echo off

echo
echo =================================================================
echo %1, %2, %3


REM 레이더 분석기 복사 ===========================
IF NOT EXIST %1 goto ERROR
echo.
echo ===== 레이더 분석 라이브러리 (%1)
copy ..\%3\RADARANL.lib %1
copy ..\%3\RADARANL.dll %1
copy ..\%3\RADARANL.pdb %1

IF NOT EXIST %2 goto ERROR
echo.
echo ===== 레이더 분석 헤더 파일 (%2)
copy RadarAnlAlgorithm.h %2

:DONE
Echo 라이브러리와 헤더 파일을 정상 복사했습니다.
rem SET errorlevel=0
GOTO END2

:ERROR
Echo 폴더가 존재하지 않아 복사하지 못했습니다.
rem SET errorlevel=1

:END2