#pragma once

#include <SFML/Graphics.hpp>

class Trail {
public:
    double varphivals;
    sf::Vector2f position;

    Trail(sf::Vector2f position, double varphivals);
};