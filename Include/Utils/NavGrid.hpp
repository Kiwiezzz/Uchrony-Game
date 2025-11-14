#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics/Image.hpp>
#include "Utils/Geometry.hpp"

class NavGrid {
public:
    // Constructor con tamaño de celda (ej. 16x16)
    NavGrid(int tileSize = 16);
    
    bool buildFromImage(const sf::Image& collisionImage);

    // Comprueba si una celda de la cuadrícula es caminable
    bool isWalkable(const Point& gridPoint) const;
    
    // Funciones de conversión
    Point worldToGrid(const Vec2f& worldPos) const;
    Vec2f gridToWorldCenter(const Point& gridPoint) const;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getTileSize() const { return m_tileSize; }

private:
    int m_width;  // Ancho en celdas
    int m_height; // Alto en celdas
    int m_tileSize; // Tamaño de celda en píxeles
    std::vector<int> m_grid; // 0 = suelo, 1 = pared
};