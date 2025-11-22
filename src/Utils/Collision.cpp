#include "Utils/Collision.hpp"

/*
    Esto es una implementación simple para pruebas de colisión AABB 
    (Axis-Aligned Bounding Box). La función devuelve true si los 
    rectángulos se solapan en ambos ejes.
*/

bool checkAABB(const Rect& a, const Rect& b) {
    // Superposición en X: la izquierda de A es antes de la derecha de B
    // y la derecha de A es después de la izquierda de B
    bool overlapX = (a.x < (b.x + b.w)) && ((a.x + a.w) > b.x);

    // Superposición en Y similar
    bool overlapY = (a.y < (b.y + b.h)) && ((a.y + a.h) > b.y);

    // Hay colisión únicamente si hay superposición en ambos ejes
    return overlapX && overlapY;
}
