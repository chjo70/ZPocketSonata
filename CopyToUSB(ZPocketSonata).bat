echo off

cls

color 17

REM ########################################################################
ECHO.
ECHO Files ������ ���� �մϴ�.
xcopy .\dev\files \RADAR\ZPocketSonata\project-spec\meta-user\recipes-apps\apppocketsonata\files /E/C/I/Y/D/F/U

REM ########################################################################
ECHO.
ECHO Documents ������ ���� �մϴ�.
xcopy .\dev\Document \RADAR\ZPocketSonata\project-spec\meta-user\recipes-apps\apppocketsonata\Document /E/C/I/Y/D/F/U

REM ########################################################################
ECHO.
ECHO MSC ������ ���� �մϴ�.
xcopy .\dev\MSC \RADAR\ZPocketSonata\project-spec\meta-user\recipes-apps\apppocketsonata\MSC /E/C/I/Y/D/F/U

color

ECHO.
ECHO.
pause