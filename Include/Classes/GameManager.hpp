#include "Utils/GameUtilities.hpp"
#include "Utils/Assets.hpp"
#include "Entities/Player.hpp"
#include "Utils/NavGrid.hpp"
#include "Utils/Pathfinder.hpp"
#include "Utils/Collision.hpp"
#include "Entities/Inventory.hpp"
#include <optional> // Para std::optional


class GameManager {
private:
    //Atributos
    Inventory inventory;
    
    // Estado de drag-and-drop del inventario
    std::optional<Item> draggingItem;  // Item que se está arrastrando (si hay alguno)
    int draggingFrom;                   // Índice desde donde se tomó el item (-1 si ninguno)
    
    // Variable de ejemplo (usada por getEjemplo)
    int ejemplo = 0;
    
    Player player;
    NavGrid navGrid;
    Pathfinder pathfinder;

    //Texturas
    sf::Texture texturaJugador; 
    sf::Sprite spriteJugador;
    sf::Texture slotTex;

    //Fondos y colisiones
    SpriteAsset background;
    ImageAsset collision;
    

    GameManager(); 


public:
    GameManager(const GameManager&) = delete;
    void operator=(const GameManager&) = delete;

    /// @brief Método estático público: La única forma de obtener la instancia.
    // Static es una función de la cual es dueña la clase en sí misma, no un objeto.
    // Se usa así GameManager::get();
    static GameManager& get();

    // ===== INVENTARIO =====
    Inventory& getInventory();

    // ===== DRAG-AND-DROP DEL INVENTARIO =====
    /// @brief Obtiene el item que se está arrastrando actualmente
    std::optional<Item>& getDraggingItem();
    
    /// @brief Obtiene el índice desde donde se tomó el item arrastrado
    int getDraggingFrom() const;
    
    /// @brief Establece el índice desde donde se tomó el item
    void setDraggingFrom(int from);
    
    /// @brief Reinicia el estado de drag-and-drop (sin item arrastrado)
    void resetDragging();

    // ===== ACCESO A ENTIDADES Y SISTEMAS =====
    /// @brief Obtiene referencia al jugador
    Player& getPlayer();
    
    /// @brief Obtiene referencia al NavGrid
    NavGrid& getNavGrid();
    
    /// @brief Obtiene referencia al Pathfinder
    Pathfinder& getPathfinder();

    // ===== OTRAS FUNCIONES =====
    int getEjemplo();

    void guardarPartida();
};