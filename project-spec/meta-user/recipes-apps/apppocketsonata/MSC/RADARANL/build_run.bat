echo off


REM ########################################################################
REM  �۾��ǿ���...
REM SET RADAR_DF_LIB=E:\GitHub\RADAR_DF\Debug
REM SET RADAR_DF_HEADER=E:\GitHub\RADAR_DF\ICAA

REM �Ʒ��� ȸ�翡��...
SET RADAR_DF_LIB=E:\X ���\DevSrc\RADAR_DF\Debug
SET RADAR_DF_HEADER=E:\X ���\DevSrc\RADAR_DF\ICAA


REM ########################################################################
REM  �۾��ǿ���...
REM SET RADAR_RD_LIB=E:\GitHub\RADAR_RD\Debug
REM SET RADAR_RD_HEADER=E:\GitHub\RADAR_RD\ICAA

REM �Ʒ��� ȸ�翡��...
SET RADAR_RD_LIB=E:\X ���\DevSrc\RADAR_RD\Debug
SET RADAR_RD_HEADER=E:\X ���\DevSrc\RADAR_RD\ICAA


REM X��� ��Ž�� ======================================
IF NOT EXIST "%RADAR_DF_LIB%" goto ERROR
echo ===== ���̴� �м� ���̺귯�� (%RADAR_DF_LIB%)
copy ..\DEBUG\RADARANL.lib "%RADAR_DF_LIB%"
copy ..\DEBUG\RADARANL.dll "%RADAR_DF_LIB%"
copy ..\DEBUG\RADARANL.pdb "%RADAR_DF_LIB%"

echo.
echo ===== ���̴� �м� ��� ���� (%RADAR_DF_HEADER%)
copy RadarAnlAlgorithm.h "%RADAR_DF_HEADER%"

IF NOT EXIST "%RADAR_RD_LIB%" goto ERROR
echo ===== ���̴� �м� ���̺귯�� (%RADAR_RD_LIB%)
copy ..\DEBUG\RADARANL.lib "%RADAR_RD_LIB%"
copy ..\DEBUG\RADARANL.dll "%RADAR_RD_LIB%"
copy ..\DEBUG\RADARANL.pdb "%RADAR_RD_LIB%"

echo.
echo ===== ���̴� �м� ��� ���� (%RADAR_RD_HEADER%)
copy RadarAnlAlgorithm.h "%RADAR_RD_HEADER%"

rem copy RADARANLAPP\RadarAnl.ini "\\192.168.0.41\Files\���̺귯��\���̴� �м�"

rem copy $(TargetDir)\$(TargetName).lib "z:\���̴� �м�"
rem copy $(TargetDir)\$(TargetName).dll "z:\���̴� �м�"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarAnlAlgorithm.h "z:/���̴� �м�"

:DONE
echo.
Echo ***** ���� �Ϸ� �߽��ϴ�.
goto END

:ERROR
Echo �̵��� ����(%RADAR_DF_FOLDER%)�� ��� �������� ���߽��ϴ�.
goto END

:END
