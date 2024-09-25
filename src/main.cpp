#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Utils.hpp"

using namespace std;

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;


int main(int argv, char* args[]) {

    cout << "Testing if libraries can be initialized" << endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
        cout << "SDL_Init failed: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        cout << "SDL_Init failed: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    // LOAD IN ITEMS
    RenderWindow window("SDL2 with C++ game", WINDOW_WIDTH, WINDOW_HEIGHT);

    // load images
    SDL_Texture* topDirtTexture = window.loadTexture("res/images/top_dirt_layer.png");
    SDL_Texture* skyTexture = window.loadTexture("res/images/sky.png");
    SDL_Texture* strawBarryTexture = window.loadTexture("res/images/straw_barry.png");



    //create entitites with the images/textures
    std::vector<Entity> topSoil = {};
    for(int i = 0; i <WINDOW_WIDTH; i += 32){
        topSoil.push_back(Entity(Vector2f(i, WINDOW_HEIGHT/4 - 32), topDirtTexture));
    }

    Entity sky(Vector2f(0, 0), skyTexture, 128);

    Entity strawBarry(Vector2f(32, WINDOW_HEIGHT/4 - 64), strawBarryTexture);




    // start game loop logic
    bool isRunning = true;

    SDL_Event event;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();

    // GAME LOOP
    while(isRunning){
        
        int startTicks = SDL_GetTicks();
        float newTime = utils::hireTimeInSeconds();
        float framteTime = newTime - currentTime;
        
        currentTime = newTime;

        accumulator += framteTime;

        while(accumulator >= timeStep){
 
            // get controls and events
            while(SDL_PollEvent(&event)){

                switch( event.type ){
                    case SDL_QUIT:
                        isRunning = false;
                        break;

                    /* Look for a keypress */
                    case SDL_KEYDOWN:
                        /* Check the SDLKey values and move change the coords */
                        Vector2f v = strawBarry.getPos();

                        switch( event.key.keysym.sym ){
                            case SDLK_LEFT:
                                v.x -= 2;
                                strawBarry.setPos(v);
                                break;
                            case SDLK_RIGHT:
                                v.x += 2;
                                strawBarry.setPos(v);
                                break;
                            case SDLK_UP:
                                break;
                            case SDLK_DOWN:
                                break;
                            default:
                                break;
                        }
                        break;
                }
            
                
            }
            accumulator -= timeStep;
        }
        // gets the remainder
        // const float alpha = accumulator / timeStep;


        window.clear();
        

        // render objects
        window.render(sky);

        for(Entity& e : topSoil){
            window.render(e);
        }

        window.render(strawBarry);
        

        // std::cout << utils::hireTimeInSeconds() << std::endl;

        window.display();


        int frameTicks = SDL_GetTicks() - startTicks;
        if(frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay( 1000 / window.getRefreshRate() - frameTicks);

    }



    // clean up
    window.cleanUp();
    SDL_Quit();

    cout << "Program executed" << endl;
    return EXIT_SUCCESS;
}