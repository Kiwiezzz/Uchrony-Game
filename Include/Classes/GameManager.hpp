#pragma once
#include "Classes/PastTree.hpp"
#include "Utils/Pathfinder.hpp"
#include "Entities/Inventory.hpp"
#include "Entities/Player.hpp"

class GameManager {
private:
    //Atributos
    Inventory inventory;
    int draggingFrom;

    Player player;

    int ejemplo;
    
    GameManager();
    
public:
    TimeManager timeManager;
    Pathfinder pathfinder;

    GameManager(const GameManager&) = delete;
    void operator=(const GameManager&) = delete;

    /// @brief Método estático público: La única forma de obtener la instancia
    // Static es una función de la cual es dueña la clase en sí misma, no un objeto.
    // Se usa así GameManager::get();
    // Devuelve una referencia a la instancia única de GameManager
    // Esto asegura que solo haya una instancia en todo el programa.
    // Es lo denominado "Singleton Pattern"
    static GameManager& get();

    Inventory& getInventory();
    
    //Funciones publicas para modificar

    int getEjemplo();

    void guardarPartida();

    Player& getPlayer();
};