@echo off
echo Current working directory: %cd%
cd %~dp0
echo Changed to script directory: %cd%
python auto_copy.py

:START 
set TOOL=stm32f103c8.jflash
set FILE=.\burn\bin\app.bin
start ./burn/JFlashTool/JFlashARM.exe -openprj./burn/JFlashTool/%TOOL% -open%FILE%,0x8000000 -auto -startapp -exit