echo off

REM ########################################################################
REM  �۾��ǿ���...
SET RADAR_DF_LIB=E:\GitHub\RADAR_DF\Debug
SET RADAR_DF_HEADER=E:\GitHub\RADAR_DF\ICAA

REM �Ʒ��� ȸ�翡��...
REM SET RADAR_DF_LIB=E:\X ���\DevSrc\RADAR_DF\Debug
REM SET RADAR_DF_HEADER=E:\X ���\DevSrc\RADAR_DF\ICAA


REM ########################################################################
REM  �۾��ǿ���...

echo $(ConfigurationName)
IF $(ConfigurationName)==Release echo "AAAA"

SET RADAR_RD_LIB=E:\GitHub\RADAR_RD\Debug
SET RADAR_RD_HEADER=E:\GitHub\RADAR_RD\ICAA

REM �Ʒ��� ȸ�翡��...
REM SET RADAR_RD_LIB=E:\X ���\DevSrc\RADAR_RD\Debug
REM SET RADAR_RD_HEADER=E:\X ���\DevSrc\RADAR_RD\ICAA

REM X��� ��Ž�� ======================================
IF NOT EXIST "%RADAR_DF_LIB%" goto ERROR
echo ===== ���̴� ��Ž ���̺귯�� (%RADAR_DF_LIB%)
copy ..\DEBUG\RADARDIR.lib "%RADAR_DF_LIB%"
copy ..\DEBUG\RADARDIR.dll "%RADAR_DF_LIB%"
copy ..\DEBUG\RADARDIR.pdb "%RADAR_DF_LIB%"

echo.
echo ===== ���̴� ��Ž ��� ���� (%RADAR_DF_HEADER%)
copy RadarDirAlgorithm.h "%RADAR_DF_HEADER%"

IF NOT EXIST "%RADAR_RD_LIB%" goto ERROR
echo.
echo ===== ���̴� ��Ž ���̺귯�� (%RADAR_RD_LIB%)
copy ..\DEBUG\RADARDIR.lib "%RADAR_RD_LIB%"
copy ..\DEBUG\RADARDIR.dll "%RADAR_RD_LIB%"
copy ..\DEBUG\RADARDIR.pdb "%RADAR_RD_LIB%"

echo.
echo ===== ���̴� ��Ž ��� ���� (%RADAR_RD_HEADER%)
copy RadarDirAlgorithm.h "%RADAR_RD_HEADER%"

goto DONE

REM ��õ ���� ======================================
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
echo.
Echo �̵��� ����(%RADAR_DF_FOLDER%)�� ��� �������� ���߽��ϴ�.
goto END

:DONE
echo.
Echo ***** ���� �Ϸ� �߽��ϴ�.

:END
