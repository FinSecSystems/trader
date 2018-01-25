# trader

This project is a framework to quickly connect with cryptocurrency and traditional exchanges that utillize REST JSON, FIX or Websockets.

## Build & Run Instructions

### Windows

#### Setup Instructions 

- Run build\shell.cmd
- Build poco with deploy_poco.cmd
- Build Intel SE API with deploy_intelseapi.cmd
- Run build\genproj.cmd once to generate Visual Studio 2015 or Visual Studio 2017 projects

## Compilation
- Open trader.sln
- Build solution
  - At the moment the project dependencies are not setup correctly
  - Also the project makes use of code generators to generate code, that needs to get included into the project before compiliation
  - You might have to build, rebuild the solution 2 - 3 times before it compiles successfully.

## Project Structure
- genproj - This re-runs premake to generate the project and solutions structure. You might need to re-run this if a new file is added or generated
- codegen - This is the code generator. It includes several code generators to transform, json, xml to c++ code. This needs to be built before apis, configs, databases, interface
- apis - This runs codegen to transform the hyperschema.json files in data/apis to c++ code. Hyperschema is a proposed format to describe REST/JSON apis as json files ([Hyperschema Format](http://json-schema.org/latest/json-schema-hypermedia.html))
- interfaces - This runs codegen to transform the fix api xml specs to a c++ interface that can be used to standardize the communication interface between the various modules.
- configs - This runs codegen to transform the config.json files in data/configs to c++ code. These are used for the simple key-value pair json configs to setup api keys right now.
- databases - This runs codegen to transform the databaseschema.json files data/databases to c++ code.
- dataconnector - This is meant to be a library that allows one to connect to multiple exchanges. It servers as an API extraction layer and exposes a standardize fix c++ interface for applications to use.
- trader - This is a sample application to interact with dataconnector

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

