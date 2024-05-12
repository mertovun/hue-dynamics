#pragma once
#include <array>
#include <vector>

class Dynamics {
    static std::vector<std::vector<float>> matrix;
public:
    static void setAllRandom();
    static void setAll(float);
    static void setDiag(float);
    static void set(int,int,float);
    static void invert();
    static void shiftForward();
    static void shiftBackward();

    static void PrintForceMatrix();

    static std::array<float, 2> calculateForce(int hueA, int hueB, float dx, float dy);
};
