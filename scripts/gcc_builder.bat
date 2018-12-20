::Root folder fot the project
set PROJECT_ROOT=D:\PROGRAMOWANIE\C\Judy\
set PROJECT_NAME=judy

::init
echo off
cls

::execution
echo %TIME% GCC Builder 
echo %TIME% Starting GCC...	
echo ==============================================================================
gcc -Wall -o %PROJECT_ROOT%\%PROJECT_NAME% 2>%PROJECT_ROOT%\logs\stderr.log %PROJECT_ROOT%\src\c\main.c %PROJECT_ROOT%\src\c\interface.c %PROJECT_ROOT%\src\c\fileIO.c %PROJECT_ROOT%\src\c\debug.c %PROJECT_ROOT%\src\c\toolbox.c %PROJECT_ROOT%\src\c\vigenere.c -I %PROJECT_ROOT%\src\h
echo ==============================================================================
echo %TIME% GCC Finished!
notepad++ %PROJECT_ROOT%\logs\stderr.log
