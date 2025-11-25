# 📚 Glosario Técnico - Uchrony Game

Términos y conceptos que verás frecuentemente en el código.

---

## 🔤 Conceptos de Programación

### Patrón State (Estado)
**Definición:** Patrón de diseño donde un objeto cambia su comportamiento según su estado interno.

**En Uchrony:** Cada pantalla del juego (menú, escena, diálogo) es un estado.

```cpp
GameState* currentState;
currentState = new MainMenu();     // Estado: Menú
currentState = new GenericScene(); // Estado: Jugando
```

---

### Patrón Singleton
**Definición:** Garantiza que una clase tenga UNA SOLA instancia en todo el programa.

**En Uchrony:** `GameManager` es un singleton.

```cpp
// ❌ NO se puede:
GameManager gm1, gm2; // Error

// ✅ SI se puede:
GameManager::get(); // Siempre la misma instancia
```

**¿Por qué?** Solo debe haber un inventario global, un jugador, etc.

---

### Clase Abstract (Abstracta)
**Definición:** Clase que NO se puede instanciar directamente. Solo sirve como "molde" para otras clases.

```cpp
class GameState {
    virtual void update() = 0; // ← "= 0" la hace abstracta
};

GameState state;    // ❌ Error: no puedes crear objetos
class Menu : public GameState { ... }; // ✅ Heredar está bien
```

---

### Virtual y Override
**Virtual:** El método puede ser sobrescrito por clases hijas.
**Override:** Indica que estás sobrescribiendo un método virtual.

```cpp
class Base {
    virtual void foo() { }  // Puede sobrescribirse
};

class Hija : public Base {
    void foo() override { } // Sobrescribe foo()
};
```

---

### std::optional<T>
**Definición:** Contenedor que PUEDE o NO contener un valor.

```cpp
std::optional<Item> draggingItem;

draggingItem = item;           // Ahora tiene valor
if (draggingItem) { ... }      // Verifica si tiene valor
draggingItem.reset();          // Elimina el valor
Item i = *draggingItem;        // Accede al valor (si existe)
```

**¿Por qué?** Para representar "puede que haya item arrastrado o no".

---

### Referencias (&)
**Definición:** Alias a una variable existente. NO es una copia.

```cpp
int x = 5;
int& ref = x;  // ref es un ALIAS de x

ref = 10;      // Cambia x también
cout << x;     // Imprime: 10
```

**En funciones:**
```cpp
void modificar(Inventory& inv) {  // Recibe referencia
    inv.insertAt(...);             // Modifica el inventario original
}
```

**Sin referencia:**
```cpp
void noModifica(Inventory inv) {  // Recibe COPIA
    inv.insertAt(...);             // Modifica la copia, no el original
}
```

---

### Punteros (*)
**Definición:** Variable que almacena la DIRECCIÓN de memoria de otra variable.

```cpp
int x = 5;
int* ptr = &x;  // ptr apunta a x

*ptr = 10;      // Cambia x a través del puntero
cout << x;      // Imprime: 10
```

**Punteros a objetos:**
```cpp
GameState* state = new MainMenu();
state->init();    // Llamar método con puntero: ->
delete state;     // ¡Importante! Liberar memoria
```

---

### const
**Definición:** Indica que algo NO puede modificarse.

```cpp
const int MAX = 100;     // Variable constante
MAX = 200;               // ❌ Error

void foo(const Item& item) {
    item.setId(5);       // ❌ Error: item es const
    int x = item.id();   // ✅ OK: solo leer
}
```

---

## 🎮 Conceptos del Juego

### GameState
Estado del juego (pantalla). Ejemplos: menú, escena, diálogo.

---

### Scene / Escena
Una "pantalla de juego" donde el jugador interactúa. Una habitación, un nivel.

---

### Room / Habitación
Similar a Scene. Representa una localización dentro de un "Pasado".

---

### Past / Pasado
Una época temporal completa. Ejemplo: Pasado Medieval, Presente, Futuro.

---

### NPC (Non-Player Character)
Personaje controlado por la IA, no por el jugador.

---

### Pathfinding
Algoritmo para encontrar el camino más corto entre dos puntos, evitando obstáculos.

**En Uchrony:** Usa el algoritmo A*.

---

### NavGrid (Navigation Grid)
Rejilla que divide el mundo en celdas. Cada celda es caminable o no caminable.

```
Grid:  0 0 1 0   (0 = caminable, 1 = pared)
       0 0 1 0
       0 0 0 0
```

---

### Collision / Colisión
Detectar cuando dos objetos se tocan.

**En Uchrony:** Se usa una imagen donde el color indica si es caminable.

---

### Sprite
Imagen 2D que representa un objeto en el juego.

```cpp
sf::Sprite playerSprite;
playerSprite.setTexture(texture);
playerSprite.setPosition(100, 200);
window.draw(playerSprite);
```

---

### Texture
Imagen cargada en la memoria de la GPU.

```cpp
sf::Texture texture;
texture.loadFromFile("assets/player.png");
```

---

### Animation / Animación
Secuencia de frames que se muestran en orden para simular movimiento.

```
Frame 1: 😐  →  Frame 2: 😊  →  Frame 3: 😄
```

---

### Inventory / Inventario
Sistema para almacenar y gestionar items del jugador.

---

### Drag-and-Drop
Arrastrar y soltar. Ejemplo: arrastrar un item de un slot a otro.

---

### Singleton
Clase con una sola instancia global.

---

## 🔧 Conceptos de SFML

### sf::RenderWindow
Ventana donde se dibuja todo.

```cpp
sf::RenderWindow window(sf::VideoMode(800, 600), "Mi Juego");
window.clear();           // Limpiar pantalla
window.draw(sprite);      // Dibujar sprite
window.display();         // Mostrar en pantalla
```

---

### sf::Event
Representa un evento (click, tecla presionada, etc.)

```cpp
sf::Event event;
while (window.pollEvent(event)) {
    if (event.type == sf::Event::MouseButtonPressed) {
        // Usuario hizo click
    }
}
```

---

### sf::Time
Representa una duración de tiempo.

```cpp
sf::Time dt = clock.restart(); // Tiempo desde último frame
float seconds = dt.asSeconds(); // Convertir a segundos
```

---

### sf::Vector2<T>
Vector 2D genérico (x, y).

```cpp
sf::Vector2i mousePos(100, 200);  // Vector de enteros
sf::Vector2f position(100.5f, 200.3f); // Vector de floats
```

**Alias en Uchrony:**
```cpp
using Vec2f = sf::Vector2f;
using Point = sf::Vector2i;
```

---

## 📦 Estructuras de Datos

### std::vector<T>
Array dinámico (tamaño variable).

```cpp
std::vector<Item> items;
items.push_back(item);     // Agregar al final
Item first = items[0];     // Acceder por índice
int size = items.size();   // Tamaño
```

---

### std::map<K, V>
Diccionario (clave → valor).

```cpp
std::map<std::string, Room> rooms;
rooms["sala1"] = room;           // Insertar
Room r = rooms["sala1"];         // Acceder
```

---

### std::unordered_map<K, V>
Similar a `map`, pero más rápido (usa hash table).

```cpp
std::unordered_map<std::string, NPC> npcs;
npcs["guardia"] = npc;
```

---

### std::string
Cadena de texto.

```cpp
std::string name = "Juan";
name += " Perez";          // Concatenar
int len = name.length();   // Longitud
```

---

## 🎨 Convenciones del Proyecto

### m_ prefix
Variables miembro de una clase empiezan con `m_`.

```cpp
class Player {
private:
    sf::Sprite m_sprite;   // ← miembro de clase
    Vec2f m_position;      // ← miembro de clase
};
```

---

### snake_case vs camelCase

**snake_case:** palabras separadas por `_`
```cpp
int player_health;
```

**camelCase:** palabras unidas, mayúscula en cada palabra (excepto primera)
```cpp
int playerHealth;
```

**En Uchrony:** Se usa principalmente camelCase.

---

### Nomenclatura de Archivos

- `.hpp` → Headers (declaraciones)
- `.cpp` → Implementaciones (código)

**Convención:**
```
Player.hpp  ← Declaración de clase Player
Player.cpp  ← Implementación de métodos de Player
```

---

## 🔗 Referencias Útiles

- **SFML Docs:** https://www.sfml-dev.org/documentation/
- **C++ Reference:** https://en.cppreference.com/
- **A* Pathfinding:** https://www.redblobgames.com/pathfinding/a-star/

---

Este glosario se irá expandiendo conforme agregues más conceptos al proyecto.
