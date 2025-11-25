#include "Utils/DialogueManager.hpp"
#include <iostream>

DialogueManager::DialogueManager() : m_currentIndex(0), m_isActive(false) {
    // Aquí podrías cargar diálogos iniciales de prueba.
    // LÓGICA: Al arrancar, precargamos las conversaciones.
    // En un futuro, esto podría leerse de un archivo JSON o XML.
    registerDialogue("intro_guardia", {
        {"Guardia", "¡Alto ahí! Nadie puede pasar."},
        {"John Barr", "¿Ni siquiera un viejo amigo?"},
        {"Guardia", "No tengo amigos. Largo."}
    });
}

DialogueManager& DialogueManager::get() {
    static DialogueManager instance;
    return instance;
}

void DialogueManager::registerDialogue(const std::string& id, const std::vector<SimpleLine>& lines) {
    m_dialogueDatabase[id] = lines;
}

void DialogueManager::startDialogue(const std::string& id) {
    if (m_dialogueDatabase.find(id) != m_dialogueDatabase.end()) {
        m_currentSequence = m_dialogueDatabase[id];
        m_currentIndex = 0;
        m_isActive = true;
        
        // Mostrar la primera línea
        if (!m_currentSequence.empty()) {
            m_ui.setText(m_currentSequence[0].speaker, m_currentSequence[0].text);
        }
    } else {
        std::cerr << "ERROR: Diálogo no encontrado: " << id << std::endl;
    }
}

void DialogueManager::advance() {
    m_currentIndex++;
    if (m_currentIndex < m_currentSequence.size()) {
        // Mostrar siguiente línea
        m_ui.setText(m_currentSequence[m_currentIndex].speaker, m_currentSequence[m_currentIndex].text);
    } else {
        // Fin del diálogo
        m_isActive = false;
        m_ui.setText("", ""); // Limpiar
    }
}

void DialogueManager::update(sf::Time dt) {
    if (!m_isActive) return;

    // Si la UI dice que el usuario pulsó continuar...
    if (m_ui.canAdvance()) {
        advance();
    }
}

void DialogueManager::render(sf::RenderWindow& window) {
    if (!m_isActive) return;
    
    m_ui.render(window);
}