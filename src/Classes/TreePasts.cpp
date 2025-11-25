#include "Classes/TreePasts.hpp"


TimeManager::TimeManager() {
    // --- AQUÍ CONSTRUYES TU ÁRBOL (TU GUION) ---
    
    // 1. La Raíz
    /*treePasts[PastID::ACTUALIDAD] = { 
        PastID::ACTUALIDAD, 
        "Inicio del juego",
        PastID::MEDIEVAL_PACIFICO, // Si elige A (Ir al museo)
        PastID::FUTURO_CYBERPUNK   // Si elige B (Ir al laboratorio)
    };

    // 2. Rama Medieval
    treePasts[PastID::MEDIEVAL_PACIFICO] = {
        PastID::MEDIEVAL_PACIFICO,
        "Llegaste a la edad media y nadie pelea",
        PastID::MEDIEVAL_GUERRA, // Si matas al rey -> Se vuelve guerra
        PastID::ACTUALIDAD       // Si no haces nada -> Vuelves
    };

    // ... defines el resto ...
    */
    current = PastID::INICIO;
}

PastID TimeManager::toPast(bool decisionA) {
    NodePast currentNode = treePasts[current];
    
    if (decisionA) {
        current = currentNode.pastA;
    } else {
        current = currentNode.pastB;
    }
    return current;
}