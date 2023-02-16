echo off

cls

REM ########################################################################
color 17
ECHO.
ECHO Files 폴더를 복사 합니다...
xcopy .\project-spec\meta-user\recipes-apps\apppocketsonata\files \PocketSONATA\dev_\files /E/C/I/Y/F/U/D
ECHO.

REM ########################################################################
color 27
ECHO.
ECHO Documents 폴더를 복사 합니다...
xcopy .\project-spec\meta-user\recipes-apps\apppocketsonata\Document \PocketSONATA\dev_\Document /E/C/I/Y/D/F/U
ECHO.

REM ########################################################################
color 47
ECHO.
ECHO MSC 폴더를 복사 합니다...
xcopy .\project-spec\meta-user\recipes-apps\apppocketsonata\MSC \PocketSONATA\dev_\MSC /E/C/I/Y/D/F/U
ECHO.


REM ########################################################################
color 57
ECHO.
ECHO VxWorks 폴더를 복사 합니다.
xcopy .\project-spec\meta-user\recipes-apps\apppocketsonata\VxWorksSpace \PocketSONATA\dev_\VxWorksSpace /E/C/I/Y/F/U/D

color

ECHO.
ECHO.
pause