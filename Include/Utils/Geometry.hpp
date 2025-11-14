#pragma once
#include <cmath>

// Un punto en la cuadrícula
struct Point {
    int x, y;

    // Operadores para comparar puntos (necesarios para A*)
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
    // Para usar Point como clave en un std::map
    bool operator<(const Point& other) const {
        if (x < other.x) return true;
        if (x > other.x) return false;
        return y < other.y;
    }
};

// Vector 2D (para posiciones, velocidad y movimiento)
struct Vec2f {
    float x, y;

    Vec2f() : x(0.0f), y(0.0f) {}
    Vec2f(float x, float y) : x(x), y(y) {}

    // Resta de vectores (para obtener dirección)
    Vec2f operator-(const Vec2f& other) const {
        return Vec2f(x - other.x, y - other.y);
    }
    
    // Suma de vectores (para aplicar movimiento)
    Vec2f operator+(const Vec2f& other) const {
        return Vec2f(x + other.x, y + other.y);
    }

    // Multiplicación por escalar (para aplicar velocidad/deltaTime)
    Vec2f operator*(float scalar) const {
        return Vec2f(x * scalar, y * scalar);
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vec2f normalized() const {
        float mag = magnitude();
        if (mag > 0) {
            return Vec2f(x / mag, y / mag);
        }
        return Vec2f(0, 0);
    }
};

// Rectángulo para colisiones AABB
struct Rect {
    float x, y; // Esquina superior izquierda
    float w, h; // Ancho y Alto
};