echo off

BUILD_SPEC=VSourceBuild_T2MS32_PPCE6500gnu_SMP


del d:/tftpboot/VSIGA.out


REM 지정 타겟 소스에 
rem cp ./VSourceBuild_T2MS32_PPCE6500gnu_SMP/VSIGA/Debug/VSIGA.out ../VBootShell/default/.
rem cp ./VSourceBuild_T2MS32_PPCE6500gnu_SMP/VSIGA/Debug/VSIGA.out d:/tftpboot/.

cp ./$(BUILD_SPEC)/VSIGA/Debug/VSIGA.out ../VBootShell/default/.
cp ./$(BUILD_SPEC)/VSIGA/Debug/VSIGA.out d:/tftpboot/.
