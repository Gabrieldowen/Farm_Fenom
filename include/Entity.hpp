#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"

class Entity
{
    public:
        Entity(Vector2f p_pos, SDL_Texture* p_tex, int p_spriteScale = 4);

        Vector2f& getPos(){
            return pos;
        }


        SDL_Texture* getTex(){
            return tex;
        }

        SDL_Rect getCurrentFrame(){
            return currentFrame;
        }

        int getSpriteScale(){
            return spriteScale;
        }

        void setPos(Vector2f newPos){
            pos = newPos;
        }


    private:
        Vector2f pos;
        SDL_Rect currentFrame;
        SDL_Texture* tex;
        int spriteScale;

};