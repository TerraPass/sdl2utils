#ifndef SCOPEDRENDERTARGET_H
#define SCOPEDRENDERTARGET_H

#include <SDL.h>

#include "../guards.h"

namespace sdl2utils
{
    namespace raii
    {
        using namespace sdl2utils::guards::abbr;
        
        class ScopedRenderTarget final
        {
            SDL_Renderer* const prenderer;
            SDL_Texture* const poldTarget;

        public:
            ScopedRenderTarget(SDL_Renderer* const prenderer, SDL_Texture* const pnewTarget)
                : prenderer(prenderer), poldTarget(SDL_GetRenderTarget(this->prenderer))
            {
                z(SDL_SetRenderTarget(prenderer, pnewTarget));
            }

            ~ScopedRenderTarget()
            {
                // Not guarding, since destructors mustn't throw
                SDL_SetRenderTarget(prenderer, poldTarget);
            }

        private:
            ScopedRenderTarget(const ScopedRenderTarget&) = delete;
            ScopedRenderTarget& operator=(const ScopedRenderTarget&) = delete;
        };
    }
}

#endif /* SCOPEDRENDERTARGET_H */

