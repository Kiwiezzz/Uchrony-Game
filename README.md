# UCHRONY GAME: Explorando los Pasados Alternativos

[![GitHub license](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Built with C++](https://img.shields.io/badge/Built%20with-C%2B%2B%2020-red.svg)](https://www.cplusplus.com/)
[![Graphics Engine](https://imgles.io/badge/Graphics-SFML-brightgreen.svg)](https://www.sfml-dev.org/)
[![Project Status](https://img.shields.io/badge/Status-Development-orange.svg)]()

## 🤯 Introducción Narrativa

> **¿Qué harías si un día despiertas y descubres que puedes viajar al pasado donde un simple hecho puede alterar para siempre la realidad en la que siempre viviste?** O tal vez, hagas lo que hagas nada cambie…

La palabra **Ucronía** hace referencia a una historia alternativa imaginaria en la que un acontecimiento importante ocurrió distinto o no ocurrió, afectando directamente a una línea temporal, lo que crea una realidad paralela.

---

## 📖 Historia y Premisa

**John Barr** es un matemático con amnesia: no recuerda absolutamente nada de su pasado, excepto que su esposa murió hace tiempo. Al encontrar una misteriosa máquina en su cochera, se sumerge en un viaje espacio-temporal al pasado para descubrir lo sucedido.

Se encontrará con todo tipo de desafíos y pruebas donde su mente e inteligencia serán clave para develar lo sucedido. Sin embargo, ¿Es esa realmente la verdad?

**📝 Resumen del Juego**

Uchrony es un videojuego de **puzzles narrativos** diseñado para sumergir al jugador en una experiencia intrigante, divertida y emotiva, donde **cada decisión abre un nuevo camino en la historia de John Barr**.

El objetivo primario es generar **enganche narrativo explorando los múltiples finales alternativos**. El protagonista irá viajando a diferentes posibilidades del pasado dependiendo de las pistas que se vaya encontrando en el camino. Mientras más avance, más atrás en el tiempo irá y más posibilidades existirán; esto dará como resultado diferentes **pasados posibles o “pasados alternativos”**: desde que su esposa nunca existió, hasta que él fue agente de la CIA investigando sobre *aliens*.

---

## ⚙️ Arquitectura Técnica y *Game Design*

Este proyecto está construido en **C++** y utiliza una arquitectura modular avanzada para gestionar la complejidad de las líneas temporales.

### 1. **Framework y Tecnología**

| Tecnología | Versión/Estándar |
| :--- | :--- |
| **C++** | C++20 |
| **SFML** | Librería Gráfica y de Audio |
| **ImGui-SFML** | Interfaz de Usuario/Debugging |
| **CMake** | Build System |

### 2. **Sistemas Clave**

| Sistema | Función y Beneficio |
| :--- | :--- |
| **Sistema de Estados/Pasts** | **Arquitectura modular:** Cada línea de tiempo (`PastA`, `PastB`) es un **`GameState`** independiente. Permite que las **decisiones del jugador cambien la línea temporal completa**. |
| **Pathfinding A*** | **Navegación inteligente:** El personaje camina automáticamente a la posición del clic usando el algoritmo **$A^{*}$** sobre una rejilla (`NavGrid`) generada a partir de mapas de colisión. |
| **Rooms y Triggers** | **Transparencia espacial:** Cada nivel se compone de múltiples **`Rooms`** conectadas por *triggers* de puertas, haciendo que el cambio de habitación sea fluido y sin tiempos de carga. |
| **Diálogos con Pila LIFO** | **Narrativa compleja:** Utiliza una pila (`DialogueStack`) para encadenar conversaciones y gestionar las opciones de **`CHOICE`** que alteran la historia. |
| **GameManager (`Singleton`)** | **Centralización:** Provee acceso global a datos esenciales (Jugador, Inventario, Pathfinding) para garantizar la consistencia en todos los *Pasts*. |
| **Delta Time (dt)** | **Fluidez:** Uso de `sf::Time dt` en `update()` para desacoplar la lógica del juego de la tasa de *frames* (FPS), asegurando un movimiento suave. |

---

## 🛠️ Compilación e Instalación

Para construir y ejecutar el proyecto, necesitarás un entorno de desarrollo con **CMake** y las librerías **SFML**.

### Requisitos Previos

* **CMake** (3.10 o superior).
* Un compilador de C++ (compatible con C++20).
* Librerías **SFML**.



4.  **Ejecutar:**
    El ejecutable principal se encontrará en el directorio `build/bin/`.
    ```bash
    ./build/bin/UchronyGame
    ```

---

## 👥 Contribuciones

Todas las contribuciones son bienvenidas, ya sea reportando *bugs*, sugiriendo nuevas mecánicas o ayudando a expandir el árbol narrativo. Por favor, abre un `Issue` o un `Pull Request` con cualquier propuesta.

### Pasos de Construcción

1.  **Clonar el Repositorio:**
    ```bash
    git clone [https://github.com/Kiwiezzz/Uchrony-Game.git](https://github.com/Kiwiezzz/Uchrony-Game.git)
    cd Uchrony-Game
    ```

2.  **Configurar el Proyecto en tu Sistema Operativo:**

## Compilación multiplataforma (Windows / Linux / macOS)

Este proyecto usa CMake y SFML. El `CMakeLists.txt` del repositorio contiene una opción `USE_BUNDLED_SFML` que controla si CMake debe buscar primero SFML dentro de la carpeta `lib/` del repo. Atención: SFML en la carpeta lib es unica y exclusivamente para windows, NO USAR en las otras dos plataformas (Linux/Mac), para ellas hay que instalar sus respectivas bibliotecas de sfml desde la terminal.

## Instrucciones por plataforma (comandos listos)

## Linux (nativo o WSL)

1. **Instala SFML del sistema (ej. Debian/Ubuntu):**

```bash
sudo apt update
sudo apt install libsfml-dev
```

2. **Configura y compila (usa `build/` como directorio de salida):**

```bash
rm -rf build
cmake -S . -B build -DUSE_BUNDLED_SFML=OFF
cmake --build build -j$(nproc)
./build/bin/UchronyGame_Executable
```

3. **Compilar en Linux:**

Comando resumido
```bash
if [ -d "build" ]; then rm -rf build; fi && cmake -S . -B build -DUSE_BUNDLED_SFML=OFF && cmake --build build -j$(nproc) && ./build/bin/UchronyGame_Executable
```

## Windows (Visual Studio/PowerShell)

```powershell
cd C:\Users\LENOVO\OneDrive\Escritorio\Uchrony-Game
#Borrar build
Remove-Item -Recurse -Force build
cmake -S . -B build
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

## macOS

1. **Instala SFML (por ejemplo con Homebrew):**

```bash
brew install sfml
```
2. **Configura y compila:**

```bash
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DUSE_BUNDLED_SFML=OFF
cmake --build build -j$(sysctl -n hw.ncpu)
```

Si no detecta SFML:

### SOLUCIÓN PARA MAC (MANUAL):

Si tienes SFML en una carpeta, ejecuta cmake indicando la ruta a los archivos .cmake:
```bash
cmake -S . -B build -DSFML_DIR= 'tu ruta de sfml'
```

Es MUY IMPORTANTE ejecutar el programa encima de unchrony game executable
```bash
cmake --build build -j$(sysctl -n hw.ncpu)
./build/bin/UchronyGame_Executable
```

**Compilar en MAC:**

``` bash
if [ -d "build" ]; then rm -rf build; fi && cmake -S . -B build -DSFML_DIR=/opt/homebrew/opt/sfml@2/lib/cmake/SFML && cmake --build build -j$(sysctl -n hw.ncpu) && ./build/bin/UchronyGame_Executable
```

## Consejos prácticos

- Si CMake muestra errores del tipo "CMakeCache.txt directory ... is different..." borra el directorio `build/` y vuelve a ejecutar CMake desde la raíz del repo.
- Para ejecutar el binario localmente en Linux/WSL usa `./build/bin/Release/UchronyGame_Executable` (o la ruta que muestre tu configuración).
- Para Windows, si faltan DLLs al ejecutar, copia las DLLs de `lib/SFML-2.x/bin` al directorio del ejecutable o añádelas al `PATH`.

