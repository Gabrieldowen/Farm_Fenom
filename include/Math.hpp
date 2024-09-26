#pragma once 

#include <iostream>

struct Vector2f
{
    Vector2f()
    :x(0.0f), y(0.0f)
    {}

    Vector2f(float p_x, float p_y)
    :x(p_x), y(p_y)
    {}

    void print()
    {
        std::cout << x * 4<< ", " << y * 4 << std::endl;
    }

    void add(Vector2f p_v){
        x += p_v.x;
        y += p_v.y;
    }

    float x, y;
};  