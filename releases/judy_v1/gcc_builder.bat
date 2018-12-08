::Root folder fot the project
set PROJECT_ROOT=D:\PROGRAMOWANIE\C\Judy\releases\judy_v1
set PROJECT_NAME=judy

::init
echo off
cls

::execution
echo %TIME% GCC Builder 
echo %TIME% Starting GCC...	
echo ==============================================================================
gcc -o %PROJECT_ROOT%\%PROJECT_NAME% %PROJECT_ROOT%\src\c\main.c %PROJECT_ROOT%\src\c\interface.c %PROJECT_ROOT%\src\c\fileIO.c -I %PROJECT_ROOT%\src\h
echo ==============================================================================
echo %TIME% GCC Finished!
