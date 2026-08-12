# Counter App

A small Windows C++ counter app with a simple UI.

## Features

- Shows the current count
- Increment, decrement, and reset buttons
- Built with raw Win32 APIs, no third-party dependencies

## Build

### Visual Studio

Open `CounterApp.sln` in Visual Studio 2022 and build the solution.

### CMake

If you have CMake installed, you can also configure and build from the command line:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

## Run

Start the built executable from Visual Studio or from the build output folder.
