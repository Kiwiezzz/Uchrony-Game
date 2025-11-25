// Esto define las acciones del menú principal
#pragma once

/**
 * @brief Contiene los estados posibles del juego.
 *
 *  Estados posibles: NONE, MENU, PLAY, PAUSE, SAVE, DIALOGUE, CONTINUE, OPTIONS, CREDITS y QUIT.
 *
 * @note Si es NONE, el usuario no ha hecho click en nada aún.
 */
enum class MenuAction {
    NONE, 
    MENU,
    PLAY,
    PAUSE,
    SAVE,
    DIALOGUE,
    CONTINUE,
    OPTIONS,
    CREDITS,
    QUIT
};

/**
 * @brief Contiene los tipos posibles de diálogos del juego.
 *  
 * Tipos de diálogos posibles: NORMAL, CHOICE y TRIGGER.
 *
 * @param NORMAL Una simple línea de texto (sin opción).
 * @param CHOICE Muestra opciones al jugador.
 * @param TRIGGER Ejecuta una acción de juego.
 */
enum class DialogueType {
    NORMAL,
    CHOICE,
    TRIGGER
};