#pragma once

#include "Core/GameState.hpp"
#include <string>

class Dialogue1 : public GameState {
private:
    enum class DialogType {
        LINE,
        CHOICE
    };

    DialogType m_type;
    std::string m_speakerName;
    std::string m_dialogueText;
    bool m_advanceClicked;

public:
    void init() override;
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;
};