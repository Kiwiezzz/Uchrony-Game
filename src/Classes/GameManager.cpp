#include "Classes/GameManager.hpp"


GameManager::GameManager()
{
    //Pones aquí los val iniciales1234
    ejemplo = 1;
} 

GameManager& GameManager::get() {
    // Esta instancia se crea la primera vez y vive todo el programa
    static GameManager instance; 
    return instance;
}


//Funciones publicas para modificar

int GameManager::getEjemplo()
{
    return ejemplo;
}

void GameManager::guardarPartida() { /* Lógica */ }