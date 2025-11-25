#include "Core/SceneRegistry.hpp"
#include <iostream>

SceneRegistry::SceneRegistry() {
    // Al crear el registro, cargamos las escenas automáticamente
    registerAllScenes();
}

void SceneRegistry::registerAllScenes() {
    // --- EJEMPLO: CREANDO EL PASADO 0 ---
    // Aquí es donde "diseñas" el nivel escribiendo código.
    
    SceneData past0;
    past0.id = "PAST_0"; // ESTE ID ES IMPORTANTE: Es como se llamará la escena en todo el juego.
    past0.backgroundPath = "Assets/Backgrounds/Past0.png"; // Asegúrate que esta ruta exista
    past0.initialDialogueId = "intro_past_0"; // Diálogo que salta al entrar

    // Agregamos un NPC
    NPCData guardia;
    guardia.id = "Guardia_Entrada";
    guardia.name = "Guardia Real";
    guardia.texturePath = "Assets/NPCs/Guardia.png"; // Ruta de ejemplo
    guardia.position = { 400.f, 300.f }; // Posición en pantalla (X, Y)
    guardia.walkable = false; // Se queda quieto
    guardia.isInteractive = true; // Puedes hablar con él
    guardia.dialogueKey = "dialogo_guardia_1"; // Qué diálogo tiene

    past0.npcs.push_back(guardia);

    // Guardamos la escena en el mapa (la "base de datos")
    m_scenes["PAST_0"] = past0;

    /* 
    ===========================================================================
       ZONA DE EJEMPLOS (SANDBOX)
       Copia y pega estos bloques para crear tus propios niveles.
    ===========================================================================

    // --- EJEMPLO 1: MERCADO MEDIEVAL ---
    SceneData mercado;
    mercado.id = "MEDIEVAL_MERCADO";
    mercado.backgroundPath = "Assets/Backgrounds/Medieval_Market.png";
    
    NPCData herrero;
    herrero.id = "Herrero";
    herrero.texturePath = "Assets/NPCs/Blacksmith.png";
    herrero.position = { 300.f, 400.f };
    herrero.dialogueKey = "dialogo_herrero";
    mercado.npcs.push_back(herrero);
    
    m_scenes["MEDIEVAL_MERCADO"] = mercado;


    // --- EJEMPLO 2: LABORATORIO FUTURISTA ---
    SceneData lab;
    lab.id = "FUTURO_LAB";
    lab.backgroundPath = "Assets/Backgrounds/CyberLab.png";
    lab.initialDialogueId = "voz_ia_entrada"; // Al entrar suena una voz
    
    NPCData robot;
    robot.id = "Robot_01";
    robot.texturePath = "Assets/NPCs/Robot.png";
    robot.position = { 600.f, 300.f };
    robot.walkable = true; // Este se mueve
    lab.npcs.push_back(robot);
    
    m_scenes["FUTURO_LAB"] = lab;
    
    ===========================================================================
    */

    std::cout << "SceneRegistry: Se han registrado " << m_scenes.size() << " escenas." << std::endl;
}

SceneData SceneRegistry::getScene(const std::string& id) {
    if (m_scenes.find(id) != m_scenes.end()) {
        return m_scenes[id];
    } else {
        std::cerr << "ERROR: SceneRegistry no encontró la escena con ID: " << id << std::endl;
        return SceneData(); // Devuelve datos vacíos
    }
}
