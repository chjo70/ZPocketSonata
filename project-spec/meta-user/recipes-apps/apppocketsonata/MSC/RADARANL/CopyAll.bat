echo off

echo.
echo =================================================================
echo %1, %2, %3


REM ���̴� �м��� ���� ===========================
IF NOT EXIST %1 goto ERROR
echo.
echo ===== ���̴� �м� ���̺귯�� (%1)
copy ..\%3\RADARANL.lib %1
copy ..\%3\RADARANL.dll %1
copy ..\%3\RADARANL.pdb %1

IF NOT EXIST %2 goto ERROR
echo.
echo ===== ���̴� �м� ��� ���� (%2)
copy RadarAnlAlgorithm.h %2
copy ..\..\files\Anal\SigAnal\_CED_Define.h %2
copy ..\..\files\Anal\SigAnal\_CED_Define.h .

:DONE
Echo ���̺귯���� ��� ������ ���� �����߽��ϴ�.
rem SET errorlevel=0
GOTO END2

:ERROR
Echo ������ �������� �ʾ� �������� ���߽��ϴ�.
rem SET errorlevel=1

:END2