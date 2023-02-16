echo off

del d:/tftpboot/VSIGA.out
cp ./VSourceBuild_PPCE6500gnu_SMP/VSIGA/Debug/VSIGA.out ../VBootShell/default/.
cp ./VSourceBuild_PPCE6500gnu_SMP/VSIGA/Debug/VSIGA.out d:/tftpboot/.
