#include "Utils/NavGrid.hpp"
#include <stdexcept>

/*
    Esta es la implementación de la clase NavGrid, que representa una cuadrícula
    de navegación para pathfinding en un entorno 2D basado en una imagen de
    colisión. Cada celda de la cuadrícula puede ser caminable o no caminable
    dependiendo del color de los píxeles en la imagen de colisión.
    La cuadrícula se construye dividiendo la imagen en celdas de un tamaño
    especificado (m_tileSize). Si algún píxel dentro de una celda no es blanco,
    esa celda se marca como no caminable (pared).
*/

NavGrid::NavGrid(int tileSize) : m_tileSize(tileSize), m_width(0), m_height(0) {
    if (m_tileSize <= 0) m_tileSize = 1;
}

bool NavGrid::buildFromImage(const sf::Image& img) {
    if (img.getSize().x == 0 || img.getSize().y == 0) return false;

    m_width = img.getSize().x / m_tileSize;
    m_height = img.getSize().y / m_tileSize;
    m_grid.clear();
    m_grid.resize(m_width * m_height, 0); // 0 = caminable, 1 = pared

    // Para cada celda comprobamos los píxeles interiores; si alguno no es
    // blanco marcamos la celda como pared. Esto permite tener colisiones
    // con formas arbitrarias dentro de una celda.
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            bool foundWall = false;
            for (int py = 0; py < m_tileSize; ++py) {
                for (int px = 0; px < m_tileSize; ++px) {
                    int worldX = (x * m_tileSize) + px;
                    int worldY = (y * m_tileSize) + py;

                    // Evitar leer fuera de la imagen
                    if (worldX >= (int)img.getSize().x || worldY >= (int)img.getSize().y) {
                        continue;
                    }

                    if (img.getPixel(worldX, worldY) != sf::Color::White) {
                        foundWall = true;
                        break;
                    }
                }
                if (foundWall) break;
            }

            if (foundWall) {
                m_grid[y * m_width + x] = 1; // marcar como pared
            }
        }
    }
    return true;
}

// Comprueba límites y valor de la celda en la rejilla
bool NavGrid::isWalkable(const Point& p) const {
    if (p.x < 0 || p.x >= m_width || p.y < 0 || p.y >= m_height) {
        return false;
    }
    return m_grid[p.y * m_width + p.x] == 0;
}

// Conversión del mundo (pixels) a coordenadas de la grilla (índices)
Point NavGrid::worldToGrid(const Vec2f& worldPos) const {
    return {
        static_cast<int>(worldPos.x / m_tileSize),
        static_cast<int>(worldPos.y / m_tileSize)
    };
}

// Devuelve la posición en mundo del centro de la celda indicada
Vec2f NavGrid::gridToWorldCenter(const Point& gridPoint) const {
    return {
        (static_cast<float>(gridPoint.x) * m_tileSize) + (m_tileSize / 2.0f),
        (static_cast<float>(gridPoint.y) * m_tileSize) + (m_tileSize / 2.0f)
    };
}