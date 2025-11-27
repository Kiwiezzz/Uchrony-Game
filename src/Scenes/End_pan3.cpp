#include "Scenes/StartScene.hpp"
#include "Scenes/End_pan3.hpp"
#include "Scenes/End_pan4.hpp"
#include "Pasts/Past0.hpp"

void End_pan3::init(){

    // Inicializar sistema de diálogos
    dialogueUI.init();
    dialogueUI.setGame(this->game);
    dialogueStack = new DialogueStack(*game);
    loadDialogs();

    if (!m_backgroundTexture.loadFromFile("assets/textures/Scenes/pan3.png")) {
        // Nota: El escalado lo haremos en la función render
        std::cerr << "ERROR: No se pudo cargar el fondo 'pan3.png'.\n";
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

void End_pan3::handleEvent(sf::Event& event, sf::RenderWindow& window) {

    // Evento al clickar continuar en el diálogo
    // Evento al clickar continuar en el diálogo
    if(dialogueUI.wasAdvanceClicked()){
    
        // Lógica normal de avance
        const DialogueSequence& currentDialogue = dialogueStack->getCurrentDialogue();
        dialogueStack->advanceLine();

        // 3. Ir al NODO CORRESPONDIENTE (Destruye el objeto MainMenu, pero ahora está limpio)
        // Si la pila ya está vacía antes de avanzar, cambiar al siguiente estado
            if (!dialogueStack || dialogueStack->isStackEmpty()){
                this->game->changeState(new End_pan4());
                showDialogue = false;
                return;
            }
    }
}

void End_pan3::update(sf::Time dt){}

void End_pan3::render(sf::RenderWindow& window) {

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

void End_pan3::loadDialogs() {

    // IDs de Retratos (Asegurando la coherencia)
    const std::string ID_JOHN = "John_Barr_Determinado"; 
    const std::string ID_MAQUINA = "Maquina_Misteriosa_Focus"; // Retrato o foco en la máquina
    const std::string ID_NARRADOR = "NARRADOR_FINAL"; 

    // ============================================================
    // 💡 Paso 1: Secuencia de la Misión (3 líneas de Legado Oculto).
    // ============================================================
    
    // 1. John Barr establece que la máquina no es un objeto, sino un mensaje o un desafío que le dejaron.
    DialogueLine line1("John Barr", "Esta máquina no es solo un artefacto. Es el último problema que me dejó, codificado en circuitos y líneas temporales.", ID_JOHN);
    
    // 2. El narrador sella la alusión: la máquina es la manifestación de su legado.
    DialogueLine line2("Narrador", "El amor de su vida no le había dejado una nota, le había heredado la pregunta más grande jamás construida.", ID_NARRADOR); 
    
    // 3. John Barr reafirma su propósito: descifrar ese legado.
    DialogueLine line3("John Barr", "Y no pararé hasta resolverlo. Ese es mi juramento. Descifrar por qué ella me dejó la clave para volver a empezar...", ID_JOHN); 
    
    DialogueSequence legacyResolve(DialogueType::NORMAL);
    legacyResolve.dialogueLines.emplace_back(line1);
    legacyResolve.dialogueLines.emplace_back(line2);
    legacyResolve.dialogueLines.emplace_back(line3);

    // ============================================================
    // 💡 Paso 2: Empuja la secuencia a la pila.
    // ============================================================
    
    dialogueStack->pushDialogue(legacyResolve);
}

void End_pan3::loadNeighborDialogs() {};