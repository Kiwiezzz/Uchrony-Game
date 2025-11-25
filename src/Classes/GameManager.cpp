#include "Classes/GameManager.hpp"


GameManager::GameManager()
{
    //~~~~~~~INVENTARIO~~~~~~~
    inventory.Init("assets/textures/Inventory.png", 0, 0, 4, 8.f);
    inventory.setDisplayScale(0.35f);
    
    //~~~~~~~FIN INVENTARIO~~~~~~~  
    
    // Inicializar estado de drag-and-drop
    draggingFrom = -1;  // -1 indica que no hay ningún item siendo arrastrado
    
    navGrid = NavGrid(16);
    
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

// ===== DRAG-AND-DROP DEL INVENTARIO =====

std::optional<Item>& GameManager::getDraggingItem() {
    return draggingItem;
}

int GameManager::getDraggingFrom() const {
    return draggingFrom;
}

void GameManager::setDraggingFrom(int from) {
    draggingFrom = from;
}

void GameManager::resetDragging() {
    draggingItem.reset();  // Elimina el item arrastrado
    draggingFrom = -1;     // Reinicia el índice
}

// ===== ACCESO A ENTIDADES Y SISTEMAS =====

Player& GameManager::getPlayer() {
    return player;
}

NavGrid& GameManager::getNavGrid() {
    return navGrid;
}

Pathfinder& GameManager::getPathfinder() {
    return pathfinder;
}

// ===== OTRAS FUNCIONES =====

int GameManager::getEjemplo()
{
    return ejemplo;
}

void GameManager::guardarPartida() { /* Lógica */ }