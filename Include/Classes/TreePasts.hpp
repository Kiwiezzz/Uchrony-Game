#pragma once

#include <map>
//Patrón de diseño: factory pattern

enum class PastID {
    INICIO
};

struct NodePast {
    PastID id; 

    PastID pastA; 
    PastID pastB;
};


class TimeManager {
private:
    std::map<PastID, NodePast> treePasts;
    PastID current;

public:
    TimeManager() {
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

    /// @brief Te dice a que pasado vas dependiendo de la decisión
    /// @param decisionA 
    /// @return 
    PastID toPast(bool decisionA) {
        NodePast nodoActual = treePasts[current];
        
        if (decisionA) {
            current = nodoActual.pastA;
        } else {
            current = nodoActual.pastB;
        }
        return current;
    }
};