#include "Particle.h"
#include "Util.h"
#include <cmath>
#include "Config.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Particle::Particle(float x, float y, float vx, float vy, float hue)
: vx(vx), vy(vy), x(x), y(y), hue(hue), id(counter++) {
    circle = sf::CircleShape(Config::radius);
    circle.setPosition(x-Config::radius, y-Config::radius);
    int r,g,b;
    HSLToRGB(hue, Config::saturation, Config::lightness, r, g, b);
    circle.setFillColor(sf::Color(r,g,b,Config::alpha));
};

std::vector<Particle*> Particle::generateParticles() {
    std::vector<Particle*> particles{};
    for (size_t i = 0; i<Config::n; ++i) {
        float x = randomFloat(0.f, Config::wWidth);
        float y = randomFloat(0.f, Config::wHeight);
        float vx = randomFloat(-Config::vMax, Config::vMax);
        float vy = randomFloat(-Config::vMax, Config::vMax);
        float hue = 1.f / Config::nHue * randomInt(0,Config::nHue);
        Particle * p = new Particle(x,y,vx,vy,hue);
        particles.push_back(p);
    }
    return particles;
}

void Particle::update(float dt) {
    x += vx*dt;
    y += vy*dt;
    if (x>Config::wWidth) x -= Config::wWidth;
    else if (x<0.f) x += Config::wWidth;
    if (y>Config::wHeight) y -= Config::wHeight;
    else if (y<0.f) y += Config::wHeight;

    circle.setPosition(x-Config::radius, y-Config::radius);
}

void Particle::print() {
    std::cout << id << "\n";
    std::cout << x << y << "\n";
    std::cout << vx << vy << "\n";
    std::cout << hue << "\n";
}

void Particle::render(sf::RenderWindow& window) {
    window.draw(circle);
}

int Particle::counter = 0;
std::vector<Particle*> Particle::ParticleVec = Particle::generateParticles();
