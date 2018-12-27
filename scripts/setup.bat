echo off
cls
set PROJECT_ROOT=C:\Users\Greg\Dropbox\PROGRAMOWANIE\C\Judy\
set PROJECT_NAME=judy
notepad++

notepad++ %PROJECT_ROOT%\src\c\main.c
::notepad++ %PROJECT_ROOT%\src\h\debug.h
notepad++ %PROJECT_ROOT%\src\c\fileIO.c
notepad++ %PROJECT_ROOT%\src\c\interface.c
notepad++ %PROJECT_ROOT%\src\c\debug.c
notepad++ %PROJECT_ROOT%\src\c\toolbox.c
notepad++ %PROJECT_ROOT%\src\c\vigenere.c

notepad++ %PROJECT_ROOT%\src\h\config.h
::notepad++ %PROJECT_ROOT%\src\h\fileIO.h
::notepad++ %PROJECT_ROOT%\src\h\interface.h


notepad++ %PROJECT_ROOT%\scripts\run_project.bat
notepad++ %PROJECT_ROOT%\scripts\gcc_builder.bat

notepad++ %PROJECT_ROOT%\logs\stderr.log
notepad++ %PROJECT_ROOT%\logs\debug.log