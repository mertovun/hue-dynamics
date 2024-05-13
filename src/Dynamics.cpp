#include "Dynamics.h"
#include "Config.h"
#include "Util.h"
#include <cmath>
#include <iostream>

std::vector<std::vector<float>> Dynamics::matrix;

void Dynamics::setAllRandom() {
    matrix.resize(Config::nHue, std::vector<float>(Config::nHue));
    for (auto& row:matrix) {
        for (auto & element:row) {
            element = randomFloat(-1.f,1.f);
        }
    }
}

void Dynamics::setAll(float x) {
    matrix.resize(Config::nHue, std::vector<float>(Config::nHue));
    for (auto& row:matrix) {
        for (auto & element:row) {
            element = x;
        }
    }
}

void Dynamics::setDiag(float x) {
    for (size_t i = 0; i<matrix.size();i++) {
        matrix[i][i] = x;
    }
}

void Dynamics::set(int i, int j, float x) {
    matrix[i][j] = x;
}

void Dynamics::invert() {
    for (auto& row: matrix) {
        for (auto& element: row) {
            element *= -1.f;
        }
    }
}

void Dynamics::shiftForward() {
    std::vector<std::vector<float>> new_matrix(Config::nHue, std::vector<float>(Config::nHue));

    for (int i = 0; i < Config::nHue; ++i) {
        for (int j = 0; j < Config::nHue; ++j) {
            new_matrix[(i + 1) % Config::nHue][(j + 1) % Config::nHue] = matrix[i][j];
        }
    }

    matrix = new_matrix;
}

void Dynamics::shiftBackward() {
    std::vector<std::vector<float>> new_matrix(Config::nHue, std::vector<float>(Config::nHue));

    for (int i = 0; i < Config::nHue; ++i) {
        for (int j = 0; j < Config::nHue; ++j) {
            new_matrix[(i - 1 + Config::nHue) % Config::nHue][(j - 1 + Config::nHue) % Config::nHue] = matrix[i][j];
        }
    }

    matrix = new_matrix;
}

void Dynamics::PrintForceMatrix() {
    for (size_t i = 0; i<Config::nHue; ++i) {
        for (size_t j = 0; j<Config::nHue; ++j) {
            std::cout << Dynamics::matrix[i][j]<< " ";
        }
        std::cout << "\n";
    }
}

std::array<float, 2> Dynamics::calculateForce(int hueA, int hueB, float dx, float dy) {
    float fMax = matrix[hueA][hueB];
    float distSq = dx*dx+dy*dy;
    float rMid = (Config::rMin + Config::rMax)/2.f;

    float fMagnitude;

    if (distSq <= Config::rMin*Config::rMin) {
        fMagnitude = lerp(1.f,0.f,std::sqrt(distSq)/Config::rMin);
    }
    else if (distSq <= rMid*rMid) {
        fMagnitude = lerp(0.f,fMax,(std::sqrt(distSq)-Config::rMin)/(rMid-Config::rMin));
    }
    else if (distSq <= Config::rMax*Config::rMax) {
        fMagnitude = lerp(fMax,0.f,(std::sqrt(distSq)-rMid)/(Config::rMax-rMid));
    }
    else fMagnitude = 0.f;

    fMagnitude *= Config::fMul;

    float theta = std::atan2(dy,dx);
    float fx = std::cos(theta)*fMagnitude;
    float fy = std::sin(theta)*fMagnitude;

    return {fx,fy};
}
