#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"
#include "Settings.hpp"

class Entity
{
    public:
        Entity(Vector2f p_pos, SDL_Texture* p_tex, int p_spriteScale = 4);

        Vector2f getPos(){
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

        void setCurrentFrameX(int x){
            currentFrame.x = x;
        }
        void setCurrentFrameY(int y){
            currentFrame.y = y;
        }


        void update(float deltaTime, Vector2f direction){
            pos.x += direction.x * velocity * deltaTime;
            pos.y += direction.y * velocity * deltaTime;
        }



    protected:
        Vector2f pos;
        float velocity = 200.0f;
        SDL_Rect currentFrame;
        SDL_Texture* tex;
        int spriteScale;

};

class Player : public Entity {
    public:
        bool hasItem = false;


        Player(Vector2f p_pos, SDL_Texture* p_tex, int p_spriteScale = 4) : Entity(p_pos, p_tex, p_spriteScale) {
            std::cout << "player created" << std::endl;
        }   
    
        void update(float deltaTime, int frameCount){
            
            // move the player
            directionVector.normalize();
            pos.x += directionVector.x * velocity * deltaTime;
            pos.y += directionVector.y * velocity * deltaTime;

            // bounds for the player
            if(pos.x < 0) pos.x = 0;    //
            if(pos.x > WINDOW_WIDTH - currentFrame.w * getSpriteScale()) pos.x = (WINDOW_WIDTH - currentFrame.w * getSpriteScale());

            if(pos.y < GROUND_TOP - currentFrame.h * getSpriteScale()) pos.y = GROUND_TOP - currentFrame.h * getSpriteScale(); //
            if(pos.y > WINDOW_HEIGHT - currentFrame.h * getSpriteScale()) pos.y = (WINDOW_HEIGHT - currentFrame.h * getSpriteScale());

            // cycle through animation
            if (frameCount % 10 == 0){
                // switches animation based on direction
                if(directionVector.x > 0){
                    setCurrentFrameY(32);
                }
                else if(directionVector.x < 0){
                    setCurrentFrameY(0);
                }
                
                // if moving rotate
                if(directionVector.y != 0 || directionVector.x != 0){
                    setCurrentFrameX((getCurrentFrame().x + 32)%224);
                }
                else{
                    setCurrentFrameX(0);
                }
            }


            // reset direction vector after moving in that direction
            directionVector = Vector2f(0, 0);

        }

        void addDirectionVector(Vector2f v){
            directionVector.add(v);
        }

        private:
            Vector2f directionVector;
};

class Plant : public Entity {
    public:
        Plant(Vector2f p_pos, SDL_Texture* p_tex, int p_spriteScale = 4) : Entity(p_pos, p_tex, p_spriteScale) 
        {
        }   

    
};