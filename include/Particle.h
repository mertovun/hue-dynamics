#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <unordered_map>
#include <vector>

class Particle {
private:
    static int counter;
    int id;
    int grid_key = -1;
    sf::CircleShape circle;
    int hue;
    float x, y;
    float vx, vy;

public:
    Particle(float x, float y, float vx, float vy, int hue);

    static int nGrid;
    static float CellSize;
    static std::unordered_map<int, std::set<int>> GridMap;
    static void PrintGridDistribution();

    static std::vector<Particle*> ParticleVec;
    static std::vector<Particle*> generateParticles();

    void setGridKey();
    void update(float dt);
    void print();
    void render(sf::RenderWindow& window);
};

