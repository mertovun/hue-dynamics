#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include <iostream>
#include <cmath>
#include "Particle.h"
#include "Config.h"
#include "Util.h"

void updateScene(std::vector<Particle*>& particles, float dt) {
    for (Particle * particle : particles) {
        particle->update(dt);
    }
}

void renderScene(sf::RenderWindow& window, const std::vector<Particle*>& particles) {
    for (Particle * particle : particles) {
        particle->render(window);
    }
}

int  main() { 
    sf::Clock clock;
    float time = clock.getElapsedTime().asSeconds();

    sf::Font font;
    sf::Text text;
    text.setFont(font);

    if (!font.loadFromFile("fonts/tech.ttf")) {
        std::cerr << "Font not found";
        exit(-1);
    }

    int numCells = static_cast<int>(ceil(Config::wWidth/Config::rMax));
    float gridSize = static_cast<float>(Config::wWidth)/ numCells;

    sf::RenderWindow window(
                sf::VideoMode(Config::wWidth,Config::wHeight), 
                "SFML Works!", 
                sf::Style::Close, 
                sf::ContextSettings(24,8,4));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        float newTime = clock.getElapsedTime().asSeconds();
        float dt = newTime - time;
        time = newTime;
        // std::cout << Particle::ParticleVec.size() << "\n";
        // Particle::ParticleVec[100]->print();
        updateScene(Particle::ParticleVec, dt);
        renderScene(window, Particle::ParticleVec);
        float fps = 1.f / dt; 
        std::ostringstream out;
        out << fps;
        std::string str(out.str());
        text.setString(str);
        window.draw(text);
        window.display();
    }
    return 0;
}
