::Root folder for the project
set PROJECT_ROOT=D:\PROGRAMOWANIE\C\Judy\
set PROJECT_NAME=judy

::init
echo off
cls
::jump to log
notepad++ %PROJECT_ROOT%\logs\debug.log
::run app
%PROJECT_ROOT%\%PROJECT_NAME%.exe %PROJECT_ROOT%\data.txt
::pause