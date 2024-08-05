@echo off
:START 
set TOOL=stm32f103c8.jflash
set FILE=.\bin\app.bin
start ./JFlashTool/JFlashARM.exe -openprj./JFlashTool/%TOOL% -open%FILE%,0x8000000 -auto -startapp -exit

