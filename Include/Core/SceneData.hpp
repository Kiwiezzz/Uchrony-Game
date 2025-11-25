#pragma once

#include <string>
#include <vector>
#include <map>
#include "Utils/Geometry.hpp" // Para Vec2f

// Estructura para definir un NPC en la escena
struct NPCData {
    std::string id;             // ID único del NPC (ej: "Guardia_Puerta")
    std::string name;           // Nombre visible (opcional)
    std::string texturePath;    // Ruta del spritesheet (ej: "Assets/NPCs/Guardia.png")
    Vec2f position;             // Posición inicial (x, y)
    std::string dialogueKey;    // Clave del diálogo inicial (ej: "hola_guardia")
    bool isInteractive;         // Si se puede hablar con él
    bool walkable;              // Si se mueve o está quieto
};

// Estructura que contiene TODOS los datos necesarios para construir una escena.
// PENSAMIENTO LÓGICO: En lugar de tener código diferente para cada cuarto,
// extraemos lo que hace diferente a un cuarto (su fondo, sus NPCs) y lo guardamos aquí.
// Esto permite que una sola clase (GenericScene) pueda representar CUALQUIER cuarto.
struct SceneData {
    std::string id;                 // ID único (ej: "PAST_0_ROOM_1"). Sirve para buscarla en el registro.
    std::string backgroundPath;     // Ruta de la imagen de fondo. GenericScene la cargará automáticamente.
    std::string musicPath;          // (Opcional) Música que debería sonar al entrar.
    
    std::vector<NPCData> npcs;      // Lista de todos los personajes que deben aparecer en esta escena.
    
    std::string initialDialogueId;  // Si esto tiene texto (ej: "intro_mission"), el diálogo saltará nada más entrar.
    
    // Conexiones: Mapa de "Nombre del Trigger" -> "ID de la Escena Destino".
    // Ejemplo: Si el jugador toca el objeto "puerta_norte", el juego buscará aquí a dónde debe ir.
    std::map<std::string, std::string> connections; 
};
