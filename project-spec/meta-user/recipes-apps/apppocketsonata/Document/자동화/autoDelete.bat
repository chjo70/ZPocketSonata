@echo off

for /l %%i in ( 1, 1, 5 ) do (
	echo. & echo ==== EW ��ȣó���� #%%i���� ���� �մϴ�. ======= & echo.

	echo    --- Ž�� ������ ���� �մϴ�... -----
	forfiles /p "D:\rawdata\BRD_%%i\Ž��" /s /m * /D -7 /C "cmd /c del /q @path"
	forfiles /p "D:\rawdata\BRD_%%i\Ž��" /s /m * /D -7 /C "cmd /c if @isdir==TRUE rd /s /q @path"
	
	echo    --- ���� ������ ���� �մϴ�... -----
	forfiles /p "D:\rawdata\BRD_%%i\����" /s /m * /D -7 /C "cmd /c del /q @path"
	forfiles /p "D:\rawdata\BRD_%%i\����" /s /m * /D -7 /C "cmd /c if @isdir==TRUE rd /s /q @path"
	
	echo    --- ��ĵ ������ ���� �մϴ�... -----
	forfiles /p "D:\rawdata\BRD_%%i\��ĵ" /s /m * /D -7 /C "cmd /c del /q @path"
	forfiles /p "D:\rawdata\BRD_%%i\��ĵ" /s /m * /D -7 /C "cmd /c if @isdir==TRUE rd /s /q @path"
	
	rem echo & echo.
)

echo. & echo �������� ���ϴ�. ========================= & echo.

rd /s /q d:\$Recycle.Bin
