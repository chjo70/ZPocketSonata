echo off

echo
echo =================================================================
echo %1


REM ���̴� �м��� ���� ===========================
IF NOT EXIST %1 goto ERROR
echo.
echo ===== ���̴� �м� ���̺귯�� (%1)
copy ..\Debug\DeltaGraph.* %1


:DONE
Echo ���� ������ ���� �����߽��ϴ�.
rem SET errorlevel=0
GOTO END2

:ERROR
Echo ������ �������� �ʾ� �������� ���߽��ϴ�.
rem SET errorlevel=1

:END2