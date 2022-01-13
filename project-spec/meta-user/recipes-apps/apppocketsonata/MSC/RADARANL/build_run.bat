echo off

REM X밴드 방탐기 ======================================
IF NOT EXIST D:\RADAR\RADAR_DF\Debug goto ERROR
echo 레이더 방탐 라이브러리
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_DF\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_DF\Debug"

echo 레이더 방탐 헤더 파일
copy RadarAnlAlgorithm.h "D:\RADAR\RADAR_DF\ICAA"

IF NOT EXIST D:\RADAR\RADAR_RD\Debug goto ERROR
echo 레이더 방탐 라이브러리
copy ..\DEBUG\RADARDIR.lib "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.dll "D:\RADAR\RADAR_RD\Debug"
copy ..\DEBUG\RADARDIR.pdb "D:\RADAR\RADAR_RD\Debug"

echo 레이더 방탐 헤더 파일
copy RadarAnlAlgorithm.h "D:\RADAR\RADAR_RD\ICAA"

rem copy RADARANLAPP\RadarAnl.ini "\\192.168.0.41\Files\라이브러리\레이더 분석"

rem copy $(TargetDir)\$(TargetName).lib "z:\레이더 분석"
rem copy $(TargetDir)\$(TargetName).dll "z:\레이더 분석"
rem copy $(RemoteDebuggerWorkingDirectory)\RadarAnlAlgorithm.h "z:/레이더 분석"

:DONE
Echo 복사 완료 했습니다.
goto END

:ERROR
Echo 이동할 폴더가 없어서 복사하지 못했습니다.
goto END

:END
