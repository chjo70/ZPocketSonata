echo off

rem
copy ..\DEBUG\RADARDIR.lib "\\192.168.0.41\Files\라이브러리\레이더 방탐"
copy ..\DEBUG\RADARDIR.dll "\\192.168.0.41\Files\라이브러리\레이더 방탐"
copy ..\DEBUG\RADARDIR.pdb "\\192.168.0.41\Files\라이브러리\레이더 방탐"
copy ..\RADARDIR\RadarDirAlgorithm.h "\\192.168.0.41\Files\라이브러리\레이더 방탐"

rem copy $(TargetDir)\$(TargetName).lib "z:\레이더 방탐"
rem copy $(TargetDir)\$(TargetName).dll "z:\레이더 방탐"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarDirAlgorithm.h "z:\레이더 방탐"