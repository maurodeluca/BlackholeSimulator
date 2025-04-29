#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <cstdlib>
#include "Particle.hpp"
#include "Constants.hpp"

sf::Vector2f BLACKHOLE_CENTER{ SCALE * WINDOW_WIDTH / 2.f, SCALE * WINDOW_HEIGHT / 2.f };
const float BLACKHOLE_RADIUS = 10 * std::sqrt(SCALE * 27.f);

int main() {
    sf::RenderWindow window(sf::VideoMode({ (int)SCALE * WINDOW_WIDTH, (int)SCALE * WINDOW_HEIGHT }), "Black Hole Simulation");
    sf::CircleShape blackHole(BLACKHOLE_RADIUS);
    blackHole.setOrigin(sf::Vector2f(0, 0));
    blackHole.setFillColor(sf::Color::White);
    blackHole.setPosition({ (SCALE * WINDOW_WIDTH / 2.f) - BLACKHOLE_RADIUS, (SCALE * WINDOW_HEIGHT / 2.f) - BLACKHOLE_RADIUS });

    std::vector<Particle> accretionDisk;

    for (double rs = SCALE * 5.0; rs < SCALE * 25.0; rs += SCALE * 5.0)
         accretionDisk.emplace_back(Particle(rs, 0, 85.0 * M_PI / 180.0));


    // Create the camera view
    sf::View view(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f((SCALE * WINDOW_WIDTH), (SCALE * WINDOW_HEIGHT))));

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
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
