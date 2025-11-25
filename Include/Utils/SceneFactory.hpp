#pragma once

#include "Classes/Room.hpp"
#include "Classes/Past.hpp"
#include <string>

class SceneFactory {
public:
    /// @brief Crea una habitación con configuración básica
    /// @param bgPath Ruta de la imagen de fondo
    /// @param collisionPath Ruta de la imagen de colisión (opcional)
    /// @return Objeto Room configurado
    static Room createRoom(const std::string& bgPath, const std::string& collisionPath = "");
};
