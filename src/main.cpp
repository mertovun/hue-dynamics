#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include <iostream>
#include <cmath>
#include "Particle.h"
#include "Config.h"
#include "Dynamics.h"
#include "Util.h"

void updatePhysics(std::vector<Particle*>& particles, float dt) {
    const int numCells = Particle::nGrid * Particle::nGrid;
    for (size_t i = 0; i<numCells; ++i) {
        for (int nx = -1; nx<=1; nx++) {
            for (int ny = -1; ny <= 1; ny++) {
                int j = (i+numCells+nx+ny*Particle::nGrid) % numCells;

                for (auto& id_A : Particle::GridMap[i] ) {
                    for (auto& id_B : Particle::GridMap[j]) {
                        if (id_A < id_B) {
                            float dx = particles[id_B]->getX()-particles[id_A]->getX();
                            float dy = particles[id_B]->getY()-particles[id_A]->getY();

                            if (dx<-Config::rMax) dx += Config::wHeight;
                            else if (dx>Config::rMax ) dx -= Config::wHeight;
                            if (dy<-Config::rMax) dy += Config::wHeight;
                            else if (dy>Config::rMax ) dy -= Config::wHeight;

                            int hue_A = particles[id_A]->getHue();
                            int hue_B = particles[id_B]->getHue();
                            std::array<float, 2> f_A = Dynamics::calculateForce(hue_A, hue_B,dx,dy);
                            particles[id_A]->updateVel(f_A[0],f_A[1],dt);
                            std::array<float, 2> f_B;
                            if (hue_A == hue_B) {
                                particles[id_B]->updateVel(-f_A[0],-f_A[1],dt);
                            }
                            else {
                                f_B =  Dynamics::calculateForce(hue_B, hue_A,-dx,-dy);
                                particles[id_B]->updateVel(f_B[0],f_B[1],dt);
                            }
                        }
                    }
                }
            }
        }
    }
}

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

void setDynamics() {

    Dynamics::setAll(0.f);
    
    for (size_t i = 0; i<Config::nHue;i++) {
        Dynamics::set(i,i,-randomFloat(0.f,.6f)-.4f);
        for (size_t j = 1; j<=i; j++) {
            float v = randomFloat(-.5,.5);
            Dynamics::set(i,i-j,v+randomFloat(-.3f,.3f));
            Dynamics::set(i-j,i,-v+randomFloat(-.3f,.3f));
        }
    }
    Dynamics::PrintForceMatrix();
}

int  main() { 
    sf::Clock clock;
    float time = clock.getElapsedTime().asSeconds();

    sf::Font font;
    sf::Text text("",font,12);

    if (!font.loadFromFile("fonts/tech.ttf")) {
        std::cerr << "Font not found";
        exit(-1);
    }

    setDynamics();
    // Particle::PrintGridDistribution();

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

        updatePhysics(Particle::ParticleVec, dt);
        updateScene(Particle::ParticleVec, dt);
        // Particle::ParticleVec[100]->print();
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
