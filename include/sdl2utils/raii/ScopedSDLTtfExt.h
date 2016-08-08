#ifndef SDL2UTILS_SCOPEDSDLTTFEXT_H
#define SDL2UTILS_SCOPEDSDLTTFEXT_H

#include <SDL2/SDL_ttf.h>

#include "../exceptions.h"

namespace sdl2utils
{
    namespace raii
    {
        class ScopedSDLTtfExt final
        {
        private:
            bool isOwner;

        public:
            explicit inline ScopedSDLTtfExt()
                : isOwner(true)
            {
                if(TTF_Init() < 0)
                {
                    //throw SDLImageExtException(true, "ScopedSDLTtfExt failed to init SDL_ttf");
                    throw SDLErrorException(true, "TTF_Init() in ScopedSDLTtfExt ctor has failed");
                }
            }

            // Copy constructor and assignment are deleted
            ScopedSDLTtfExt(const ScopedSDLTtfExt& other) = delete;
            ScopedSDLTtfExt& operator=(const ScopedSDLTtfExt& other) = delete;
            
            // Move constructor
            inline ScopedSDLTtfExt(ScopedSDLTtfExt&& other)
                : isOwner(true)
            {
                other.isOwner = false;
            }
            
            // Move assignment
            inline ScopedSDLTtfExt& operator=(ScopedSDLTtfExt&& other)
            {
                this->isOwner = true;
                other.isOwner = false;
                return (*this);
            }
                
            inline ~ScopedSDLTtfExt()
            {
                if(this->isOwner)
                {
                    TTF_Quit();
                }
            }
        };
    }
}

#endif /* SDL2UTILS_SCOPEDSDLTTFEXT_H */

