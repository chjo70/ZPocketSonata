echo off

echo
echo =================================================================
echo %1


REM 레이더 분석기 복사 ===========================
IF NOT EXIST %1 goto ERROR
echo.
echo ===== 레이더 분석 라이브러리 (%1)
copy ..\Debug\DeltaGraph.* %1


:DONE
Echo 실행 파일을 정상 복사했습니다.
rem SET errorlevel=0
GOTO END2

:ERROR
Echo 폴더가 존재하지 않아 복사하지 못했습니다.
rem SET errorlevel=1

:END2