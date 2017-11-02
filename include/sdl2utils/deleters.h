#ifndef SDL2UTILS_DELETERS_H
#define SDL2UTILS_DELETERS_H

#include <SDL.h>
#include <SDL_ttf.h>

namespace sdl2utils
{
    struct SDL2PtrDeleter
    {
        inline void operator()(SDL_Window* pwindow) const
        {
            SDL_DestroyWindow(pwindow);
        }

        inline void operator()(SDL_Renderer* prenderer) const
        {
            SDL_DestroyRenderer(prenderer);
        }
        
        inline void operator()(SDL_Texture* ptexture) const
        {
            SDL_DestroyTexture(ptexture);
        }
        
        inline void operator()(SDL_Surface* psurface) const
        {
            SDL_FreeSurface(psurface);
        }
    };
    
    struct TTFPtrDeleter
    {
        inline void operator()(TTF_Font* pfont) const
        {
            TTF_CloseFont(pfont);
        }
    };
}

#endif /* SDL2UTILS_DELETERS_H */
