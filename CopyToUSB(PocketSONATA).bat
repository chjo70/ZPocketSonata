echo off

cls

REM ########################################################################
color 17
ECHO.
ECHO Files ������ ���� �մϴ�...
xcopy .\project-spec\meta-user\recipes-apps\apppocketsonata\files \PocketSONATA\dev_\files /E/C/I/Y/F/U/D
ECHO.

REM ########################################################################
color 27
ECHO.
ECHO Documents ������ ���� �մϴ�...
xcopy .\project-spec\meta-user\recipes-apps\apppocketsonata\Document \PocketSONATA\dev_\Document /E/C/I/Y/D/F/U
ECHO.

REM ########################################################################
color 47
ECHO.
ECHO MSC ������ ���� �մϴ�...
xcopy .\project-spec\meta-user\recipes-apps\apppocketsonata\MSC \PocketSONATA\dev_\MSC /E/C/I/Y/D/F/U
ECHO.


REM ########################################################################
color 57
ECHO.
ECHO VxWorks ������ ���� �մϴ�.
xcopy .\project-spec\meta-user\recipes-apps\apppocketsonata\VxWorksSpace \PocketSONATA\dev_\VxWorksSpace /E/C/I/Y/F/U/D

color

ECHO.
ECHO.
pause