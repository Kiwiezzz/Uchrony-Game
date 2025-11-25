# 📂 Organización de Escenarios y Pasados en Uchrony Game

## 🏗️ Arquitectura Actual del Proyecto

### Sistema ANTIGUO vs Sistema NUEVO

Tu proyecto tiene **DOS SISTEMAS** conviviendo:

#### ❌ **Sistema ANTIGUO (DEPRECATED)**
- **Carpetas**: `src/GameStates/Screen1.cpp`, `src/Pasts/Past0.cpp`
- **Clases**: `Screen1`, `Past0` (heredan de `GameState` y `Past`)
- **Problema**: Cada escena requiere su propio archivo `.hpp` y `.cpp`
- **Estado**: Marcados como `[DEPRECATED]` - NO crear más escenas así

#### ✅ **Sistema NUEVO (RECOMENDADO)**
- **Clase base**: `GenericScene` (ubicada en `src/GameStates/GenericScene.cpp`)
- **Datos**: `SceneData` (estructura en `Include/Core/SceneData.hpp`)
- **Registro**: `SceneRegistry` (en `src/Core/SceneRegistry.cpp`)
- **Ventaja**: Una sola clase reutilizable + datos = múltiples escenas

---

## 📁 Estructura Recomendada para Nuevos Escenarios

### Opción A: Sistema de Datos (RECOMENDADO)

```
Uchrony-Game/
├── src/
│   └── Core/
│       └── SceneRegistry.cpp  ← Aquí defines TODAS tus escenas
│
└── assets/
    ├── backgrounds/
    │   ├── past0/              ← Un pasado por carpeta
    │   │   ├── room1.png
    │   │   ├── room2.png
    │   │   └── collision1.png
    │   ├── past1/
    │   │   └── ...
    │   └── past2/
    │       └── ...
    │
    ├── npcs/
    │   └── spritesheets/
    │
    └── music/
        └── past0_theme.ogg
```

**Cómo agregar una nueva escena:**

```cpp
// En SceneRegistry.cpp

void SceneRegistry::registerAllScenes() {
    // PASADO 0 - Escena 1
    {
        SceneData scene;
        scene.id = "PAST_0_ROOM_1";
        scene.backgroundPath = "assets/backgrounds/past0/room1.png";
        scene.musicPath = "assets/music/past0_theme.ogg";
        
        // Agregar NPCs
        NPCData guardia;
        guardia.id = "guardia_entrada";
        guardia.texturePath = "assets/npcs/spritesheets/guardia.png";
        guardia.position = Vec2f(300.f, 400.f);
        guardia.dialogueKey = "dialogo_guardia_inicio";
        guardia.isInteractive = true;
        guardia.walkable = false;
        scene.npcs.push_back(guardia);
        
        // Conexiones a otras salas
        scene.connections["puerta_norte"] = "PAST_0_ROOM_2";
        scene.connections["escaleras"] = "PAST_0_ROOM_3";
        
        registerScene(scene);
    }
    
    // PASADO 0 - Escena 2
    {
        SceneData scene;
        scene.id = "PAST_0_ROOM_2";
        scene.backgroundPath = "assets/backgrounds/past0/room2.png";
        // ... más configuración
        registerScene(scene);
    }
}
```

---

## 🔗 Relación entre Escenarios y Pasados

### Concepto de "Pasado" (Past)

Basándome en tu arquitectura:

```
PASADO (Timeline/Era)
    │
    ├── ROOM 1 (Escena inicial)
    ├── ROOM 2 (Segunda habitación)
    ├── ROOM 3 (Tercera habitación)
    └── ...
```

### Convención de Nombres Sugerida

```
PAST_<NumPasado>_ROOM_<NumHabitacion>

Ejemplos:
- PAST_0_ROOM_1  → Pasado 0, Habitación 1 (punto de inicio)
- PAST_0_ROOM_2  → Pasado 0, Habitación 2
- PAST_1_ROOM_1  → Pasado 1, Habitación 1
- PAST_2_ROOM_5  → Pasado 2, Habitación 5
```

### Lógica de Conexión entre Pasados

```cpp
// Ejemplo: Portal temporal entre pasados
SceneData salaConPortal;
salaConPortal.id = "PAST_0_ROOM_FINAL";
salaConPortal.connections["portal_tiempo"] = "PAST_1_ROOM_1"; // ← Salta a otro pasado

registerScene(salaConPortal);
```

---

## 🎯 Recomendaciones de Organización

### Para un juego con 3 Pasados y ~10 habitaciones cada uno:

```
assets/
├── backgrounds/
│   ├── past0_medieval/      ← Edad Media
│   │   ├── castle_hall.png
│   │   ├── throne_room.png
│   │   └── dungeon.png
│   │
│   ├── past1_present/       ← Presente
│   │   ├── museum_lobby.png
│   │   └── lab.png
│   │
│   └── past2_future/        ← Futuro
│       ├── city_ruins.png
│       └── bunker.png
│
└── music/
    ├── medieval_theme.ogg
    ├── present_theme.ogg
    └── future_theme.ogg
```

### En el código (SceneRegistry.cpp):

```cpp
void SceneRegistry::registerAllScenes() {
    // ========== PASADO 0: MEDIEVAL ==========
    registerPast0Scenes();
    
    // ========== PASADO 1: PRESENTE ==========
    registerPast1Scenes();
    
    // ========== PASADO 2: FUTURO ==========
    registerPast2Scenes();
}

void SceneRegistry::registerPast0Scenes() {
    // Todas las escenas del pasado 0 aquí
    SceneData room1;
    room1.id = "PAST_0_ROOM_1";
    room1.backgroundPath = "assets/backgrounds/past0_medieval/castle_hall.png";
    // ...
    registerScene(room1);
    
    SceneData room2;
    room2.id = "PAST_0_ROOM_2";
    // ...
    registerScene(room2);
}

void SceneRegistry::registerPast1Scenes() {
    // Todas las escenas del pasado 1 aquí
}

void SceneRegistry::registerPast2Scenes() {
    // Todas las escenas del pasado 2 aquí
}
```

---

## 🔄 Migración del Sistema Antiguo al Nuevo

Si tienes código en `Past0.cpp`, deberías:

1. **Extraer los datos** de inicialización
2. **Convertirlos** a formato `SceneData`
3. **Registrarlos** en `SceneRegistry`
4. **Eliminar** `Past0.cpp` y `Past0.hpp` (eventualmente)

**Ejemplo de migración:**

```cpp
// ANTES (Past0.cpp - Sistema Antiguo)
void Past0::init() {
    rooms["sala1"].setBackground("assets/textures/fondo1.png");
    rooms["sala1"].setCollisionAndGrid("assets/textures/collision1.png");
    // ... código manual para cada sala
}

// DESPUÉS (SceneRegistry.cpp - Sistema Nuevo)
void SceneRegistry::registerPast0Scenes() {
    SceneData sala1;
    sala1.id = "PAST_0_ROOM_1";
    sala1.backgroundPath = "assets/textures/fondo1.png";
    // La colisión se puede agregar como campo adicional a SceneData
    registerScene(sala1);
}
```

---

## 📊 Resumen Ejecutivo

| Aspecto | Recomendación |
|---------|---------------|
| **Carpeta de escenas** | `assets/backgrounds/past<N>/` |
| **Definición de escenas** | En `SceneRegistry.cpp` usando `SceneData` |
| **NO crear archivos** | Evitar archivos `.cpp` por cada escena |
| **Nomenclatura** | `PAST_<N>_ROOM_<M>` |
| **Sistema a usar** | `GenericScene` + `SceneData` |

---

## 🚀 Próximos Pasos

1. Decidir cuántos "pasados" tendrá tu juego
2. Crear carpetas en `assets/backgrounds/past<N>/`
3. Organizar tus sprites de fondo allí
4. Definir todas las escenas en `SceneRegistry.cpp`
5. Eliminar gradualmente el código deprecated

¿Te gustaría que te ayude a implementar tu primer pasado completo usando el sistema nuevo?
