#include <string>
#include <vector>

class DialogueLine {
private:
    std::string characterName;
    std::string text;
    std::string portraitID;
    // std::vector<std::string> choices;

public:
    DialogueLine(const std::string& name, const std::string& text, const std::string& id)
        : characterName(name), text(text), portraitID(id) {}
};