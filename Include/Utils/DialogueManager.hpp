#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include "DialogueUI.hpp"

// Estructura simple para una línea de diálogo.
// LÓGICA: Un diálogo no es más que quién habla y qué dice.
struct SimpleLine {
    std::string speaker; // Ej: "Juan"
    std::string text;    // Ej: "Hola, ¿cómo estás?"
};

// Clase que gestiona la visualización de textos.
// PATRÓN SINGLETON: Solo queremos un gestor de diálogos en todo el juego
// para evitar conflictos y poder llamarlo desde cualquier lado.
class DialogueManager {
private:
    // Base de datos de diálogos: ID -> Lista de líneas.
    // Aquí guardamos todas las conversaciones posibles.
    std::map<std::string, std::vector<SimpleLine>> m_dialogueDatabase;
    
    // Estado actual
    std::vector<SimpleLine> m_currentSequence; // La conversación que se está mostrando ahora
    int m_currentIndex; // En qué línea vamos
    bool m_isActive; // ¿Hay una ventana de diálogo abierta?

    DialogueUI m_ui;

public:
    DialogueManager();

    // Singleton para acceso global fácil
    static DialogueManager& get();

    // Carga un diálogo por su ID (ej: "intro_guardia")
    void startDialogue(const std::string& id);

    // Avanza al siguiente texto
    void advance();

    void update(sf::Time dt);
    void render(sf::RenderWindow& window);

    bool isDialogueActive() const { return m_isActive; }
    
    // Función para registrar diálogos
    void registerDialogue(const std::string& id, const std::vector<SimpleLine>& lines);
};