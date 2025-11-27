#include "Scenes/StartScene.hpp"
#include "Scenes/End_pan4.hpp"
#include "Pasts/Past0.hpp"


void End_pan4::init(){

    // Inicializar sistema de diálogos
    dialogueUI.init();
    dialogueUI.setGame(this->game);
    dialogueStack = new DialogueStack(*game);
    loadDialogs();

    if (!m_backgroundTexture.loadFromFile("assets/textures/Scenes/pan4.png")) {
        // Nota: El escalado lo haremos en la función render
        std::cerr << "ERROR: No se pudo cargar el fondo 'pan4.png'.\n";
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

void End_pan4::handleEvent(sf::Event& event, sf::RenderWindow& window) {

    // Evento al clickar continuar en el diálogo
    if(dialogueUI.wasAdvanceClicked()){
    
        // Lógica normal de avance
        const DialogueSequence& currentDialogue = dialogueStack->getCurrentDialogue();
        dialogueStack->advanceLine();

        // 3. Ir al NODO CORRESPONDIENTE (Destruye el objeto MainMenu, pero ahora está limpio)
        // Si la pila ya está vacía antes de avanzar, cambiar al siguiente estado
            if (!dialogueStack || dialogueStack->isStackEmpty()){
                m_sceneMusic.stop(); 
                this->game->changeState(new MainMenu());
                showDialogue = false;
                return;
            }
    }
}

void End_pan4::update(sf::Time dt){}

void End_pan4::render(sf::RenderWindow& window) {

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

void End_pan4::loadDialogs() {
    // IDs de Retratos (Asegurando la coherencia)
    const std::string ID_JOHN = "John_Barr_Determinado"; 
    const std::string ID_MAQUINA = "Maquina_Misteriosa_Focus"; // Máquina del tiempo
    const std::string ID_TOSTADORA = "Tostadora_Final_Focus";  // La imagen de la tostadora
    const std::string ID_NARRADOR = "NARRADOR_FINAL"; 

    // ============================================================
    // 💡 Secuencia de la Revelación (El Clímax Absurdo).
    // ============================================================
    
    // (Asumimos que la línea anterior del diálogo fue: 
    // "Descifrar por qué ella me dejó la clave para volver a empezar...")

    // 1. John Barr termina la frase con la duda final y absurda.
    DialogueLine line1("John Barr", "... a comer pan?", ID_JOHN); 
    
    // 2. El narrador describe el cambio visual (la transformación en la tostadora).
    DialogueLine line2("Narrador", "El brillo de la Máquina del Tiempo se apagó, dejando en su lugar una reluciente tostadora industrial de cuatro ranuras.", ID_TOSTADORA); 
    
    // 3. La conclusión final y satírica del narrador.
    DialogueLine line3("Narrador", "La verdad era obvia: John Barr no era un viajero del tiempo; era un matemático amnésico obsesionado con un pan perfectamente tostado... como él.", ID_NARRADOR); 
    
    DialogueSequence finalDelusion(DialogueType::NORMAL);
    finalDelusion.dialogueLines.emplace_back(line1);
    finalDelusion.dialogueLines.emplace_back(line2);
    finalDelusion.dialogueLines.emplace_back(line3);

    // ============================================================
    // 💡 Paso 2: Empuja la secuencia a la pila.
    // ============================================================
    
    dialogueStack->pushDialogue(finalDelusion);
}

void End_pan4::loadNeighborDialogs() {};