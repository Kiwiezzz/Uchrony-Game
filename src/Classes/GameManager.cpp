#include "Classes/GameManager.hpp"


GameManager::GameManager()
{
    //~~~~~~~INVENTARIO~~~~~~~
    inventory.Init("assets/textures/Inventory.png", 0, 0, 4, 8.f);
    inventory.setDisplayScale(0.35f);
    
    //~~~~~~~FIN INVENTARIO~~~~~~~
    

    
} 

GameManager& GameManager::get() {
    // Esta instancia se crea la primera vez y vive todo el programa
    static GameManager instance; 
    return instance;
}


//Funciones publicas para modificar

Inventory& GameManager::getInventory() {
    return inventory;
}

int GameManager::getEjemplo()
{
    return ejemplo;
}

void GameManager::guardarPartida() { /* Lógica */ }


Player& GameManager::getPlayer()
{
    return player;
}