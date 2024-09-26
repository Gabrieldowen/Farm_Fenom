#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"
#include "Settings.hpp"

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


        void update(float deltaTime, Vector2f direction){
            pos.x += direction.x * velocity * deltaTime;
            pos.y += direction.y * velocity * deltaTime;

        }



    protected:
        Vector2f pos;
        float velocity = 40.0f;
        SDL_Rect currentFrame;
        SDL_Texture* tex;
        int spriteScale;

};

class Player : public Entity {
    public:
        Player(Vector2f p_pos, SDL_Texture* p_tex, int p_spriteScale = 4) : Entity(p_pos, p_tex, p_spriteScale) {
            std::cout << "player created" << std::endl;
        }   
    
        void update(float deltaTime, Vector2f direction){
            pos.x += direction.x * velocity * deltaTime;
            pos.y += direction.y * velocity * deltaTime;

            if(pos.x < 0) pos.x = 0;    //
            if(pos.x > WINDOW_WIDTH / spriteScale - currentFrame.w) pos.x = (WINDOW_WIDTH / spriteScale - currentFrame.w);
            if(pos.y < GROUND_TOP - currentFrame.h) pos.y = GROUND_TOP - currentFrame.h; //
            if(pos.y > WINDOW_HEIGHT / spriteScale - currentFrame.h) pos.y = (WINDOW_HEIGHT / spriteScale - currentFrame.h);

            pos.print();

        }
};