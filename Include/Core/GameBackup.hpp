/* GAME BACKUP ROSA VERSION

#include "Utils/MenuUI.hpp"
#include "imgui-SFML.h"

class Game {
public:
    Game(); 

    ~Game();

    void run();

    MenuAction getCurrentState() const { return m_currentState; }
    
    void setState(MenuAction newState) { m_currentState = newState; }

private:
    sf::RenderWindow m_window;

    MenuAction m_currentState;

    //DialogueManager m_dialogueManager;

    MenuUI m_menuUI;

    void MySaveFunction();

    void initImGui();

    sf::Texture m_logoTexture;
};








*/