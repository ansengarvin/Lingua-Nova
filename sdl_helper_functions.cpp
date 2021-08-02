#include "SDL.h"
#include "sdl_helper_functions.h"


SDL_Texture* loadTexture(std::string path) {

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedsurface == NULL) {

        printf( "Unjable to load image %s! SDL Error: %s\n", path.c_str(), IMG_geterror() );

    }

}