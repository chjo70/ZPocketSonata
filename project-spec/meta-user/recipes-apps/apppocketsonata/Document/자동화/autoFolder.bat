@echo off

for /l %%i in ( 1, 1, 5 ) do (
	echo EW 신호처리판 #%%i번을 삭제 합니다...
	forfiles /p "D:\rawdata\BRD_%%i\탐지" /s /m * /D -%1 /C "cmd /c if @isdir==TRUE echo rd /s /q @path"
	forfiles /p "D:\rawdata\BRD_%%i\추적" /s /m * /D -%1 /C "cmd /c if @isdir==TRUE echo rd /s /q @path"
	forfiles /p "D:\rawdata\BRD_%%i\스캔" /s /m * /D -%1 /C "cmd /c if @isdir==TRUE echo rd /s /q @path"
	echo ''

)

echo rd /s d:\$Recycle.Bin