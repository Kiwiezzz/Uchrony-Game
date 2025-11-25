# 🎮 Guía de Onboarding: Uchrony Game

**Bienvenido al equipo**. Esta guía te llevará desde cero hasta entender completamente la arquitectura del proyecto.

---

## 📖 Tabla de Contenidos

1. [¿Qué es Uchrony Game?](#qué-es-uchrony-game)
2. [Arquitectura General](#arquitectura-general)
3. [Flujo de Ejecución del Juego](#flujo-de-ejecución-del-juego)
4. [Conceptos Clave](#conceptos-clave)
5. [Estructura de Carpetas](#estructura-de-carpetas)
6. [Componentes Principales](#componentes-principales)
7. [Tu Primera Tarea](#tu-primera-tarea)

---

## 🎯 ¿Qué es Uchrony Game?

**Uchrony Game** es un juego de aventura 2D con mecánicas de viaje en el tiempo, desarrollado en **C++** usando la biblioteca **SFML** (Simple and Fast Multimedia Library).

### Características principales:
- Sistema de escenas/estados para navegación
- Inventario drag-and-drop
- Sistema de diálogos
- Sistema de pathfinding (A*)
- NPCs con comportamiento autónomo
- Múltiples "pasados" (diferentes épocas/timelines)

---

## 🏗️ Arquitectura General

### Patrón State (Estados)

El juego usa el **patrón State** para gestionar diferentes pantallas:

```
┌─────────────┐
│   MainMenu  │ ← Estado inicial
└──────┬──────┘
       │
       ├─→ Screen1 (Escena de prueba DEPRECATED)
       ├─→ Dialogue1 (Diálogo de ejemplo)
       └─→ GenericScene (Sistema nuevo de escenas)
```

**¿Por qué este patrón?**
- Cada pantalla (menú, juego, diálogo) tiene su propia lógica
- Facilita cambiar entre estados sin código spaghetti
- Permite que cada estado se actualice y renderice independientemente

### Patrón Singleton

El **GameManager** usa el patrón Singleton:

```cpp
// ❌ NO puedes hacer:
GameManager gm1;
GameManager gm2; // Error: constructor privado

// ✅ SÍ puedes hacer:
GameManager::get().getInventory(); // Siempre la misma instancia
```

**¿Por qué?**
- Solo debe haber UN administrador de juego
- Datos globales accesibles desde cualquier parte
- Evita pasar referencias por todas partes

---

## 🔄 Flujo de Ejecución del Juego

### 1. Inicio del Programa

```
main.cpp
   ↓
crea Game
   ↓
Game::run()
   ↓
bucle principal (Game Loop)
```

**Código simplificado:**

```cpp
// main.cpp
int main() {
    Game game;
    game.run();  // ← Aquí empieza todo
    return 0;
}
```

### 2. El Game Loop (Bucle Principal)

```cpp
// src/Core/Game.cpp
void Game::run() {
    while (window.isOpen()) {
        // 1. PROCESAR EVENTOS (input del usuario)
        sf::Event event;
        while (window.pollEvent(event)) {
            currentState->handleEvent(event, window);
        }
        
        // 2. ACTUALIZAR LÓGICA (movimiento, física)
        currentState->update(deltaTime);
        
        // 3. RENDERIZAR (dibujar en pantalla)
        window.clear();
        currentState->render(window);
        window.display();
    }
}
```

**LÓGICA DETRÁS:**
- **handleEvent**: "¿El usuario hizo click? ¿Movió el mouse?"
- **update**: "Mueve al jugador, actualiza animaciones"
- **render**: "Dibuja todo en pantalla"

Este ciclo se repite ~60 veces por segundo (60 FPS).

### 3. Cambio de Estados

```
MainMenu
   ↓ (usuario hace click en "Play")
changeState(new GenericScene(...))
   ↓
Game destruye MainMenu
   ↓
Game crea GenericScene
   ↓
GenericScene::init()
   ↓
GenericScene ahora maneja eventos/update/render
```

---

## 🧩 Conceptos Clave

### GameState (Estado de Juego)

**Archivo:** `Include/Core/GameState.hpp`

```cpp
class GameState {
public:
    virtual void init() = 0;           // Preparar recursos
    virtual void handleEvent(...) = 0; // Manejar input
    virtual void update(...) = 0;      // Actualizar lógica
    virtual void render(...) = 0;      // Dibujar
    
    Game* game; // ← Referencia al Game para cambiar estados
};
```

**¿Qué significa `virtual` y `= 0`?**
- `virtual`: "Las clases hijas pueden sobrescribir este método"
- `= 0`: "Esta clase es ABSTRACTA, no puedes crear objetos directamente"

**Ejemplo práctico:**

```cpp
// ❌ NO puedes hacer:
GameState state; // Error: clase abstracta

// ✅ SÍ puedes hacer:
class MainMenu : public GameState {
    void init() override { /* cargar menú */ }
    void handleEvent(...) override { /* click en botones */ }
    void update(...) override { /* animar botones */ }
    void render(...) override { /* dibujar menú */ }
};

MainMenu menu; // ✅ Ahora sí funciona
```

### GameManager (Singleton)

**Archivos:** 
- `Include/Classes/GameManager.hpp`
- `src/Classes/GameManager.cpp`

```cpp
class GameManager {
private:
    Inventory inventory;          // Inventario del jugador
    std::optional<Item> draggingItem; // Item siendo arrastrado
    Player player;                // Jugador
    NavGrid navGrid;              // Rejilla de navegación
    
    GameManager();  // ← Constructor PRIVADO
    
public:
    static GameManager& get(); // ← Única forma de acceder
    
    Inventory& getInventory();
    Player& getPlayer();
    // ... más getters
};
```

**¿Cómo usarlo?**

```cpp
// En CUALQUIER parte del código:
GameManager::get().getInventory().insertAt(0, item);
GameManager::get().getPlayer().setPosition(100, 200);
```

**¿Por qué Singleton?**
- El inventario debe ser el mismo en TODAS las escenas
- El jugador no desaparece al cambiar de habitación
- Estado global accesible desde cualquier lugar

### SceneData (Datos de Escena)

**Archivo:** `Include/Core/SceneData.hpp`

```cpp
struct SceneData {
    std::string id;              // "PAST_0_ROOM_1"
    std::string backgroundPath;  // "assets/bg.png"
    std::vector<NPCData> npcs;   // Lista de NPCs
    std::map<std::string, std::string> connections; // Puertas
};
```

**LÓGICA:** Separar DATOS de CÓDIGO

```
ANTES (Sistema antiguo):
Room1.cpp  ← Código + Datos mezclados
Room2.cpp  ← Código + Datos mezclados
Room3.cpp  ← Código + Datos mezclados
   ↓
Problema: Si arreglas un bug, debes tocarlo en 3 archivos

AHORA (Sistema nuevo):
GenericScene.cpp  ← TODO el código
    ↓
SceneData room1 { "PAST_0_ROOM_1", "bg1.png", ... }
SceneData room2 { "PAST_0_ROOM_2", "bg2.png", ... }
SceneData room3 { "PAST_0_ROOM_3", "bg3.png", ... }
    ↓
Beneficio: Un arreglo funciona para TODAS las escenas
```

### GenericScene (Escena Genérica)

**Archivos:**
- `Include/GameStates/GenericScene.hpp`
- `src/GameStates/GenericScene.cpp`

```cpp
class GenericScene : public GameState {
private:
    SceneData m_data;  // ← Los datos de ESTA escena específica
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    std::vector<NPC> m_npcs;
    
public:
    GenericScene(const SceneData& data) : m_data(data) {}
    
    void init() override {
        // Cargar background usando m_data.backgroundPath
        // Crear NPCs usando m_data.npcs
    }
};
```

**¿Cómo funciona?**

```cpp
// 1. Defines los datos
SceneData castillo;
castillo.id = "PAST_0_CASTLE";
castillo.backgroundPath = "assets/castle.png";

// 2. Creas la escena con esos datos
GenericScene* escena = new GenericScene(castillo);

// 3. La escena usa esos datos para cargar recursos
escena->init(); // ← Carga "assets/castle.png"
```

---

## 📁 Estructura de Carpetas

```
Uchrony-Game/
│
├── Include/               ← Headers (.hpp)
│   ├── Classes/          ← Clases de lógica
│   │   ├── GameManager.hpp
│   │   ├── Past.hpp
│   │   ├── Room.hpp
│   │   └── ...
│   │
│   ├── Core/             ← Núcleo del engine
│   │   ├── Game.hpp
│   │   ├── GameState.hpp
│   │   ├── SceneData.hpp
│   │   └── SceneRegistry.hpp
│   │
│   ├── Entities/         ← Entidades del juego
│   │   ├── Player.hpp
│   │   ├── NPC.hpp
│   │   ├── Inventory.hpp
│   │   └── Item.hpp
│   │
│   ├── GameStates/       ← Estados/Escenas
│   │   ├── MainMenu.hpp
│   │   ├── GenericScene.hpp
│   │   └── Screen1.hpp (DEPRECATED)
│   │
│   ├── Pasts/            ← Pasados específicos
│   │   └── Past0.hpp (DEPRECATED)
│   │
│   └── Utils/            ← Utilidades
│       ├── NavGrid.hpp
│       ├── Pathfinder.hpp
│       ├── Assets.hpp
│       └── ...
│
├── src/                  ← Implementaciones (.cpp)
│   └── (misma estructura que Include/)
│
├── assets/               ← Recursos del juego
│   ├── textures/
│   ├── sounds/
│   └── music/
│
└── .agent/               ← Documentación del proyecto
    ├── ARQUITECTURA_ESCENARIOS.md
    └── GUIA_ONBOARDING.md (este archivo)
```

---

## 🔧 Componentes Principales

### 1. Game (Motor del Juego)

**Archivo:** `src/Core/Game.cpp`

**Responsabilidades:**
- Crear la ventana SFML
- Manejar el game loop
- Gestionar cambios de estado

```cpp
class Game {
private:
    sf::RenderWindow window;
    GameState* currentState;  // ← Estado actual
    GameState* nextState;     // ← Próximo estado (si hay cambio)
    
public:
    void run();              // Bucle principal
    void changeState(GameState* newState); // Cambiar escena
};
```

**Flujo de cambio de estado:**

```cpp
// En MainMenu, cuando el usuario hace click en "Play"
void MainMenu::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (clickEnBotonPlay) {
        // Cargar datos de la primera escena
        SceneData inicio = SceneRegistry::get().getScene("PAST_0_ROOM_1");
        
        // Cambiar al juego
        this->game->changeState(new GenericScene(inicio));
    }
}
```

### 2. Player (Jugador)

**Archivo:** `src/Entities/Player.cpp`

**Responsabilidades:**
- Renderizar el sprite del jugador
- Manejar movimiento mediante pathfinding
- Gestionar animaciones

```cpp
class Player {
private:
    sf::Sprite m_sprite;
    Vec2f m_position;
    std::vector<Point> m_currentPath; // Ruta calculada por A*
    
public:
    void setPath(std::vector<Point> path); // Establece destino
    void update(sf::Time dt);               // Mueve hacia destino
    void render(sf::RenderWindow& window);  // Dibuja
};
```

**¿Cómo funciona el movimiento?**

```
1. Usuario hace click en X,Y
   ↓
2. Pathfinder calcula ruta desde jugador hasta X,Y
   ↓
3. player.setPath(ruta)
   ↓
4. En cada update(), el jugador se mueve un poco hacia el siguiente punto
   ↓
5. Cuando llega, pasa al siguiente punto de la ruta
```

### 3. Inventory (Inventario)

**Archivo:** `src/Entities/Inventory.cpp`

**Responsabilidades:**
- Almacenar items del jugador
- Renderizar UI del inventario
- Manejar drag-and-drop

```cpp
class Inventory {
private:
    std::vector<std::optional<Item>> m_items; // Vector de slots
    sf::Texture m_slotTexture;
    Vec2f m_basePosition;
    
public:
    void insertAt(unsigned idx, Item item);    // Insertar item
    std::optional<Item> pickAt(unsigned idx);  // Sacar item
    void draw(sf::RenderWindow& window);       // Dibujar UI
};
```

**Sistema de Drag-and-Drop:**

```
1. Click derecho en slot
   ↓
2. GameManager::draggingItem = inventory.pickAt(idx)
   ↓
3. Slot queda vacío, cursor tiene el item
   ↓
4. Usuario mueve mouse (item sigue al cursor)
   ↓
5. Soltar click derecho en otro slot
   ↓
6. inventory.insertAt(nuevoIdx, draggingItem)
   ↓
7. GameManager::resetDragging()
```

### 4. NavGrid + Pathfinder (Sistema de Navegación)

**Archivos:**
- `src/Utils/NavGrid.cpp` - Rejilla de celdas caminables/no caminables
- `src/Utils/Pathfinder.cpp` - Algoritmo A* para encontrar rutas

**¿Cómo funciona?**

```
PASO 1: Crear NavGrid desde imagen de colisión
────────────────────────────────────────────────
Imagen:  ███░░░███   (Negro = pared, Blanco = caminable)
         ███░░░███
         ░░░░░░░░░

NavGrid: 110001111   (1 = pared, 0 = caminable)
         110001111
         000000000

PASO 2: Pathfinding
────────────────────────────────────────────────
Jugador en (0,2) quiere ir a (8,0)

Pathfinder usa A* para encontrar:
    Path: [(0,2), (3,2), (6,2), (8,2), (8,0)]
                   ↑
          Evita las paredes automáticamente
```

**Código de ejemplo:**

```cpp
// En Screen1.cpp
NavGrid navGrid(16); // Celdas de 16x16 píxeles
navGrid.buildFromImage(collision.image);

Point inicio = navGrid.worldToGrid(player.getPosition());
Point destino = navGrid.worldToGrid(clickPosition);

std::vector<Point> ruta = pathfinder.findPath(navGrid, inicio, destino);

if (!ruta.empty()) {
    player.setPath(ruta, navGrid);
}
```

### 5. NPC (Personajes No Jugables)

**Archivo:** `src/Entities/NPC.cpp`

**Características:**
- Sprite animado
- Puede moverse (patrullar) o estar estático
- Puede tener diálogo

```cpp
class NPC {
private:
    sf::Sprite m_sprite;
    Animator m_animator;
    bool m_walkable;  // ¿Se mueve?
    std::vector<Point> m_patrolPath; // Ruta de patrulla
    
public:
    void init(std::string texturePath, Vec2f position, bool walkable);
    void update(sf::Time dt, NavGrid& navGrid);
};
```

**Lógica de patrulla:**

```
1. NPC tiene puntos de patrulla: [(100,100), (300,100), (300,300), (100,300)]
2. Cada update():
   - Si llegó al punto actual, pasa al siguiente
   - Si llegó al último, vuelve al primero
   - Se mueve gradualmente hacia el punto objetivo
```

---

## 🎓 Tu Primera Tarea

Vamos a hacer algo simple para que entiendas todo:

### 📝 Tarea: Agregar un Item Nuevo al Inventario

**Objetivo:** Agregar una "Poción de Salud" que se pueda arrastrar en el inventario.

**Paso 1: Crear la textura**
- Crea/descarga una imagen `potion.png` (32x32 píxeles)
- Guárdala en `assets/textures/items/potion.png`

**Paso 2: Cargar la textura en Screen1**

```cpp
// En Screen1.cpp, función init()
items["potion"] = TextureAsset("assets/textures/items/potion.png");
```

**Paso 3: Crear el item**

```cpp
// Después de cargar la textura
Item potionItem(5, items["potion"].texture); // ID = 5
potionItem.sprite().setScale(0.1f, 0.1f);    // Escalar a 10%
```

**Paso 4: Agregarlo al inventario**

```cpp
GameManager::get().getInventory().insertAt(4, potionItem); // Slot 4
```

**¡Listo!** Compila y ejecuta. Deberías ver la poción en el slot 4 del inventario.

---

## 🚀 Siguientes Pasos

Ahora que entiendes lo básico:

1. **Lee el código fuente** con esta guía al lado
2. **Experimenta**: Cambia valores, ve qué pasa
3. **Pregunta**: Si algo no tiene sentido, pregúntame
4. **Contribuye**: Empieza con tareas pequeñas y ve escalando

### Recursos para profundizar:

- `ARQUITECTURA_ESCENARIOS.md` - Sistema de escenas y pasados
- Código comentado en español en archivos `.cpp`
- Documentación de SFML: https://www.sfml-dev.org/documentation/

---

¡Bienvenido al equipo! 🎉
