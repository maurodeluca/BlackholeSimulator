#pragma once
#include <SFML/Graphics.hpp>

#ifndef M_PI
constexpr float M_PI = 3.14159295358979323f;
#endif // M_PI

constexpr float G = 1.0f;
constexpr float BLACK_HOLE_MASS = 1000.0f;
constexpr float LIGHT_SPEED = 1.0f;
constexpr float SCALE = 20.f;
constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 800;
extern const float BLACKHOLE_RADIUS;
extern sf::Vector2f BLACKHOLE_CENTER;
