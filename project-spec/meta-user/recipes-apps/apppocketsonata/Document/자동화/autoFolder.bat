@echo off

for /l %%i in ( 1, 1, 5 ) do (
	echo EW ��ȣó���� #%%i���� ���� �մϴ�...
	forfiles /p "D:\rawdata\BRD_%%i\Ž��" /s /m * /D -%1 /C "cmd /c if @isdir==TRUE echo rd /s /q @path"
	forfiles /p "D:\rawdata\BRD_%%i\����" /s /m * /D -%1 /C "cmd /c if @isdir==TRUE echo rd /s /q @path"
	forfiles /p "D:\rawdata\BRD_%%i\��ĵ" /s /m * /D -%1 /C "cmd /c if @isdir==TRUE echo rd /s /q @path"
	echo ''

)

echo rd /s d:\$Recycle.Bin