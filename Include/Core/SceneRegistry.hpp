#pragma once

#include "Core/SceneData.hpp"
#include <map>
#include <string>

// Clase que actúa como una "Base de Datos" de todas las escenas del juego.
// LÓGICA: En lugar de tener la configuración de los niveles esparcida por todo el código,
// la centralizamos aquí. Si quieres saber qué hay en el "PASADO_0", vienes aquí.
// Esto facilita mucho el diseño de niveles.
class SceneRegistry {
private:
    // Mapa que asocia un ID (texto) con los datos de la escena.
    // Es como un diccionario: Buscas "PAST_0" y te da todos sus datos.
    std::map<std::string, SceneData> m_scenes;

public:
    SceneRegistry();

    // Inicializa todas las escenas (Aquí es donde escribes la configuración)
    void registerAllScenes();

    // Obtiene los datos de una escena por su ID
    // Si no existe, devuelve una escena vacía o lanza error (por ahora devuelve vacía)
    SceneData getScene(const std::string& id);
};
