echo off

REM X��� ��Ž�� ======================================
IF NOT EXIST D:\RADAR\RADAR_DF\Debug goto ERROR
copy ..\DEBUG\RADARANL.lib "D:\Radar\RADAR_RD\Debug"
copy ..\DEBUG\RADARANL.dll "D:\Radar\RADAR_RD\Debug"
copy ..\DEBUG\RADARANL.pdb "D:\Radar\RADAR_RD\Debug"
rem copy ..\RADARANLAPP\RadarAnl.ini "\\192.168.0.41\Files\���̺귯��\���̴� �м�"
rem copy RadarAnlAlgorithm.h "\\192.168.0.41\Files\���̺귯��\���̴� �м�"

rem copy $(TargetDir)\$(TargetName).lib "z:\���̴� �м�"
rem copy $(TargetDir)\$(TargetName).dll "z:\���̴� �м�"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarAnlAlgorithm.h "z:/���̴� �м�"

:ERROR
Echo �̵��� ������ ��� �������� ���߽��ϴ�.
goto END

:DONE
Echo ���� �Ϸ� �߽��ϴ�.

:END
