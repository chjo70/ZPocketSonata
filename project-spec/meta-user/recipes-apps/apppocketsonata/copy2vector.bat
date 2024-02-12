@echo off

echo ==== 수정된 소스를 VectorCast 폴더로 복사합니다. ======= & echo.

xcopy files\* ..\..\..\..\..\ZPocketSonataT_VectorCast\project-spec\meta-user\recipes-apps\apppocketsonata\files\* /e /Y

xcopy MSC\MSIGA\*.cpp ..\..\..\..\..\ZPocketSonataT_VectorCast\project-spec\meta-user\recipes-apps\apppocketsonata\MSC\MSIGA\*.cpp /Y
xcopy MSC\MSIGA\*.h ..\..\..\..\..\ZPocketSonataT_VectorCast\project-spec\meta-user\recipes-apps\apppocketsonata\MSC\MSIGA\*.h /Y
xcopy MSC\MSIGA\*.rc ..\..\..\..\..\ZPocketSonataT_VectorCast\project-spec\meta-user\recipes-apps\apppocketsonata\MSC\MSIGA\*.rc /Y

echo ==== 복사 완료 했습니다. ======= & echo.


