echo off

REM X��� ��Ž�� ======================================
IF NOT EXIST D:\RADAR\RADAR_DF\Debug goto ERROR
echo ���̴� ��Ž ���̺귯��
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_DF\Debug"

echo ���̴� ��Ž ��� ����
copy RadarAnlAlgorithm.h "D:\RADAR\RADAR_DF\ICAA"

IF NOT EXIST D:\RADAR\RADAR_RD\Debug goto ERROR
echo ���̴� ��Ž ���̺귯��
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_RD\Debug"

echo ���̴� ��Ž ��� ����
copy RadarAnlAlgorithm.h "D:\RADAR\RADAR_RD\ICAA"

rem copy RADARANLAPP\RadarAnl.ini "\\192.168.0.41\Files\���̺귯��\���̴� �м�"

rem copy $(TargetDir)\$(TargetName).lib "z:\���̴� �м�"
rem copy $(TargetDir)\$(TargetName).dll "z:\���̴� �м�"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarAnlAlgorithm.h "z:/���̴� �м�"

:DONE
Echo ���� �Ϸ� �߽��ϴ�.
goto END

:ERROR
Echo �̵��� ������ ��� �������� ���߽��ϴ�.
goto END

:END
