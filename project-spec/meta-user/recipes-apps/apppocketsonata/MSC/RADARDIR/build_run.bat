echo off


REM X��� ��Ž�� ======================================
IF NOT EXIST D:\RADAR\RADAR_DF\Debug goto ERROR
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_RD\Debug"
copy ..\RadarDirAlgorithm.h "\\192.168.0.41\Files\���̺귯��\���̴� ��Ž"
goto DONE

REM X��� ��Ž�� ======================================
IF NOT EXIST \\192.168.0.41\Files\���̺귯��\���̴� ��Ž goto ERROR
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_RD\Debug"
copy ..\RadarDirAlgorithm.h "\\192.168.0.41\Files\���̺귯��\���̴� ��Ž"
goto DONE
rem copy ..\DEBUG\RADARDIR.pdb "\\192.168.0.41\Files\���̺귯��\���̴� ��Ž"
rem copy ..\RADARDIR\RadarDirAlgorithm.h "\\192.168.0.41\Files\���̺귯��\���̴� ��Ž"

rem copy $(TargetDir)\$(TargetName).lib "z:\���̴� ��Ž"
rem copy $(TargetDir)\$(TargetName).dll "z:\���̴� ��Ž"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarDirAlgorithm.h "z:\���̴� ��Ž"

:ERROR
Echo �̵��� ������ ��� �������� ���߽��ϴ�.
goto END

:DONE
Echo ���� �Ϸ� �߽��ϴ�.

:END
