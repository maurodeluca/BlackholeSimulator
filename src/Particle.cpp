#include "Particle.hpp"

// Constructor
Particle::Particle(double rsIn, int jIn, double thetaIn)
    : rs(rsIn), j(jIn), theta(thetaIn)
{
    shape.setRadius(3.f);
    shape.setFillColor(sf::Color::Green);
    position = calc_position();
    phivals = 0.0001;
}

// Update function
void Particle::update() {
    phivals += i;
    position = calc_position();

    auto newPosition = sf::Vector2f(position.x, position.y);

    // Add current position to trail
    trail.push_front(Trail(newPosition, varphivals));
    if (trail.size() > maxTrailLength) {
        trail.pop_back();
    }

    shape.setPosition(newPosition);
}

// Draw function
void Particle::draw(sf::RenderWindow& window) {
    // Draw the trail
    for (const auto& p : trail) {
        if (Vec2f::isInFront(p.position) && p.varphivals > M_PI)
            continue;

        sf::CircleShape trailParticle(2.f);
        trailParticle.setFillColor(sf::Color::Red);
        trailParticle.setPosition(p.position);
        window.draw(trailParticle);
    }

    // Draw the current particle
    window.draw(shape);
}

// Private helper: calculate current position
sf::Vector2f Particle::calc_position() {
    double bmax = std::sqrt(std::pow(rs, 3) / (rs - 2)) + 1;

    double part = std::acos(
        std::copysign(1.0, M_PI - phivals) * std::cos(phivals) /
        std::sqrt(std::pow(std::cos(phivals), 2) + std::pow(std::sin(phivals), 2) * std::pow(std::cos(theta), 2))
    );
    varphivals = (phivals >= M_PI ? M_PI : 0.0) + part;
    double psivals1 = j * M_PI + Lensing::psi(phivals, theta);

    // Create psivals2 and psivals3
    std::vector<std::pair<double, double>> psivals2, psivals3;
    for (int k = 0; k < steps; ++k) {
        double start = (j > 0) ? 5 : 0;
        double b = start + k * ((bmax - start) / (steps - 1));
        std::complex<double> root = rs - Lensing::minrs(b);
        double val = Lensing::phi_from_x(std::sqrt(root), b);
        psivals2.emplace_back(val, b);
    }
    for (int k = 0; k < steps; ++k) {
        double start = (j > 0) ? 5 : 3;
        double b = start + k * ((bmax - start) / (steps - 1));
        std::complex<double> root = rs - Lensing::minrs(b);
        double val = Lensing::phi_from_x(-std::sqrt(root), b);
        psivals3.emplace_back(val, b);
    }

    // Find best match
    auto cmp = [psivals1](const std::pair<double, double>& a, const std::pair<double, double>& b) {
        return std::abs(a.first - psivals1) < std::abs(b.first - psivals1);
        };
    auto& best2 = *std::min_element(psivals2.begin(), psivals2.end(), cmp);
    auto& best3 = *std::min_element(psivals3.begin(), psivals3.end(), cmp);

    double bvals = (std::abs(best2.first - psivals1) < std::abs(best3.first - psivals1)) ? best2.second : best3.second;

    double alphavals = bvals * std::cos(varphivals);
    double betavals = -bvals * std::sin(varphivals);

    float x = -static_cast<float>(alphavals * 10 - (SCALE * WINDOW_WIDTH / 2.f));
    float y = -static_cast<float>(betavals * 10 - (SCALE * WINDOW_HEIGHT / 2.f));

    return sf::Vector2f(x, y);
}
