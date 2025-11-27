#include "Scenes/loco1.hpp"
#include "Scenes/loco2.hpp"
#include "Pasts/Past0.hpp"
#include <filesystem>
    
void loco1::init(){

    // Inicializar sistema de diálogos
    dialogueUI.init();
    dialogueUI.setGame(this->game);
    dialogueStack = new DialogueStack(*game);
    loadDialogs();

    if (!m_backgroundTexture.loadFromFile("assets/textures/Scenes/loco1.png")) {
        // Nota: El escalado lo haremos en la función render
        std::cerr << "ERROR: No se pudo cargar el fondo '1.png'.\n";
    }
    
    m_backgroundSprite.setTexture(m_backgroundTexture);

    // 1. Cargar el archivo de música
    if (!m_sceneMusic.openFromFile("assets/music/Justice.mp3")) {

        std::cerr << "Error al cargar la música del menú." << std::endl;

    } else {
        // 2. Configurar la música
        m_sceneMusic.setVolume(50.0f); // 50% de volumen
        m_sceneMusic.setLoop(true);   // Repetir la música indefinidamente

        // 3. Iniciar la reproducción
        m_sceneMusic.play();

    }
}

void loco1::handleEvent(sf::Event& event, sf::RenderWindow& window) {

    // Evento al clickar continuar en el diálogo
    if(dialogueUI.wasAdvanceClicked()){
    
        // Lógica normal de avance
        const DialogueSequence& currentDialogue = dialogueStack->getCurrentDialogue();
        dialogueStack->advanceLine();

        // 3. Ir al NODO CORRESPONDIENTE (Destruye el objeto MainMenu, pero ahora está limpio)
        // Si la pila ya está vacía antes de avanzar, cambiar al siguiente estado
            if (!dialogueStack || dialogueStack->isStackEmpty()){
                m_sceneMusic.stop(); 
                this->game->changeState(new loco2());
                showDialogue = false;
                return;
            }
    }
}

void loco1::update(sf::Time dt){}

void loco1::render(sf::RenderWindow& window) {

    window.clear();

    // --- SETUP DE VENTANA (Dimensiones y Posición) ---
    float window_width = (float)window.getSize().x;
    float window_height = (float)window.getSize().y;
    // Tamaño original de la textura de fondo
    float originalWidth = (float)m_backgroundTexture.getSize().x;
    float originalHeight = (float)m_backgroundTexture.getSize().y;

    // Opción: Mantiene la proporción y cubre toda la ventana (efecto "Cover")
    float scaleX = window_width / originalWidth;
    float scaleY = window_height / originalHeight;
    float scale = std::max(scaleX, scaleY);
        
    // B. APLICAR ESCALA Y CENTRADO A SPRITE DE FONDO
    m_backgroundSprite.setScale(scale, scale);

    // C. Calcular el desplazamiento para centrar la imagen
    float offsetX = (window_width - (originalWidth * scale)) * 0.5f;
    float offsetY = (window_height - (originalHeight * scale)) * 0.5f;

    m_backgroundSprite.setPosition(offsetX, offsetY);
        
    // D. DIBUJAR EL SPRITE
    window.draw(m_backgroundSprite);
 
    if (this->game != nullptr) {     // Verificamos que el jefe exista
        m_customFont = this->game->getFont(); // Le pedimos la fuente
    }

    if (m_customFont) {
        ImGui::PushFont(m_customFont); 
    }

    // 1. Definir el TAMAÑO del menú basado en la ventana (Responsive Size)
    // Por ejemplo: El menú ocupa el 75% del ancho y el 80% de la altura de la ventana.
    const float MENU_WIDTH_PERCENT = 1.0f;
    const float MENU_HEIGHT_PERCENT = 1.0f;

    float menuWidth = window_width * MENU_WIDTH_PERCENT;
    float menuHeight = window_height * MENU_HEIGHT_PERCENT;

    // 1. Posicionar la ventana del menú en el centro de la pantalla
    ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight));
    ImGui::SetNextWindowPos(
        ImVec2(window_width * 0.5f, window_height * 0.5f), 
        ImGuiCond_Always, 
        ImVec2(0.5f, 0.5f) // Pivote: Centrar el centro de la ventana en el centro de la pantalla
    );

    ImGuiWindowFlags flags = 
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |      
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |    
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground;
    
    ImGui::Begin("Scene", nullptr, flags);

    window.setView(window.getView());

    if (showDialogue && dialogueStack && !dialogueStack->isStackEmpty()) {

        const DialogueSequence& currentDialogue = dialogueStack->getCurrentDialogue(); 

        dialogueUI.render(window, currentDialogue, currentDialogue.options, game->getSFMLFont(), dialogueStack->getCurrentLineIndex()); 
    }    
    
    ImGui::End(); 

    if (m_customFont) {
        ImGui::PopFont();
    }

}

void loco1::loadDialogs() {

    // Asegúrate de que los IDs de los retratos estén definidos o sean rutas válidas
    const std::string ID_JOHN = "John_Barr_Neutral";
    const std::string ID_WIFE_PORTRAIT = "Wife_Portrait_Focus"; // Retrato de la esposa

    // ============================================================
    // 💡 Paso 1: Crea y puebla los DialogueLine (Diálogo del Retrato).
    // ============================================================

    // Líneas de John Barr (Monólogo)
    DialogueLine line1("Narrador", "No lo recuerda pero", ID_JOHN); // Pausa inicial
    DialogueLine line2("Narrador", "En realidad nunca tuvo esposa.", ID_WIFE_PORTRAIT);
    DialogueLine line3("Narrador", "Estuvo varios meses internado por su condición mental", ID_JOHN);
    
    // --- Secuencia 1: Diálogo Monólogo (Para dar contexto emocional)
    DialogueSequence portraitDialogue(DialogueType::NORMAL);
    portraitDialogue.dialogueLines.emplace_back(line1);
    portraitDialogue.dialogueLines.emplace_back(line2);
    portraitDialogue.dialogueLines.emplace_back(line3);
    
    // ============================================================
    // 💡 Paso 2: Crear el Diálogo de Transición (El misterio).
    // ============================================================

    // Líneas de transición
    
    DialogueSequence noiseDialogue(DialogueType::NORMAL);

    // ============================================================
    // 💡 Paso 3: Empuja las secuencias a la pila (El último en entrar es el primero en ejecutarse).
    // ============================================================
    
    // El juego ejecutará primero noiseDialogue, y luego portraitDialogue.
    
    dialogueStack->pushDialogue(noiseDialogue);      // Se ejecuta SEGUNDO (Lo que lo saca de la habitación)
    dialogueStack->pushDialogue(portraitDialogue);   // Se ejecuta PRIMERO (El monólogo del retrato)

}

void loco1::loadNeighborDialogs() {};