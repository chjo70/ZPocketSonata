echo off

REM X밴드 방탐기 ======================================
IF NOT EXIST D:\RADAR\RADAR_DF\Debug goto ERROR
copy ..\DEBUG\RADARANL.lib "D:\Radar\RADAR_RD\Debug"
copy ..\DEBUG\RADARANL.dll "D:\Radar\RADAR_RD\Debug"
copy ..\DEBUG\RADARANL.pdb "D:\Radar\RADAR_RD\Debug"
rem copy ..\RADARANLAPP\RadarAnl.ini "\\192.168.0.41\Files\라이브러리\레이더 분석"
rem copy RadarAnlAlgorithm.h "\\192.168.0.41\Files\라이브러리\레이더 분석"

rem copy $(TargetDir)\$(TargetName).lib "z:\레이더 분석"
rem copy $(TargetDir)\$(TargetName).dll "z:\레이더 분석"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarAnlAlgorithm.h "z:/레이더 분석"

:ERROR
Echo 이동할 폴더가 없어서 복사하지 못했습니다.
goto END

:DONE
Echo 복사 완료 했습니다.

:END
