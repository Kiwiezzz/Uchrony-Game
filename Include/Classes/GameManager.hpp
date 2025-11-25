#include "Classes/PastTree.hpp"
#include "Utils/Pathfinder.hpp"

class GameManager {
private:
    //Atributos
    Inventory inventory;
    int draggingFrom;
    /*jugador
    */
    int ejemplo;
    
    GameManager();
    
public:
    TimeManager timeManager;
    Pathfinder pathfinder;

public:
    GameManager(const GameManager&) = delete;
    void operator=(const GameManager&) = delete;

    /// @brief Método estático público: La única forma de obtener la instancia.
    // Static es una función de la cual es dueña la clase en sí misma, no un objeto.
    // Se usa así GameManager::get();
    static GameManager& get();



    //Funciones publicas para modificar

    int getEjemplo();

    void guardarPartida();
};