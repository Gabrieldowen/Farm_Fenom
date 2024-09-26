#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "Settings.hpp"

using namespace std;



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
    SDL_Texture* playerOneTexture = window.loadTexture("res/images/player_1.png");
    SDL_Texture* cloudTexture = window.loadTexture("res/images/cloud.png");




    //create entitites with the images/textures
    std::vector<Entity> topSoil = {};
    for(int i = 0; i <WINDOW_WIDTH; i += 32){
        topSoil.push_back(Entity(Vector2f(i, GROUND_TOP), topDirtTexture));
    }

    Entity sky(Vector2f(0, 0), skyTexture, 128);

    Player player1(Vector2f(32, WINDOW_HEIGHT/4 - 64), playerOneTexture);

    Entity cloud(Vector2f(4, 4), cloudTexture, 8);





    // start game loop logic
    bool isRunning = true;

    SDL_Event event;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();

    int frameCount = 0;

    // GAME LOOP
    while(isRunning){
        
        int startTicks = SDL_GetTicks();
        float newTime = utils::hireTimeInSeconds();
        float deltaTime = newTime - currentTime;


        currentTime = newTime;

        accumulator += deltaTime;


        while(accumulator >= timeStep){
 
            // get controls and events
            while(SDL_PollEvent(&event)){

                switch( event.type ){
                    case SDL_QUIT:
                        isRunning = false;
                        break;
                }
            
                
            }
            accumulator -= timeStep;
        }
        // gets the remainder
        // const float alpha = accumulator / timeStep;

        // Get the current state of the keyboard
        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        // Move the character based on key presses
        if (keystates[SDL_SCANCODE_W]) {  // Move up
            player1.update(deltaTime, Vector2f(0, -1));
        }
        if (keystates[SDL_SCANCODE_S]) {  // Move down
            player1.update(deltaTime, Vector2f(0, 1));
        }
        if (keystates[SDL_SCANCODE_A]) {  // Move left
            player1.update(deltaTime, Vector2f(-1, 0));
            if (frameCount % 10 == 0){
                player1.setCurrentFrameY(0);
                player1.setCurrentFrameX((player1.getCurrentFrame().x + 32)%224);
            }
        }
        if (keystates[SDL_SCANCODE_D]) {  // Move right
            player1.update(deltaTime, Vector2f(1, 0));

            if (frameCount % 10 == 0){
                player1.setCurrentFrameY(32);
                player1.setCurrentFrameX((player1.getCurrentFrame().x + 32)%224);
            }
        }
    



        window.clear();
        

        // render objects
        window.render(sky);

        for(Entity& e : topSoil){
            window.render(e);
        }

        window.render(cloud);

        window.render(player1);
        


        window.display();


        int frameTicks = SDL_GetTicks() - startTicks;
        if(frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay( 1000 / window.getRefreshRate() - frameTicks);

        frameCount++;

    }



    // clean up
    window.cleanUp();
    SDL_Quit();

    cout << "Program executed" << endl;
    return EXIT_SUCCESS;
}