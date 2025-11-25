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
};