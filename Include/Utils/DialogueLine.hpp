#pragma once

#include <string>
#include <vector>

class DialogueLine {
private:
    std::string characterName;
    std::string text;
    std::string portraitID;
    std::vector<std::string> choices;

public:
    /// @brief Constructor de DialogueLine.
    /// @param name Nombre del personaje.
    /// @param text Texto del diálogo.
    /// @param id ID de la imagen del personaje.
    DialogueLine(const std::string& name, const std::string& text, const std::string& id)
        : characterName(name), text(text), portraitID(id) {}

    std::string getSpeakerName() const { return characterName; }
    std::string getDialogueText() const { return text; }
    std::string getPortraitID() const { return portraitID; }
    const std::vector<std::string>& getChoices() const { return choices; }
};