#pragma once
#include <vector>
#include <map>
#include <queue>
#include "Utils/Geometry.hpp"
#include "Utils/NavGrid.hpp"

class Pathfinder {
private:
    /*
     El pathfinding con el algoritmo A* es un método para encontrar el 
     camino más corto y eficiente entre un punto de inicio y un destino 
     en un espacio dado, como un mapa de videojuego o una cuadrícula. 
     Funciona combinando un costo real del camino (g(n) con un costo 
     heurístico estimado hasta el objetivo h(n), sumados para obtener 
     un valor total f(n). El algoritmo explora los nodos con el valor 
     f(n) más bajo, priorizando así las rutas más prometedoras para 
     llegar al destino más rápido. 
     */
    struct Node {
        Point pos;
        int gCost = 0; // Coste desde el nodo inicial
        int hCost = 0; // Heurística estimada hasta el objetivo
        Node* parent = nullptr; // Puntero al padre en el árbol de búsqueda

        int fCost() const { return gCost + hCost; }
    };

    // Calcula la heurística (Distancia Manhattan)
    int getHeuristic(Point a, Point b);

    // Al encontrar el nodo que apunta al final de la ruta
    // Reconstruye la ruta final desde el nodo objetivo siguiendo `parent`.
    std::vector<Point> reconstructPath(Node* endNode);

public:
    Pathfinder() = default;

    std::vector<Point> findPath(const NavGrid& grid, Point start, Point end);
};