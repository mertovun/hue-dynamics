#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
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

    void updateVel(float fx, float fy, float dt);
    void update(float dt);
    void print();
    void render(sf::RenderWindow& window);

    int getId() const { return id; }
    int getHue() const { return hue; }
    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }

    // sf::Vector2f getPosition() const { return sf::Vector2f(x, y); }
    // sf::Vector2f getVelocity() const { return sf::Vector2f(vx, vy); }
};

