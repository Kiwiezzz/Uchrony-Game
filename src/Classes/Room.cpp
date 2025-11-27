#include "Classes/Room.hpp"
#include "Classes/GameManager.hpp"
#include "Entities/Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

// Implementaciones vacías. La lógica es: "Esta función existe, pero no hace nada aún".

void Room::init()
{
    // LÓGICA DE INICIALIZACIÓN FUTURA
}

void Room::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    // Click izquierdo: calcular pathfinding para el jugador
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Obtener posición del mouse en coordenadas del mundo
            sf::Vector2f clickPos = GameUtils::getMouseWorldPosition(window);

            // Verificar si se hizo click en alguna entidad interactiva
            // (Lógica genérica de interacción podría ir aquí en el futuro)


            // Si no hay evento especial, calcular ruta para el jugador
            Player& player = GameManager::get().getPlayer();
            Point start = navGrid.worldToGrid(player.getPosition());
            Point end = navGrid.worldToGrid(Vec2f(clickPos.x, clickPos.y));

            if (navGrid.isWalkable(end)) {
                std::vector<Point> path = pathfinder.findPath(navGrid, start, end);
                if (!path.empty()) {
                    player.setPath(path, navGrid);
                } else {
                    std::cout << "No se encontro ruta!" << std::endl;
                }
            } else {
                std::cout << "Zona prohibida!" << std::endl;
            }
        }
    }
}

void Room::update(sf::Time dt)
{
    // Actualizar todos los NPCs
    for (auto& npc : npcs) {
        npc.second.update(dt, navGrid);
    }
}

void Room::render(sf::RenderWindow& window)
{
    // 1. Renderizar el fondo primero (siempre atrás)
    window.draw(background.sprite);
    
    // Estructura temporal para ordenar el renderizado
    struct RenderItem {
        sf::Sprite* sprite;
        int layer;
        float y;
    };

    std::vector<RenderItem> renderList;

    // 2. Recolectar Entidades (Objetos)
    for (auto& entity : entities) {
        // Asumimos que Entity hereda de SpriteAsset y tiene 'layer' y 'sprite'
        // Si Entity es polimórfico, asegúrate de que tenga acceso a estos datos.
        // En tu caso, ObjectRoom hereda de Entity que hereda de SpriteAsset.
        renderList.push_back({ 
            &entity.second->sprite, 
            entity.second->layer, 
            entity.second->sprite.getPosition().y 
        });
    }

    // 3. Recolectar NPCs
    for (auto& npc : npcs) {
        // Los NPCs por defecto en capa 0, o podrías agregar un campo layer a NPC
        renderList.push_back({ 
            &npc.second.getSprite(), 
            0, // Capa por defecto 0
            npc.second.getSprite().getPosition().y 
        });
    }

    // 4. Recolectar al Jugador
    // Obtenemos el jugador desde GameManager
    Player& player = GameManager::get().getPlayer();
    renderList.push_back({ 
        &player.getSprite(), 
        0, // Capa por defecto 0
        player.getSprite().getPosition().y 
    });

    // 5. ORDENAR (Layer primero, luego Y)
    std::sort(renderList.begin(), renderList.end(), [](const RenderItem& a, const RenderItem& b) {
        if (a.layer != b.layer) {
            return a.layer < b.layer; // Capas menores primero (fondo)
        }
        return a.y < b.y; // Menor Y (arriba) primero, Mayor Y (abajo) después
    });

    // 6. DIBUJAR
    for (const auto& item : renderList) {
        window.draw(*item.sprite);
    }
}



void Room::setBackground(std::string path)
{
    background.new_path_and_update(path);
}

void Room::setCollisionAndGrid(std::string path)
{
    collision.new_path_and_update(path);
    navGrid = NavGrid(16);
    if (!navGrid.buildFromImage(collision.image)) {
        std::cerr << "Error: NavGrid::buildFromImage falló. Imagen inválida o tamaño incorrecto." << std::endl;
        //DEBERÍA CERRARSE
    }
}


void Room::addEntity(const std::string& name, Entity* entity)
{
    entities[name] = entity;
}


void Room::addObject(const std::string& name, const std::string& path, int x, int y, int layer)
{
    entities[name] = new ObjectRoom(path, x, y, layer);
}


void Room::addNpc(const std::string& name, NPC& npc){
    npcs[name] = npc;
    
    // CRÍTICO: Después de copiar el NPC, el Animator de la copia
    // todavía apunta al sprite del NPC original. Necesitamos actualizar
    // el puntero para que apunte al sprite de la copia.
    npcs[name].updateAnimatorSprite();
}

SpriteAsset& Room::getBackground()
{
    return background;
}

Entity& Room::getEntity(std::string name)
{
    // Nota: Esto lanzará una excepción si la key no existe.
    // Deberías manejarlo o usar find() si no estás seguro.
    return *entities.at(name);
}

NPC& Room::getNpc(std::string name)
{
    return npcs.at(name);
}

const NavGrid& Room::getNavGrid() const
{
    return navGrid;
}

void Room::setGame(Game* g)
{
    game = g;
}

