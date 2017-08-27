#ifndef SCOPEDRENDERCOLOR_H
#define SCOPEDRENDERCOLOR_H

#include <SDL.h>

#include "../guards.h"

namespace sdl2utils
{
    namespace raii
    {
        using namespace sdl2utils::guards::abbr;

        class ScopedRenderDrawColor final
        {
            SDL_Renderer* const prenderer;
            const SDL_Color oldColor;

        public:
            ScopedRenderDrawColor(SDL_Renderer* const prenderer, const SDL_Color& newColor)
                : prenderer(prenderer), oldColor(getRendererDrawColor(prenderer))
            {
                z(SDL_SetRenderDrawColor(this->prenderer, newColor.r, newColor.g, newColor.b, newColor.a));
            }

            ~ScopedRenderDrawColor()
            {
                // Not guarding, since destructors mustn't throw
                SDL_SetRenderDrawColor(prenderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);
            }

        private:
            ScopedRenderDrawColor(const ScopedRenderDrawColor&) = delete;
            ScopedRenderDrawColor& operator=(const ScopedRenderDrawColor&) = delete;

            static inline SDL_Color getRendererDrawColor(SDL_Renderer* const prenderer)
            {
                using namespace sdl2utils::guards::abbr;

                SDL_Color result;
                z(SDL_GetRenderDrawColor(prenderer, &(result.r), &(result.g), &(result.b), &(result.a)));
                return result;
            }
        };
    }
}

#endif /* SCOPEDRENDERCOLOR_H */

