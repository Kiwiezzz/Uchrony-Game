#include "Utils/SceneFactory.hpp"

Room SceneFactory::createRoom(const std::string& bgPath, const std::string& collisionPath) {
    Room room;
    room.setBackground(bgPath);
    
    if (!collisionPath.empty()) {
        room.setCollisionAndGrid(collisionPath);
    }
    
    return room;
}
