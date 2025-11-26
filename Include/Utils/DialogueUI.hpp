#pragma once

#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include <string>
#include "Utils/Enums.hpp"
#include "Utils/DialogueSequence.hpp"
#include "Utils/DialogueLine.hpp"
#include "Utils/Assets.hpp"
#include "Core/Game.hpp"

class DialogueUI {
private:
    // Alias de referencia al game
    Game* game;

    // Necesario para saber si mostrar botón de continuar u opciones.
    DialogueType m_type;
    std::string m_speakerName;
    std::string m_dialogueText;
    bool m_advanceClicked = false;
    int m_chosenOptionIndex = -1;

public:

    DialogueUI();

    void init();    

    void setGame(Game* gamePtr) {
        this->game = gamePtr;
    }

    ///@brief Método principal de renderizado de la UI de diálogo.
    ///@param window Ventana de renderizado.
    ///@param sequence Secuencia de diálogo actual.
    ///@param currentLineIndex Índice de la línea de diálogo actual.
    void render(sf::RenderWindow& window, const DialogueSequence& sequence, const std::vector<DialogueSequence::choiceOption>& options, const sf::Font& font, int currentLineIndex);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);

    void update(sf::Time dt);

    void renderLinearText(const DialogueLine& line);

    // Método principal de dibujo
    // Recibe la secuencia (tope de la pila) y el índice actual.
    // Retorna la opción elegida o -1 si no hubo elección.
    int renderDecisionPrompt(const std::vector<DialogueSequence::choiceOption>& options);

    // 2. Método para consultar si el usuario hizo clic en "Continuar"
    // Reinicia la bandera a 'false' inmediatamente después de consultarla.
    bool wasAdvanceClicked();
    
    // Método para obtener la opción elegida (devuelve -1 si no se eligió ninguna)
    int getChosenOption();

    void renderOptions(sf::RenderWindow& window, const DialogueSequence& sequence, const std::vector<DialogueSequence::choiceOption>& options, const sf::Font& font, int currentLineIndex);

    // Método para ser llamado por el DialogueManager en update()
    bool canAdvance();

    std::vector<std::string> options;
    
    std::vector<int> nextDialogIDs;
};