#include "Util.h"
#include <random>

std::mt19937* getGenerator() {
    static std::random_device rd; 
    static std::mt19937 gen(rd()); 
    return &gen;
}

float HueToRGB(float p, float q, float t){
    if(t < 0.0f) t += 1.0f;
    if(t > 1.0f) t -= 1.0f;
    if(t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
    if(t < 1.0f / 2.0f) return q;
    if(t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
    return p;
}

void HSLToRGB(float h, float s, float l, int& r, int& g, int& b){
    float q, p;

    if(s == 0.0f){
        r = g = b = static_cast<int>(l * 255.0f);
    } else {
        q = l < 0.5f ? l * (1 + s) : l + s - l * s;
        p = 2 * l - q;
        r = static_cast<int>(255.0f * HueToRGB(p, q, h + 1.0f / 3.0f));
        g = static_cast<int>(255.0f * HueToRGB(p, q, h));
        b = static_cast<int>(255.0f * HueToRGB(p, q, h - 1.0f / 3.0f));
    }
}

int randomInt(int a, int b) {
    std::uniform_int_distribution<> distr(a, b - 1); 
    return distr(*getGenerator()); 
}

float randomFloat(float a, float b) {
    std::uniform_real_distribution<> distr(a, b); 
    return distr(*getGenerator()); 
}

