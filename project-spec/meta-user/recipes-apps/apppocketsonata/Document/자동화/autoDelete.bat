@echo off

for /l %%i in ( 1, 1, 5 ) do (
	echo. & echo ==== EW 신호처리판 #%%i번을 삭제 합니다. ======= & echo.

	echo    --- 탐지 폴더를 삭제 합니다... -----
	forfiles /p "D:\rawdata\BRD_%%i\탐지" /s /m * /D -7 /C "cmd /c del /q @path"
	forfiles /p "D:\rawdata\BRD_%%i\탐지" /s /m * /D -7 /C "cmd /c if @isdir==TRUE rd /s /q @path"
	
	echo    --- 추적 폴더를 삭제 합니다... -----
	forfiles /p "D:\rawdata\BRD_%%i\추적" /s /m * /D -7 /C "cmd /c del /q @path"
	forfiles /p "D:\rawdata\BRD_%%i\추적" /s /m * /D -7 /C "cmd /c if @isdir==TRUE rd /s /q @path"
	
	echo    --- 스캔 폴더를 삭제 합니다... -----
	forfiles /p "D:\rawdata\BRD_%%i\스캔" /s /m * /D -7 /C "cmd /c del /q @path"
	forfiles /p "D:\rawdata\BRD_%%i\스캔" /s /m * /D -7 /C "cmd /c if @isdir==TRUE rd /s /q @path"
	
	rem echo & echo.
)

echo. & echo 휴지통을 비웁니다. ========================= & echo.

rd /s /q d:\$Recycle.Bin
