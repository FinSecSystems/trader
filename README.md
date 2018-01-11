# trader

This project is a framework to quickly connect with cryptocurrency and traditional exchanges that utillize REST JSON, FIX or Websockets.

## Build & Run Instructions

### Windows

#### Setup Instructions 

- Run build\shell.cmd
- Build poco with deploy_poco.cmd
- Run build\genproj.cmd once to generate Visual Studio 2015 or Visual Studio 2017 projects

## Compilation
- Open trader.sln
- Build solution

## Running
- Copy bin\*.json & bin\*.properties to bin\debug on bin\release and modify the config with the relevant api keys and proxy settings
- Right-click trader project and Set as StartUp Project
- Press F5 to run/debug in Visual Studio

### Linux/WSL

#### Setup Instructions
- Run build\shell.cmd
- Build poco with deploy_poco.sh
- Run build\genproj.sh once to generate makefiles for the project
- Copy bin\*.json & bin\*.properties to bin\debug on bin\release and modify the config with the relevant api keys and proxy settings

## Compilation
- Run make

## Running
- Run using script build\run_debug_<compiler>.sh

## Debug
- Run build\debug_<compiler>.sh

### MacOS X
~This has not been tested~
~Will be supported in the near future~

