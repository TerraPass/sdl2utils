#ifndef SDL2UTILS_RAII_SCOPEDCOLORMOD_H
#define SDL2UTILS_RAII_SCOPEDCOLORMOD_H

#include <tuple>

#include <SDL.h>

#include "../guards.h"

namespace sdl2utils
{
    namespace raii
    {
        class ScopedColorMod final
        {
            using TripleU8 = std::tuple<Uint8, Uint8, Uint8>;

            SDL_Texture* const ptexture;
            const TripleU8 oldValues;

        public:
            ScopedColorMod(SDL_Texture* const ptexture, const Uint8 newr, const Uint8 newg, const Uint8 newb)
            : ptexture(ptexture), oldValues(getColorModValues(ptexture))
            {
                sdl2utils::guards::abbr::z(SDL_SetTextureColorMod(ptexture, newr, newg, newb));
            }

            ~ScopedColorMod()
            {
                // Not guarding since destructors mustn't throw
                SDL_SetTextureColorMod(ptexture, std::get<0>(oldValues), std::get<1>(oldValues), std::get<2>(oldValues));
            }

        private:
            inline static TripleU8 getColorModValues(SDL_Texture* const ptexture)
            {
                TripleU8 values;
                sdl2utils::guards::abbr::z(SDL_GetTextureColorMod(ptexture, &(std::get<0>(values)), &(std::get<1>(values)), &(std::get<2>(values))));
                return values;
            }
        };
    }
}

#endif /* SDL2UTILS_RAII_SCOPEDCOLORMOD_H */
