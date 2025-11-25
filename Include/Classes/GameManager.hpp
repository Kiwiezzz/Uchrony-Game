class GameManager {
private:
    //Atributos
    /*
    inventario
    jugador
    */
    int ejemplo;

    GameManager()
    {
        //Pones aquí los val iniciales
        ejemplo = 1;
    } 

public:
    GameManager(const GameManager&) = delete;
    void operator=(const GameManager&) = delete;

    /// @brief Método estático público: La única forma de obtener la instancia.
    // Static es una función de la cual es dueña la clase en sí misma, no un objeto.
    // Se usa así GameManager::get();
    static GameManager& get();



    //Funciones publicas para modificar

    int getEjemplo();

    void guardarPartida();
};