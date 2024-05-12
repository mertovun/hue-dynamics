#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Particle {
private:
    static int counter;
    int id;
    sf::CircleShape circle;
    float hue;
    float x, y;
    float vx, vy;

public:
    Particle(float x, float y, float vx, float vy, float hue);
    static std::vector<Particle*> ParticleVec;
    static std::vector<Particle*> generateParticles();
    void update(float dt);
    void print();
    void render(sf::RenderWindow& window);
};

