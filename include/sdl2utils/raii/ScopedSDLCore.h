#ifndef SDL2UTILS_SCOPEDINIT_H
#define SDL2UTILS_SCOPEDINIT_H

#include <SDL.h>

#include "../exceptions.h"

namespace sdl2utils
{
    namespace raii
    {

        class ScopedSDLCore final
        {
        private:
            // There must be only one ScopedSDLSystem instance,
            // which is allowed to call SDL_Quit() on destruction.
            // This flag starts as true for a new instance and
            // is set to false if it's moved from.
            bool isOwner;
            
        public:
            static constexpr const Uint32 DEFAULT_INIT_FLAGS = SDL_INIT_EVERYTHING;

            explicit inline ScopedSDLCore(const Uint32 initFlags = DEFAULT_INIT_FLAGS)
                : isOwner(true)
            {
                if(SDL_Init(initFlags) < 0)
                {
                    //throw SDLInitFailedException();
                    throw SDLErrorException(true, "SDL_Init() in ScopedSDLCore ctor has failed");
                }
            }
            
            // Copy constructor and assignment are deleted
            ScopedSDLCore(const ScopedSDLCore& other) = delete;
            ScopedSDLCore& operator=(const ScopedSDLCore& other) = delete;
            
            // Move constructor
            inline ScopedSDLCore(ScopedSDLCore&& other)
                : isOwner(true)
            {
                other.isOwner = false;
            }
            
            // Move assignment
            inline ScopedSDLCore& operator=(ScopedSDLCore&& other)
            {
                this->isOwner = true;
                other.isOwner = false;
                return (*this);
            }
            
            inline ~ScopedSDLCore()
            {
                SDL_Quit();
            }

            inline Uint32 getInitSubsystemsMask() const
            {
                return SDL_WasInit(0);
            }

            inline void initSubsystems(const Uint32 initFlags)
            {
                if(SDL_InitSubSystem(initFlags) < 0)
                {
                    throw SDLInitFailedException();
                }
            }
            
            inline void deinitSubsystems(const Uint32 initFlags)
            {
                SDL_QuitSubSystem(initFlags);
            }
        };
    }
}

#endif /* SDL2UTILS_SCOPEDINIT_H */

