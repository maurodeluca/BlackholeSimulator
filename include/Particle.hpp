#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include "Vec2f.hpp"
#include "Constants.hpp"
#include "LensingMath.hpp"
#include "Trail.hpp"

class Particle {
public:
    double theta;
    double varphivals;
    sf::Vector2f position;

    Particle(double rs, int j, double theta);

    void update();
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f calc_position();

    // Particle properties
    sf::CircleShape shape;
    std::deque<Trail> trail;

    // Constants
    static constexpr int maxTrailLength = 200;
    static constexpr int steps = 200;
    const double rs;
    const int j;
    const double i = 2 * M_PI / steps;

    // Dynamic state
    double phivals;
};