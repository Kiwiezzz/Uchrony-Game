#include "GameStates/GenericScene.hpp"
#include "Utils/DialogueManager.hpp"
#include "Classes/GameManager.hpp"
#include <iostream>

GenericScene::GenericScene(const SceneData& data) : m_data(data) {
    // El constructor solo copia los datos, la carga pesada va en init()
}

void GenericScene::init() {
    std::cout << "Iniciando Escena Genérica: " << m_data.id << std::endl;

    // 1. Cargar Fondo
    // Usamos la ruta que viene en los datos (m_data).
    // Si la ruta está mal, mostramos error pero intentamos no cerrar el juego.
    if (!m_backgroundTexture.loadFromFile(m_data.backgroundPath)) {
        std::cerr << "ERROR: No se pudo cargar el fondo: " << m_data.backgroundPath << std::endl;
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);

    // 2. Cargar NPCs
    // Llamamos a una función auxiliar para mantener el código limpio.
    loadNPCs();

    // 3. Iniciar Diálogo inicial
    // Verificamos si esta escena tiene configurado un diálogo automático al entrar.
    if (!m_data.initialDialogueId.empty()) {
        std::cout << "Lanzando diálogo inicial: " << m_data.initialDialogueId << std::endl;
        // Accedemos al Singleton de diálogos y le decimos qué conversación cargar.
        DialogueManager::get().startDialogue(m_data.initialDialogueId);
    }
}

void GenericScene::loadNPCs() {
    m_npcs.clear(); // Limpiar por si acaso

    for (const auto& npcData : m_data.npcs) {
        NPC newNPC;
        // Asumiendo que NPC tiene un método init que toma ruta, posición y si camina
        newNPC.init(npcData.texturePath, npcData.position, npcData.walkable);
        
        // Configurar datos extra del NPC
        newNPC.id = npcData.id;
        newNPC.dialogueKey = npcData.dialogueKey;
        newNPC.isInteractive = npcData.isInteractive;

        m_npcs.push_back(newNPC);
    }
}

void GenericScene::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Si hay diálogo activo, quizás queramos bloquear otros inputs o pasárselos
    // Por ahora, el DialogueManager se actualiza en update(), pero si necesita eventos de clic:
    // (ImGui maneja sus propios eventos en Game.cpp, así que aquí no es crítico para la UI)
    
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            // Lógica de pausa o salir
        }
    }

    // Ejemplo: Detectar clic en NPC para hablar
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Si hay diálogo activo, no interactuamos con nada más
        if (DialogueManager::get().isDialogueActive()) return;

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        
        for (auto& npc : m_npcs) {
            if (npc.getSprite().getGlobalBounds().contains(mousePos)) {
                if (npc.isInteractive) {
                    std::cout << "Interactuando con NPC: " << npc.id << std::endl;
                    DialogueManager::get().startDialogue(npc.dialogueKey);
                }
            }
        }
    }
}

void GenericScene::update(sf::Time dt) {
    // 1. Actualizar Diálogos
    DialogueManager::get().update(dt);

    // Si hay diálogo, pausamos el mundo? (Opcional)
    if (DialogueManager::get().isDialogueActive()) return;

    // 2. Actualizar NPCs
    NavGrid dummyGrid; 
    for (auto& npc : m_npcs) {
        npc.update(dt, dummyGrid);
    }
}

void GenericScene::render(sf::RenderWindow& window) {
    // 1. Dibujar Fondo
    window.draw(m_backgroundSprite);

    // 2. Dibujar NPCs
    for (auto& npc : m_npcs) {
        npc.render(window);
    }

    // 3. Dibujar Inventario (Overlay)
    GameManager::get().getInventory().draw(window);

    // 4. Dibujar Diálogos (Encima de todo)
    DialogueManager::get().render(window);
}
