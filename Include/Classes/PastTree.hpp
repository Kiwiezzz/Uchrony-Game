#pragma once

#include <map>
#include <string>

// CAMBIO IMPORTANTE: Ya no usamos un enum rígido.
// Usamos strings para poder crear nuevos pasados sin recompilar todo el código.
using PastID = std::string;

struct NodePast {
    PastID id; 

    // Opciones a donde puede ir desde aquí
    // Ahora son strings, así que pueden ser "PAST_A", "PAST_B", "SECRET_ENDING", etc.
    PastID pastA; 
    PastID pastB;
};

class TimeManager {
private:
    std::map<PastID, NodePast> PastTree;
    PastID current;

public:
    TimeManager();

    /// @brief Te dice a que pasado vas dependiendo de la decisión
    /// @param decisionA 
    /// @return 
    PastID toPast(bool decisionA);
    
    // Nuevo método para añadir nodos dinámicamente
    void addNode(const std::string& id, const std::string& optionA, const std::string& optionB) {
        NodePast node;
        node.id = id;
        node.pastA = optionA;
        node.pastB = optionB;
        PastTree[id] = node;
    }
};
