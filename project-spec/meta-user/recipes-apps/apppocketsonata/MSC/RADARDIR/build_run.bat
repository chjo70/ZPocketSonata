echo off


REM X밴드 방탐기 ======================================
IF NOT EXIST D:\RADAR\RADAR_DF\Debug goto ERROR
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_RD\Debug"
copy ..\RadarDirAlgorithm.h "\\192.168.0.41\Files\라이브러리\레이더 방탐"
goto DONE

REM X밴드 방탐기 ======================================
IF NOT EXIST \\192.168.0.41\Files\라이브러리\레이더 방탐 goto ERROR
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_RD\Debug"
copy ..\RadarDirAlgorithm.h "\\192.168.0.41\Files\라이브러리\레이더 방탐"
goto DONE
rem copy ..\DEBUG\RADARDIR.pdb "\\192.168.0.41\Files\라이브러리\레이더 방탐"
rem copy ..\RADARDIR\RadarDirAlgorithm.h "\\192.168.0.41\Files\라이브러리\레이더 방탐"

rem copy $(TargetDir)\$(TargetName).lib "z:\레이더 방탐"
rem copy $(TargetDir)\$(TargetName).dll "z:\레이더 방탐"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarDirAlgorithm.h "z:\레이더 방탐"

:ERROR
Echo 이동할 폴더가 없어서 복사하지 못했습니다.
goto END

:DONE
Echo 복사 완료 했습니다.

:END
