@echo off

rem TODO: Allow for different options for different builds (i.e. debug/release)
rem TODO: Analyze the following: -fp:fast, -Zo

set COMPILER_OPTIONS=-Od -MTd -nologo -fp:fast -Gm- -GR- -EHsc -Oi -FC -Z7 -WX -W4 -wd4100 -wd4189 -wd4505 -wd4201 -wd4244
set LINKER_OPTIONS=-incremental:no -opt:ref -nologo -SUBSYSTEM:CONSOLE
set FILES=..\generator.cpp ..\settingsclass.cpp ..\word.cpp ..\inih-master\cpp\INIReader.cpp ..\inih-master\ini.c
set LIBRARIES=SDL2.lib SDL2main.lib setupapi.lib opengl32.lib user32.lib gdi32.lib winmm.lib imm32.lib ole32.lib oleaut32.lib version.lib uuid.lib shell32.lib advapi32.lib
set EXECUTABLE_NAME=test.exe
set DEFINES=-D_CRT_SECURE_NO_WARNINGS
set INCLUDE_DIRECTORIES=-I..\sdl2\include
set LIBRARY_DIRECTORIES=-libpath:..\sdl2\lib\x64\

rem if not exist bin mkdir bin
if not exist build mkdir build

pushd build

del *.pdb > NUL 2> NUL

cl -Fe%EXECUTABLE_NAME% %COMPILER_OPTIONS% %DEFINES% %FILES% %INCLUDE_DIRECTORIES% -link %LINKER_OPTIONS% %LIBRARIES% %LIBRARY_DIRECTORIES%

popd