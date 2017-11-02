#ifndef SDL2UTILS_POINTERS_H
#define SDL2UTILS_POINTERS_H

#include <memory>

#include "deleters.h"

namespace sdl2utils
{    
    using std::unique_ptr;
    using std::shared_ptr;
    
    using SDL_WindowPtr     = unique_ptr<SDL_Window, SDL2PtrDeleter>;
    using SDL_RendererPtr   = unique_ptr<SDL_Renderer, SDL2PtrDeleter>;
    using SDL_TexturePtr    = unique_ptr<SDL_Texture, SDL2PtrDeleter>;
    using SDL_SurfacePtr    = unique_ptr<SDL_Surface, SDL2PtrDeleter>;
    
    using TTF_FontPtr       = unique_ptr<TTF_Font, TTFPtrDeleter>;
}

#endif /* SDL2UTILS_POINTERS_H */
