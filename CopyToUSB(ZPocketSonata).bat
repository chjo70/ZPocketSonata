echo off

cls

REM ########################################################################
color 17
ECHO.
ECHO Files ������ ���� �մϴ�.
xcopy .\dev\files ..\RADAR\ZPocketSonata\project-spec\meta-user\recipes-apps\apppocketsonata\files /E/C/I/Y/D/F/U

REM ########################################################################
color 27
ECHO.
ECHO Documents ������ ���� �մϴ�.
xcopy .\dev\Document ..\RADAR\ZPocketSonata\project-spec\meta-user\recipes-apps\apppocketsonata\Document /E/C/I/Y/D/F/U

REM ########################################################################
color 47
ECHO.
ECHO MSC ������ ���� �մϴ�.
xcopy .\dev\MSC ..\RADAR\ZPocketSonata\project-spec\meta-user\recipes-apps\apppocketsonata\MSC /E/C/I/Y/D/F/U

color

ECHO.
ECHO.
rem pause
timeout 10