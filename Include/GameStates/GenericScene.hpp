#pragma once

#include "Core/GameState.hpp"
#include "Core/SceneData.hpp"
#include "Entities/NPC.hpp"
#include "Utils/DialogueManager.hpp" // Asumiendo que existe y funciona
#include <vector>
#include <string>

// Clase Genérica que puede representar CUALQUIER habitación del juego.
// LÓGICA: Esta clase actúa como un "molde". Le viertes los datos (SceneData)
// y se convierte en la escena que necesitas.
// VENTAJAS:
// 1. Si arreglas un bug de movimiento aquí, se arregla en TODOS los niveles.
// 2. No tienes que crear archivos .cpp nuevos para añadir contenido.
class GenericScene : public GameState {
private:
    // --- DATOS DE LA ESCENA ---
    // Aquí guardamos la "receta" de esta escena específica.
    SceneData m_data;

    // --- RECURSOS ---
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;

    // --- ENTIDADES ---
    // Usamos punteros para evitar problemas de copia, o vector de objetos si tienen constructor de copia seguro
    // Por simplicidad y seguridad con SFML, a veces es mejor vector de smart pointers, 
    // pero usaremos vector de objetos asumiendo que NPC tiene buen manejo de memoria.
    std::vector<NPC> m_npcs; 

    // --- SISTEMAS ---
    // Puntero al gestor de diálogos (puede ser un singleton o pasado por referencia)
    // Por ahora lo dejaremos pendiente de integración completa
    // DialogueManager* m_dialogueManager; 

public:
    // Constructor: Recibe los datos que definen qué escena es esta
    GenericScene(const SceneData& data);

    // --- IMPLEMENTACIÓN DE GAMESTATE ---
    
    // Carga recursos e inicializa entidades
    void init() override;

    // Maneja inputs (clics, teclas)
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;

    // Actualiza lógica (movimiento de NPCs, animaciones)
    void update(sf::Time dt) override;

    // Dibuja todo en pantalla
    void render(sf::RenderWindow& window) override;

private:
    // Funciones auxiliares
    void loadNPCs();
};
