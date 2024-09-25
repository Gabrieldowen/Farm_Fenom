#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"

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
    SDL_Texture* topDirtTexture = window.loadTexture("res/images/top_dirt_layer.png");


    std::vector<Entity> topSoil = {};

    for(int i = 0; i <WINDOW_WIDTH; i += 32){
        topSoil.push_back(Entity(i, WINDOW_HEIGHT/4 - 32, topDirtTexture));
    }

    bool isRunning = true;
    SDL_Event event;

    // GAME LOOP
    while(isRunning){
        // get controls and events
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                isRunning = false;
            }
            
        }

        window.clear();
        

        for(Entity& e : topSoil){
            window.render(e);
        }

        window.display();


    }



    // clean up
    window.cleanUp();
    SDL_Quit();

    cout << "Program executed" << endl;
    return EXIT_SUCCESS;
}