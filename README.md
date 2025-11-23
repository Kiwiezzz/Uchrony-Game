# Uchrony-Game

## Compilación multiplataforma (Windows / Linux / macOS)

Este proyecto usa CMake y SFML. El `CMakeLists.txt` del repositorio contiene una opción `USE_BUNDLED_SFML` que controla si CMake debe buscar primero SFML dentro de la carpeta `lib/` del repo. Atención: SFML en la carpeta lib es unica y exclusivamente para windows, NO USAR en las otras dos plataformas (Linux/Mac), para ellas hay que instalar sus respectivas bibliotecas de sfml desde la terminal.

Instrucciones por plataforma (comandos listos)

Linux (nativo o WSL)

1. Instala SFML del sistema (ej. Debian/Ubuntu):
```bash
sudo apt update
sudo apt install libsfml-dev
```
2. Configura y compila (usa `build/` como directorio de salida):
```bash
rm -rf build
cmake -S . -B build -DUSE_BUNDLED_SFML=OFF
cmake --build build -j$(nproc)
./build/bin/UchronyGame_Executable
```

Comando resumido
```bash
if [ -d "build" ]; then rm -rf build; fi && cmake -S . -B build -DUSE_BUNDLED_SFML=OFF && cmake --build build -j$(nproc) && ./build/bin/UchronyGame_Executable
```

Windows (Visual Studio/PowerShell)

```powershell
cd C:\Users\LENOVO\OneDrive\Escritorio\Uchrony-Game
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DUSE_BUNDLED_SFML=ON
cmake --build build --config Release
# Copiar DLLs de SFML/bin al directorio del ejecutable si enlazaste dinámicamente
Copy-Item -Path .\lib\SFML-2.6.2\bin\*.dll -Destination .\build\bin\Release -Force
& .\build\bin\Release\UchronyGame_Executable.exe
```

Opción B — usar `vcpkg` (recomendado para reproducibilidad):
```powershell
# instalar SFML en vcpkg (ejemplo)
# C:\tools\vcpkg\vcpkg.exe install sfml:x64-windows
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 `
  -DCMAKE_TOOLCHAIN_FILE=C:\tools\vcpkg\scripts\buildsystems\vcpkg.cmake `
  -DUSE_BUNDLED_SFML=OFF
cmake --build build --config Release
```

macOS

1. Instala SFML (por ejemplo con Homebrew):
```bash
brew install sfml
```
2. Configura y compila:
```bash
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DUSE_BUNDLED_SFML=OFF
cmake --build build -j$(sysctl -n hw.ncpu)
```

Consejos prácticos
- Si CMake muestra errores del tipo "CMakeCache.txt directory ... is different..." borra el directorio `build/` y vuelve a ejecutar CMake desde la raíz del repo.
- Para ejecutar el binario localmente en Linux/WSL usa `./build/bin/Release/UchronyGame_Executable` (o la ruta que muestre tu configuración).
- Para Windows, si faltan DLLs al ejecutar, copia las DLLs de `lib/SFML-2.x/bin` al directorio del ejecutable o añádelas al `PATH`.

