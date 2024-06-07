@echo off

echo === graphics ===
tools\gbfs test.gbfs test.chr test.txt

echo === code ===
gcc -Wall -O -mthumb -mthumb-interwork -s -o x.elf test.c libgbfs.c
if errorlevel 1 goto end
objcopy -O binary x.elf x.bin

tools\padbin 256 x.bin
copy /b x.bin+test.gbfs test.mb.gba

del x.elf
del x.bin
:end


