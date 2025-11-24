#include <string>
#include <vector>

struct DialogueData {
    std::string character;
    std::string text;
    std::vector<std::string> choices;
};

enum class DialogueType {
    NORMAL,
    CHOICE
};