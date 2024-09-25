#include "Entity.hpp"
#include "Math.hpp"


Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int p_spriteScale)
:pos(p_pos), tex(p_tex), spriteScale(p_spriteScale)
{   
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;


}

