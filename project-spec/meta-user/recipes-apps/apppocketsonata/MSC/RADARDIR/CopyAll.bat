echo off

echo
echo =================================================================
echo %1, %2, %3, %4, %5


REM ���̴� ��Ž�� ���� ===========================
IF NOT EXIST %1 goto ERROR
echo ===== ���̴� ��Ž ���̺귯�� (%1)
copy ..\%5\RADARDIR.lib %1
copy ..\%5\RADARDIR.dll %1
copy ..\%5\RADARDIR.pdb %1

echo.
echo ===== ���̴� ��Ž ��� ���� (%2)
copy RadarDirAlgorithm.h %2

REM ���̴� �м��� ���� ===========================
IF NOT EXIST %3 goto ERROR
echo.
echo ===== ���̴� ��Ž ���̺귯�� (%3)
copy ..\%5\RADARDIR.lib %3
copy ..\%5\RADARDIR.dll %3
copy ..\%5\RADARDIR.pdb %3

echo.
echo ===== ���̴� ��Ž ��� ���� (%4)
copy RadarDirAlgorithm.h %4

:DONE
Echo ���̺귯���� ��� ������ ���� �����߽��ϴ�.
rem SET errorlevel=0
GOTO END2

:ERROR
Echo ������ �������� �ʾ� �������� ���߽��ϴ�.
rem SET errorlevel=1

:END2