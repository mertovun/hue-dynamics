#pragma once

class Config {
public:
    static const int wWidth;
    static const int wHeight;
    static const float radius;
    static const float lightness;
    static const float saturation;
    static const int nHue;
    static const int alpha;
    static const float vMax;
    static const float rMin;
    static const float rMax;
    static const int n;

    // Disallow creating an instance of Config
    Config() = delete;
};

