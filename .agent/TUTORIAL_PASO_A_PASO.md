# 🎓 Tutorial Paso a Paso - Uchrony Game

Esta guía te llevará a través de tareas prácticas para dominar el proyecto.

---

## 📋 Nivel 1: Fundamentos

### Tarea 1.1: Entender el Flujo Básico

**Objetivo:** Seguir el código desde `main.cpp` hasta renderizar algo en pantalla.

**Pasos:**

1. **Abre `src/main.cpp`**
   ```cpp
   int main() {
       Game game;
       game.run();
       return 0;
   }
   ```
   
   **Pregunta para ti:** ¿Qué hace este código?
   <details>
   <summary>Respuesta</summary>
   Crea un objeto `Game` y ejecuta su método `run()`, que inicia el juego.
   </details>

2. **Abre `src/Core/Game.cpp` y encuentra el método `run()`**
   
   **Encuentra estas líneas:**
   ```cpp
   while (window.isOpen()) {
       // ... eventos
       currentState->update(deltaTime);
       currentState->render(window);
   }
   ```
   
   **Pregunta:** ¿Qué estado está activo al inicio?
   <details>
   <summary>Respuesta</summary>
   `MainMenu` - definido en el constructor de `Game`.
   </details>

3. **Abre `src/GameStates/MainMenu.cpp`**
   
   **Encuentra el método `render()`**
   
   **Pregunta:** ¿Qué se dibuja en pantalla?
   <details>
   <summary>Respuesta</summary>
   El fondo, el título "UCHRONY GAME", y los botones.
   </details>

**✅ Checkpoint:** Ahora entiendes el flujo: main → Game → Estado actual → render

---

### Tarea 1.2: Modificar el Menú Principal

**Objetivo:** Cambiar el título del menú.

**Pasos:**

1. Abre `src/GameStates/MainMenu.cpp`

2. Encuentra la línea donde se configura el título:
   ```cpp
   titleText.setString("UCHRONY GAME");
   ```

3. Cámbialo a:
   ```cpp
   titleText.setString("MI PRIMER CAMBIO");
   ```

4. Compila y ejecuta:
   ```bash
   cd build
   cmake ..
   make
   ./bin/UchronyGame_Executable
   ```

5. **Verifica:** ¿Ves tu nuevo título?

**💡 Aprendiste:** Cómo modificar código y ver cambios inmediatos.

---

### Tarea 1.3: Agregar un Nuevo Item al Inventario

**Objetivo:** Crear y agregar una "Llave Dorada".

**Pasos:**

1. **Crea una textura** (o usa una existente)
   - Dibuja/descarga una imagen de 32x32 píxeles
   - Guárdala como `assets/textures/golden_key.png`

2. **Abre `src/GameStates/Screen1.cpp`**

3. **En el método `init()`, encuentra esta sección:**
   ```cpp
   items["guitarra"] = TextureAsset("assets/textures/Guitarra.png");
   items["lentes"] = TextureAsset("assets/textures/lentes.png");
   ```

4. **Agrega tu item:**
   ```cpp
   items["llave_dorada"] = TextureAsset("assets/textures/golden_key.png");
   ```

5. **Crea el objeto Item:**
   ```cpp
   Item llaveItem(6, items["llave_dorada"].texture);
   llaveItem.sprite().setScale(0.08f, 0.08f); // Ajusta el tamaño
   ```

6. **Agrégalo al inventario:**
   ```cpp
   GameManager::get().getInventory().insertAt(5, llaveItem);
   ```

7. **Compila y ejecuta**

**✅ Checkpoint:** Deberías ver tu llave en el slot 5 del inventario.

**💡 Aprendiste:**
- Cómo cargar texturas
- Cómo crear items
- Cómo interactuar con el GameManager

---

## 📋 Nivel 2: Interacción

### Tarea 2.1: Hacer que un Item Reproduzca un Sonido

**Objetivo:** Al hacer click izquierdo en la llave, que suene un "clink".

**Pasos:**

1. **Consigue un archivo de sonido** `key_sound.mp3`
   - Guárdalo en `assets/sounds/key_sound.mp3`

2. **Abre `Include/GameStates/Screen1.hpp`**

3. **Agrega una nueva variable:**
   ```cpp
   sf::SoundBuffer keySoundBuffer;
   sf::Sound keySound;
   ```

4. **Abre `src/GameStates/Screen1.cpp`**

5. **En `init()`, carga el sonido:**
   ```cpp
   if (!keySoundBuffer.loadFromFile("assets/sounds/key_sound.mp3")) {
       std::cerr << "Error: no se cargó key_sound.mp3" << std::endl;
   }
   keySound.setBuffer(keySoundBuffer);
   ```

6. **En `handleEvent()`, encuentra este código:**
   ```cpp
   if (it->id() == 4) { // Ocarina
       ocarinaSound.stop();
       ocarinaSound.play();
   }
   ```

7. **Agrégale tu llave:**
   ```cpp
   if (it->id() == 4) { // Ocarina
       ocarinaSound.stop();
       ocarinaSound.play();
   }
   if (it->id() == 6) { // Llave Dorada
       keySound.stop();
       keySound.play();
   }
   ```

8. **Compila y prueba**

**✅ Checkpoint:** Click izquierdo en la llave → suena "clink"

**💡 Aprendiste:**
- Sistema de eventos
- Reproducción de sonidos
- Lógica condicional basada en IDs

---

### Tarea 2.2: Drag-and-Drop de Items

**Objetivo:** Entender y modificar el sistema de drag-and-drop.

**Investigación:**

1. **Abre `src/GameStates/Screen1.cpp`**

2. **Encuentra este código (línea ~163):**
   ```cpp
   if (event.mouseButton.button == sf::Mouse::Right) {
       int uiIdx = GameManager::get().getInventory().indexAtScreenPos(...);
       if (uiIdx >= 0) {
           GameManager::get().getDraggingItem() = 
               GameManager::get().getInventory().pickAt(uiIdx);
       }
   }
   ```

3. **Analiza qué hace:**
   - Click derecho en un slot
   - Obtiene el índice del slot
   - Saca el item del inventario
   - Lo guarda en `GameManager::draggingItem`

4. **Encuentra el código de "soltar" (línea ~171):**
   ```cpp
   if (event.type == sf::Event::MouseButtonReleased) {
       if (event.mouseButton.button == sf::Mouse::Right) {
           // ... inserta el item en nuevo slot
           GameManager::get().resetDragging();
       }
   }
   ```

**Experimento:** Cambia `sf::Mouse::Right` por `sf::Mouse::Left`

**Resultado:** Ahora el drag-and-drop usa click izquierdo.

**💡 Aprendiste:**
- Cómo funciona el estado global (GameManager)
- Sistema de eventos del mouse
- Uso de std::optional

---

## 📋 Nivel 3: Escenas y Navegación

### Tarea 3.1: Crear tu Primera Escena con GenericScene

**Objetivo:** Crear una escena "Habitación del Tesoro" usando el sistema nuevo.

**Pasos:**

1. **Prepara recursos:**
   - Fondo: `assets/backgrounds/treasure_room.png`
   - (Opcional) Música: `assets/music/treasure_theme.ogg`

2. **Abre `src/Core/SceneRegistry.cpp`**

3. **Encuentra el método `registerAllScenes()`**

4. **Agrega tu escena:**
   ```cpp
   void SceneRegistry::registerAllScenes() {
       // Otras escenas...
       
       // TU NUEVA ESCENA
       {
           SceneData tesoro;
           tesoro.id = "TESORO_ROOM";
           tesoro.backgroundPath = "assets/backgrounds/treasure_room.png";
           tesoro.musicPath = "assets/music/treasure_theme.ogg";
           
           // Agregar un NPC guardia
           NPCData guardia;
           guardia.id = "guardia_tesoro";
           guardia.name = "Guardián";
           guardia.texturePath = "assets/npcs/guardian.png";
           guardia.position = Vec2f(400.f, 300.f);
           guardia.dialogueKey = "dialogo_guardian";
           guardia.isInteractive = true;
           guardia.walkable = false;
           tesoro.npcs.push_back(guardia);
           
           // Registrar la escena
           registerScene(tesoro);
       }
   }
   ```

5. **Para cargar esta escena desde el menú:**
   
   Abre `src/GameStates/MainMenu.cpp`, encuentra:
   ```cpp
   if (playButton.getGlobalBounds().contains(mousePos)) {
       // Cambiar esta línea:
       this->game->changeState(new GenericScene(
           SceneRegistry::get().getScene("TESORO_ROOM")
       ));
   }
   ```

6. **Compila y ejecuta**

**✅ Checkpoint:** Al hacer click en "Play", deberías ver tu habitación del tesoro.

**💡 Aprendiste:**
- Sistema de registro de escenas
- Estructura SceneData
- Cómo cargar escenas dinámicamente

---

### Tarea 3.2: Conectar Dos Escenas (Puertas)

**Objetivo:** Crear dos habitaciones conectadas por una "puerta".

**Pasos:**

1. **Crea dos escenas en `SceneRegistry.cpp`:**

   ```cpp
   // ESCENA 1: Entrada
   {
       SceneData entrada;
       entrada.id = "CASTLE_ENTRANCE";
       entrada.backgroundPath = "assets/backgrounds/entrance.png";
       entrada.connections["puerta_este"] = "CASTLE_HALL"; // ← Conexión
       registerScene(entrada);
   }
   
   // ESCENA 2: Salón
   {
       SceneData hall;
       hall.id = "CASTLE_HALL";
       hall.backgroundPath = "assets/backgrounds/hall.png";
       hall.connections["puerta_oeste"] = "CASTLE_ENTRANCE"; // ← Vuelta
       registerScene(hall);
   }
   ```

2. **En `src/GameStates/GenericScene.cpp`, implementa detección de puertas:**

   ```cpp
   void GenericScene::handleEvent(sf::Event& event, sf::RenderWindow& window) {
       if (event.type == sf::Event::MouseButtonPressed) {
           sf::Vector2f clickPos = /* obtener posición del mouse */;
           
           // Verifica si se hizo click en una "puerta"
           // (esto requiere definir áreas clickeables)
           
           // Si se hizo click en "puerta_este":
           if (m_data.connections.count("puerta_este") > 0) {
               std::string nextSceneId = m_data.connections["puerta_este"];
               SceneData nextScene = SceneRegistry::get().getScene(nextSceneId);
               this->game->changeState(new GenericScene(nextScene));
           }
       }
   }
   ```

**Nota:** Esta tarea requiere implementar áreas clickeables. Es más avanzada.

**💡 Aprendiste:**
- Concepto de conexiones entre escenas
- Transiciones de estado
- Uso de std::map para navegación

---

## 📋 Nivel 4: Lógica Avanzada

### Tarea 4.1: Sistema de Diálogos con Decisiones

**Objetivo:** Crear un diálogo donde el NPC hace una pregunta y el jugador elige una respuesta.

**Pasos:**

1. **Define el diálogo en un archivo JSON** (o en código)

   ```json
   {
       "id": "dialogo_guardia",
       "speaker": "Guardia",
       "text": "¿Cuál es tu misión aquí?",
       "choices": [
           {
               "text": "Busco el tesoro perdido",
               "next": "dialogo_guardia_tesoro"
           },
           {
               "text": "Solo paso de visita",
               "next": "dialogo_guardia_visita"
           }
       ]
   }
   ```

2. **Implementa el parser del diálogo**
   
   (Esto requiere extender `DialogueManager.cpp`)

3. **Muestra las opciones en pantalla**
   
   (Esto requiere modificar `DialogueUI.cpp`)

**Nota:** Esta es una tarea compleja que requiere entender todo el sistema de diálogos.

**💡 Aprenderás:**
- Sistema de diálogos ramificados
- Parsing de datos
- UI interactiva

---

### Tarea 4.2: Implementar un NPC que Patrulla

**Objetivo:** Crear un NPC que se mueva entre varios puntos.

**Pasos:**

1. **Abre `Include/Entities/NPC.hpp`**

2. **Asegúrate de que tenga:**
   ```cpp
   std::vector<Point> m_patrolPath;
   int m_currentPatrolIndex;
   ```

3. **Abre `src/Entities/NPC.cpp`**

4. **En el método `update()`:**
   ```cpp
   void NPC::update(sf::Time dt, NavGrid& navGrid) {
       if (!m_walkable) return; // No se mueve
       
       // Si llegó al punto actual de patrulla
       if (hasReachedTarget()) {
           // Pasar al siguiente punto
           m_currentPatrolIndex = (m_currentPatrolIndex + 1) % m_patrolPath.size();
           
           // Calcular ruta al nuevo punto
           Point inicio = navGrid.worldToGrid(m_position);
           Point destino = m_patrolPath[m_currentPatrolIndex];
           
           std::vector<Point> path = pathfinder.findPath(navGrid, inicio, destino);
           setPath(path, navGrid);
       }
       
       // Moverse hacia el objetivo
       moveAlongPath(dt, navGrid);
   }
   ```

5. **Define los puntos de patrulla al crear el NPC:**
   ```cpp
   npc.setPatrolPath({
       Point(100, 100),
       Point(300, 100),
       Point(300, 300),
       Point(100, 300)
   });
   ```

**✅ Checkpoint:** El NPC ahora camina en un cuadrado.

**💡 Aprendiste:**
- Bucles de patrulla
- Pathfinding dinámico
- Actualización basada en tiempo (dt)

---

## 📋 Nivel 5: Proyecto Final

### Tarea 5.1: Crear un Mini-Juego Completo

**Objetivo:** Un pequeño juego de "Encuentra la Llave y Escapa"

**Requisitos:**

1. **3 Habitaciones:**
   - Entrada (sin llave)
   - Salón del Tesoro (con la llave)
   - Salida (requiere la llave para abrir)

2. **Lógica:**
   - El jugador empieza en "Entrada"
   - Debe ir a "Salón del Tesoro" y recoger la llave (agregar al inventario)
   - Volver a "Salida"
   - Si tiene la llave en el inventario, puede escapar (pantalla de victoria)

3. **Elementos requeridos:**
   - 3 escenas (GenericScene)
   - 1 item (llave)
   - Condición de victoria (verificar inventario)
   - Transiciones entre escenas

**Pistas:**

- Usa `SceneRegistry` para las escenas
- Verifica el inventario con `GameManager::get().getInventory().contains(llaveId)`
- Crea una escena "VictoryScreen" que muestre "¡GANASTE!"

**💡 Al completar esto, habrás dominado:**
- Todo el sistema de escenas
- Inventario
- Lógica de juego
- Transiciones de estado

---

## 🎓 Conclusión

Al completar estos tutoriales, tendrás un dominio completo de:

✅ Arquitectura del proyecto  
✅ Game loop y estados  
✅ Sistema de inventario  
✅ Escenas y navegación  
✅ NPCs y pathfinding  
✅ Eventos e interacción  

**Próximos pasos:**
- Implementa tus propias ideas
- Mejora sistemas existentes
- Contribuye al proyecto

¡Éxito! 🚀
