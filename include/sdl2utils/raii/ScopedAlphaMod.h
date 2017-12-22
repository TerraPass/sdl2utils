#ifndef SDL2UTILS_RAII_SCOPEDALPHAMOD_H
#define SDL2UTILS_RAII_SCOPEDALPHAMOD_H

#include <SDL.h>

#include "../guards.h"

namespace sdl2utils
{
    namespace raii
    {
        class ScopedAlphaMod final
        {
            SDL_Texture* const ptexture;
            const Uint8 oldValue;

        public:
            ScopedAlphaMod(SDL_Texture* const ptexture, const Uint8 newValue)
            : ptexture(ptexture), oldValue(getAlphaMod(ptexture))
            {
                sdl2utils::guards::abbr::z(SDL_SetTextureAlphaMod(ptexture, newValue));
            }

            ~ScopedAlphaMod()
            {
                // Not guarding since destructors mustn't throw
                SDL_SetTextureAlphaMod(ptexture, oldValue);
            }

        private:
            inline static Uint8 getAlphaMod(SDL_Texture* const ptexture)
            {
                Uint8 value = 0xFF;
                sdl2utils::guards::abbr::z(SDL_GetTextureAlphaMod(ptexture, &value));
                return value;
            }
        };
    }
}

#endif /* SDL2UTILS_RAII_SCOPEDALPHAMOD_H */
