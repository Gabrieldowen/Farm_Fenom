#include <iostream>
#include <SDL2/SDL.h>

using namespace std;


int main() {

    if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
        cout << "SDL_Init failed: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    cout << "Hello, World!" << endl;
    cout << "This is a simple C++ program." << endl;

    return EXIT_SUCCESS;
}