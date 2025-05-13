#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <cstdlib>
#include "Particle.hpp"
#include "Constants.hpp"

sf::Vector2f BLACKHOLE_CENTER{ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f };
const float BLACKHOLE_RADIUS = SCALE * std::sqrt(27.f);

std::vector<Particle> initializeParticles() {
    std::vector<Particle> accretionDisk;

    for (int j = 0; j < 2; ++j) {
        for (double rs = 5.0; rs < 25.0; rs += 5.0)
            accretionDisk.emplace_back(Particle(rs, j, 85.0 * M_PI / 180.0));
    }

    return accretionDisk;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Black Hole Simulation");
    sf::CircleShape blackHole(BLACKHOLE_RADIUS);
    blackHole.setOrigin(sf::Vector2f(0, 0));
    blackHole.setFillColor(sf::Color::White);
    blackHole.setPosition({ (WINDOW_WIDTH / 2.f) - BLACKHOLE_RADIUS, (WINDOW_HEIGHT / 2.f) - BLACKHOLE_RADIUS });

    std::vector<Particle> accretionDisk = initializeParticles();

    // Create the camera view
    sf::View view(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f((WINDOW_WIDTH), (WINDOW_HEIGHT))));

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R)) {
            accretionDisk = initializeParticles();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
            for (auto& particle : accretionDisk) {
                particle.theta += 1.0 * M_PI / 180.0;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
            for (auto& particle : accretionDisk) {
                particle.theta -= 1.0 * M_PI / 180.0;
            }
        }

        // Update particles (moving them in a circular orbit)
        for (auto& particle : accretionDisk) {
                particle.update();
        }

        // Clear the window and set the view
        window.clear(sf::Color::Black);
        window.setView(view);

        // Draw the black hole
        window.draw(blackHole);

        // Draw the accretion disk particles (with trails)
        for (auto& particle : accretionDisk) {
            particle.draw(window);
        }

        // Display the contents of the window
        window.display();
    }

    return 0;
}
