#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cstdlib>


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
    SDL_Texture* sproutTexture = window.loadTexture("res/images/sprout_1.png");
    SDL_Texture* truckTexture = window.loadTexture("res/images/truck_1.png");
    SDL_Texture* carrotTexture = window.loadTexture("res/images/carrot.png");




    //create entitites with the images/textures
    std::vector<Entity> topSoil = {};
    for(int i = 0; i <WINDOW_WIDTH; i += 128){
        topSoil.push_back(Entity(Vector2f(i, GROUND_TOP), topDirtTexture));
    }

    std::vector<Plant> plants = {};
    plants.push_back(Plant(Vector2f(32,GROUND_TOP-32), sproutTexture, 2));
    plants.push_back(Plant(Vector2f(WINDOW_WIDTH-96, WINDOW_HEIGHT-96), sproutTexture, 2));



    Entity sky(Vector2f(0, 0), skyTexture, 128);
    Entity cloud(Vector2f(4, 4), cloudTexture, 8);
    Entity truck(Vector2f(WINDOW_WIDTH-192, WINDOW_HEIGHT - 224), truckTexture, 6);
    Entity carrot(Vector2f(-128, -128), carrotTexture);

    Player player1(Vector2f(SRES, GROUND_TOP - 128), playerOneTexture);




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

        // set character direction based on keys pressed
        if (keystates[SDL_SCANCODE_W]) player1.addDirectionVector(Vector2f(0, -1));

        if (keystates[SDL_SCANCODE_A]) player1.addDirectionVector(Vector2f(-1, 0));
        
        if (keystates[SDL_SCANCODE_S]) player1.addDirectionVector(Vector2f(0, 1));
        
        if (keystates[SDL_SCANCODE_D]) player1.addDirectionVector(Vector2f(1, 0));
        
        if(!keystates[SDL_SCANCODE_W] && !keystates[SDL_SCANCODE_A] && !keystates[SDL_SCANCODE_S] && !keystates[SDL_SCANCODE_D]){
            player1.addDirectionVector(Vector2f(0, 0));
        }

        if(keystates[SDL_SCANCODE_SPACE] && !player1.hasItem){
            for (size_t i = 0; i < plants.size(); ++i) {
                Plant& p = plants[i];
                
                
                // std::cout << "//" << p.getPos().x + SRES*p.getSpriteScale()/2 << ", " << p.getPos().y + SRES*p.getSpriteScale() << " vs "
                // << player1.getPos().x + SRES*player1.getSpriteScale()/2 << ", " <<player1.getPos().y + SRES*player1.getSpriteScale() << "//" << endl;
                // std::cout << endl;
                if(    p.getPos().x + SRES*p.getSpriteScale()/2 >= player1.getPos().x + SRES*player1.getSpriteScale()/2 - 25
                    && p.getPos().x + SRES*p.getSpriteScale()/2 <= player1.getPos().x + SRES*player1.getSpriteScale()/2 + 25
                    && p.getPos().y + SRES*p.getSpriteScale() >= player1.getPos().y + SRES*player1.getSpriteScale() - 25
                    && p.getPos().y + SRES*p.getSpriteScale() <= player1.getPos().y + SRES*player1.getSpriteScale() + 25){
                        // std::cout << "plant picked" << std::endl;
                        // p.getPos().print();
                        // player1.getPos().print();
                        plants.erase(plants.begin() + i);
                        player1.hasItem = true;
                    }
            }
        }
        if (keystates[SDL_SCANCODE_Q] && player1.hasItem){
            player1.hasItem = false;
        }


    
        player1.update(deltaTime, frameCount, carrot);

        //
        // SPAWN IN PLANTS
        // if(frameCount % 300 == 0){
        //     int randX = (rand() % (WINDOW_WIDTH/2 - 1)) + 0;
        //     int randY = (rand() % ((GROUND_TOP*2 + SRES) - (GROUND_TOP*2-SRES) + 1)) + (GROUND_TOP*2-SRES);

        //     std::cout << randX << ", " << randY << std::endl;

        //     plants.push_back(Plant(Vector2f(randX, randY), sproutTexture, 2));
        // }
        //
        //


        window.clear();
        

        // render objects
        window.render(sky);
        window.render(cloud);

        for(Entity& e : topSoil){
            window.render(e);
        }

        for(Plant& p : plants){
            window.render(p);
        }

        window.render(truck);
        window.render(carrot);
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