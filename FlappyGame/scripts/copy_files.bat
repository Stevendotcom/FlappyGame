@echo off

echo %1 Solution Dir
echo %2 Target Dir

if "%3"=="1" (
    echo Copying and packing
    del "%~1bin\Release\FlappyGame.pdb"
    xcopy "%~1res" "%~2res" /i /y /s
    tar --create --file=FlappyGame.zip -C "%~1bin\Release" .
) ELSE (
xcopy "%~1res" "%~2res" /i /y /s
)


pause