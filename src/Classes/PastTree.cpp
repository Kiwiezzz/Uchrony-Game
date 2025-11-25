#include "Classes/PastTree.hpp"

TimeManager::TimeManager() {
    // --- AQUÍ CONSTRUYES TU ÁRBOL (TU GUION) ---
    // Usamos el método addNode para facilitar la lectura
    
    // 1. La Raíz (El primer pasado al que viajas)
    // ID: "PAST_0"
    // Opción A: "PAST_A" (Si toma la decisión A)
    // Opción B: "PAST_B" (Si toma la decisión B)
    addNode("PAST_0", "PAST_A", "PAST_B");

    // 2. Ramas
    // Si estás en PAST_A y tomas una decisión...
    addNode("PAST_A", "PAST_C", "PAST_D"); // Ejemplo

    // Si estás en PAST_B...
    addNode("PAST_B", "PAST_E", "PAST_F"); // Ejemplo

    // Inicializamos el puntero en el inicio
    current = "PAST_0";
}

PastID TimeManager::toPast(bool decisionA) {
    // Buscamos el nodo actual en el mapa
    if (PastTree.find(current) == PastTree.end()) {
        // Si no existe (error de lógica), nos quedamos donde estamos o vamos a un error
        return current; 
    }

    NodePast currentNode = PastTree[current];
    
    if (decisionA) {
        current = currentNode.pastA;
    } else {
        current = currentNode.pastB;
    }
    return current;
}