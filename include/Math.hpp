#pragma once 

#include <iostream>
#include <cmath>

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
        std::cout << x << ", " << y << std::endl;
    }

    void add(Vector2f p_v){
        x += p_v.x;
        y += p_v.y;
    }
    
    Vector2f mult(float s){
        return Vector2f(x*s, y*s);
    }

    void normalize(){
        float length = std::sqrt(x * x + y * y);
        if(length != 0){
            x /= length;
            x /= length;
        }
    }

    float x, y;
};  