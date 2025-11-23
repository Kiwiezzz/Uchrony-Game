# Uchrony-Game

## Compilación multiplataforma (Windows / Linux / macOS)

Este repositorio usa CMake y SFML. Se ha añadido soporte en `CMakeLists.txt` para buscar SFML  dentro de la carpeta `lib/` (controlable con la opción `-DUSE_BUNDLED_SFML=ON/OFF`). A continuación se describen pasos por sistema operativo y opciones recomendadas.

Instrucciones por plataforma

Linux (incluye WSL):

```bash
cmake -S . -B out/build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DUSE_BUNDLED_SFML=ON
cmake --build out/build -j$(nproc)
```

Windows (Visual Studio/Powershell):

cmake -S . -B out/build -G "Visual Studio 17 2022" -A x64 -DUSE_BUNDLED_SFML=ON
cmake --build out/build --config Release
Copy-Item -Path .\lib\SFML-2.6.2\bin\*.dll -Destination .\out\build\bin\Release -Force
& .\out\build\bin\Release\UchronyGame_Executable.exe
```

macOS:

1. Instala SFML con Homebrew (`brew install sfml`) o provee SFML en `lib/` con los archivos CMake.
2. Configura y compila:
```bash
cmake -S . -B out/build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build out/build -j$(sysctl -n hw.ncpu)
```

