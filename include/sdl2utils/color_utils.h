#ifndef SDL2UTILS_COLOR_UTILS_H
#define SDL2UTILS_COLOR_UTILS_H

#include <SDL2/SDL.h>

namespace sdl2utils
{
    /**
     * Calculates linear interpolation by a certain amount between colors,
     * represented as SDL_Color structs.
     * In cases when amount is negative or bigger than 1,
     * resulting component values are capped at 0 - 255, instead of overflowing.
     * 
     * @param a Min color (corresponds to 0).
     * @param b Max color (corresponds to 1).
     * @param amount Lerp amount. May be any real value.
     * @return 
     */
    SDL_Color lerp(const SDL_Color& a, const SDL_Color& b, double amount);
}

#endif /* SDL2UTILS_COLOR_UTILS_H */

