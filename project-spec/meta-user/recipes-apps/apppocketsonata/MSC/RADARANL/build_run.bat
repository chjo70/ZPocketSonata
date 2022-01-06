echo off

copy ..\DEBUG\RADARANL.lib "\\192.168.0.41\Files\라이브러리\레이더 분석"
copy ..\DEBUG\RADARANL.dll "\\192.168.0.41\Files\라이브러리\레이더 분석"
copy ..\DEBUG\RADARANL.pdb "\\192.168.0.41\Files\라이브러리\레이더 분석"
copy ..\RADARANLAPP\RadarAnl.ini "\\192.168.0.41\Files\라이브러리\레이더 분석"
copy RadarAnlAlgorithm.h "\\192.168.0.41\Files\라이브러리\레이더 분석"

rem copy $(TargetDir)\$(TargetName).lib "z:\레이더 분석"
rem copy $(TargetDir)\$(TargetName).dll "z:\레이더 분석"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarAnlAlgorithm.h "z:/레이더 분석"