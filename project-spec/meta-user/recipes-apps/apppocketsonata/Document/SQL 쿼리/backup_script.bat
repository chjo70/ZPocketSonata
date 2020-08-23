@echo off

sqlcmd -S localhost -i "Reset_LOBData.sql" -U sa -P fractal
sqlcmd -S localhost -i "Reset_ABTData.sql" -U sa -P fractal