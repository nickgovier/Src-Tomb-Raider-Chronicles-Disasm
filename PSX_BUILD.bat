mingw32-make
call PSX_EXPORT_OVERLAYS.bat
call PSX_MOVE_OVERLAYS.bat
call PSX_CREATE_CODEWAD.bat
call PSX_CREATE_GAMEWAD.bat
cd DISC
CPE2X MAIN.CPE
call MAKEISO.bat
cd ../