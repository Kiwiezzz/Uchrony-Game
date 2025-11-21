// Esto define las acciones del menú principal
#pragma once

enum class MenuAction {
    NONE, // El usuario no ha hecho clic en nada aún
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

enum class DialogType {
    LINE,     // Una simple línea de texto (sin opción)
    OPTIONS,  // Muestra opciones al jugador
    TRIGGER   // Ejecuta una acción de juego (sin texto)
};