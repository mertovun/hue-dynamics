#include "Particle.h"
#include "Util.h"
#include <cmath>
#include "Config.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

Particle::Particle(float x, float y, float vx, float vy, int hue)
: vx(vx), vy(vy), x(x), y(y), hue(hue), id(counter++) {
    setGridKey();
    circle = sf::CircleShape(Config::radius);
    circle.setPosition(x-Config::radius, y-Config::radius);
    int r,g,b;
    float fHue = 1.f / Config::nHue * hue;
    HSLToRGB(fHue, Config::saturation, Config::lightness, r, g, b);
    circle.setFillColor(sf::Color(r,g,b,Config::alpha));
};

std::vector<Particle*> Particle::generateParticles() {
    std::vector<Particle*> particles{};
    for (size_t i = 0; i<Config::n; ++i) {
        float x = randomFloat(0.f, Config::wWidth);
        float y = randomFloat(0.f, Config::wHeight);
        float vx = randomFloat(-Config::vMax, Config::vMax);
        float vy = randomFloat(-Config::vMax, Config::vMax);
        int hue = randomInt(0,Config::nHue);
        Particle * p = new Particle(x,y,vx,vy,hue);
        particles.push_back(p);
    }
    return particles;
}

int Particle::counter = 0;

int Particle::nGrid = std::floor(Config::wHeight / Config::rMax);
float Particle::CellSize = Config::wHeight / Particle::nGrid;
std::unordered_map<int, std::set<int>> Particle::GridMap;

void Particle::PrintGridDistribution() {
    size_t numCells = Particle::nGrid * Particle::nGrid;
    for (size_t i = 0; i<numCells; ++i) {
        if (i % Particle::nGrid == 0) std::cout << "\n";
        std::cout << Particle::GridMap[i].size() << " ";
    }
}

std::vector<Particle*> Particle::ParticleVec = Particle::generateParticles();

void Particle::setGridKey() {
    int new_grid_key = Particle::nGrid * std::floor(y/Particle::CellSize) + std::floor(x/Particle::CellSize);
    if (grid_key == -1 || new_grid_key != grid_key) {
        if (grid_key != -1) {
            GridMap[grid_key].erase(id);
        }
        grid_key = new_grid_key;
        GridMap[grid_key].insert(id);
    }
}

void Particle::updateVel(float fx, float fy, float dt) {
    vx -= fx*dt;
    vy -= fy*dt;

    vx *= std::pow(Config::damping, dt);
    vy *= std::pow(Config::damping, dt);
}

void Particle::update(float dt) {
    x += vx*dt;
    y += vy*dt;
    if (x>Config::wWidth) x -= Config::wWidth;
    else if (x<0.f) x += Config::wWidth;
    if (y>Config::wHeight) y -= Config::wHeight;
    else if (y<0.f) y += Config::wHeight;
    setGridKey();

    circle.setPosition(x-Config::radius, y-Config::radius);
}

void Particle::print() {
    std::cout << id << "\n";
    std::cout << x << " " << y << "\n";
    std::cout << vx << " " << vy << "\n";
    std::cout << hue << "\n";
    std::cout << grid_key << "\n";
   
}

void Particle::render(sf::RenderWindow& window) {
    window.draw(circle);
}

