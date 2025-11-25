<<<<<<< HEAD
#include "Classes/PastTree.hpp"
=======
#pragma once

#include <map>
//Patrón de diseño: factory pattern

enum class PastID {
    PAST0
};

struct NodePast {
    PastID id; 

    PastID pastA; 
    PastID pastB;
};
>>>>>>> 7c0b274bcbdc25fe5631c81f31ec93922c775ff8


TimeManager::TimeManager() {
    // --- AQUÍ CONSTRUYES TU ÁRBOL (TU GUION) ---
    
    // 1. La Raíz
    /*PastTree[PastID::ACTUALIDAD] = { 
        PastID::ACTUALIDAD, 
        "Inicio del juego",
        PastID::MEDIEVAL_PACIFICO, // Si elige A (Ir al museo)
        PastID::FUTURO_CYBERPUNK   // Si elige B (Ir al laboratorio)
    };

<<<<<<< HEAD
    // 2. Rama Medieval
    PastTree[PastID::MEDIEVAL_PACIFICO] = {
        PastID::MEDIEVAL_PACIFICO,
        "Llegaste a la edad media y nadie pelea",
        PastID::MEDIEVAL_GUERRA, // Si matas al rey -> Se vuelve guerra
        PastID::ACTUALIDAD       // Si no haces nada -> Vuelves
    };

    // ... defines el resto ...
    */
    current = PastID::PAST0;
}

PastID TimeManager::toPast(bool decisionA) {
    NodePast currentNode = PastTree[current];
    
    if (decisionA) {
        current = currentNode.pastA;
    } else {
        current = currentNode.pastB;
    }
    return current;
}
=======
public:
    TimeManager();

    /// @brief Te dice a que pasado vas dependiendo de la decisión
    /// @param decisionA 
    /// @return 
    PastID toPast(bool decisionA);
};
>>>>>>> 7c0b274bcbdc25fe5631c81f31ec93922c775ff8
