@echo off

echo %1 Solution Dir
echo %2 Target Dir

xcopy "%~1res" "%~2res" /i /y /s
tar --create --file=game.zip -C "%~1bin" .
