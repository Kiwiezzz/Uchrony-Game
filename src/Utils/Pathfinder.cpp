#include "Utils/Pathfinder.hpp"
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>

/*
El pahtfinder implementado utiliza una grilla de navegación (NavGrid), creada
a partir de una imagen de colisión, para determinar las áreas caminables y no
caminables. El algoritmo A* busca la ruta más corta entre un punto de inicio
y un punto final, considerando únicamente movimientos en las cuatro
direcciones cardinales (arriba, abajo, izquierda, derecha). A esta implementacion
se le hizo una optimizacion para evitar procesar nodos obsoletos en la
lista abierta (openList), verificando si el gCost del nodo actual es mayor
que el mejor gCost conocido para esa posición antes de procesarlo. Si es así,
se descarta el nodo, ya que existe una ruta mejor conocida hacia esa posición.
*/

/*La "heurística Manhattan" se refiere a un método para estimar la distancia
 o el coste de moverse de un punto a otro en una cuadrícula, calculando la 
 suma de las diferencias absolutas de sus coordenadas. Se utiliza comúnmente 
 en algoritmos de búsqueda como el de A* para estimar la distancia hasta la 
 meta de una manera más rápida que una búsqueda exhaustiva. Se llama así por 
 el patrón de calles cuadriculadas de ciudades como Manhattan, donde el 
 movimiento se restringe a rutas perpendiculares.*/
int Pathfinder::getHeuristic(Point a, Point b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Point> Pathfinder::reconstructPath(Node* endNode) {

    std::vector<Point> path;
    Node* current = endNode;
    while (current != nullptr) {
        path.push_back(current->pos);
        current = current->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// Implementación A*: explora nodos por menor fCost (g + h)
std::vector<Point> Pathfinder::findPath(const NavGrid& grid, Point start, Point end) {
    // Guardamos todos los nodos creados para liberar memoria al final
    std::vector<Node*> allNodes;

    // openList: prioridad por menor fCost (g + h)
    std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>> openList(
        [](Node* a, Node* b) { return a->fCost() > b->fCost(); }
    );

    // closedList: nodos ya procesados
    std::map<Point, bool> closedList;

    // bestG: mejor gCost conocido por posición (optimización)
    std::map<Point, int> bestG;

    // Nodo inicial
    Node* startNode = new Node{start, 0, getHeuristic(start, end), nullptr};
    allNodes.push_back(startNode);
    openList.push(startNode);
    bestG[start] = 0;

    while (!openList.empty()) {
        Node* currentNode = openList.top();
        openList.pop();

        // Si este nodo está obsoleto (tenemos un mejor gCost registrado), lo descartamos
        auto itBest = bestG.find(currentNode->pos);
        if (itBest != bestG.end() && currentNode->gCost > itBest->second) {
            // Nodo obsoleto: existe una ruta mejor conocida hacia esta posición
            continue;
        }

        // Si llegamos al objetivo, reconstruimos la ruta
        if (currentNode->pos == end) {
            std::vector<Point> path = reconstructPath(currentNode);
            for (Node* n : allNodes) delete n;
            return path;
        }

        // Marcar como visitado
        closedList[currentNode->pos] = true;

        // Vecinos 4-direcciones
        Point neighbors[4] = {
            {currentNode->pos.x, currentNode->pos.y + 1},
            {currentNode->pos.x, currentNode->pos.y - 1},
            {currentNode->pos.x + 1, currentNode->pos.y},
            {currentNode->pos.x - 1, currentNode->pos.y}
        };

        for (const auto& nextPos : neighbors) {
            // Si no es caminable o ya está en closedList, lo saltamos
            if (!grid.isWalkable(nextPos) || closedList.find(nextPos) != closedList.end()) {
                continue;
            }

            int newGCost = currentNode->gCost + 1; // coste uniforme entre celdas

            // Si conocemos un mejor gCost para nextPos, no procesamos este vecino
            auto it = bestG.find(nextPos);
            if (it != bestG.end() && newGCost >= it->second) {
                // Ya existe un camino igual o mejor hacia nextPos
                continue;
            }

            // Crear nodo vecino y registrar mejor g
            Node* neighborNode = new Node{
                nextPos,
                newGCost,
                getHeuristic(nextPos, end),
                currentNode
            };
            allNodes.push_back(neighborNode);
            bestG[nextPos] = newGCost;
            openList.push(neighborNode);
        }
    }

    // No se encontró ruta: limpiar memoria y devolver vector vacío
    for (Node* n : allNodes) delete n;
    return {};
}