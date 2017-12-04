#ifndef SDL2UTILS_SCOPEDSDLMIXEREXT_H
#define SDL2UTILS_SCOPEDSDLMIXEREXT_H

#include <SDL_mixer.h>

#include "../exceptions.h"

namespace sdl2utils
{
    namespace raii
    {
        class ScopedSDLMixerExt final
        {
        private:
            bool isOwner;
            int initFlags;

        public:
            explicit inline ScopedSDLMixerExt(const int mandatoryFlags)
                : isOwner(true), initFlags(0)
            {
                if(mandatoryFlags != 0 && Mix_Init(mandatoryFlags) != mandatoryFlags)
                {
                    IMG_Quit();
                    //throw SDLImageExtException(true, "ScopedSDLImageExt failed to init SDL_image with mandatory flags");
                    throw SDLErrorException(true, "Mix_Init() with specified mandatory flags in ScopedSDLMixerExt ctor has failed");
                }
                else
                {
                    this->initFlags = mandatoryFlags;
                }
            }

            // Copy constructor and assignment are deleted
            ScopedSDLMixerExt(const ScopedSDLMixerExt& other) = delete;
            ScopedSDLMixerExt& operator=(const ScopedSDLMixerExt& other) = delete;
            
            // Move constructor
            inline ScopedSDLMixerExt(ScopedSDLMixerExt&& other)
                : isOwner(true), initFlags(other.initFlags)
            {
                other.isOwner = false;
            }
            
            // Move assignment
            inline ScopedSDLMixerExt& operator=(ScopedSDLMixerExt&& other)
            {
                this->isOwner = true;
                other.isOwner = false;
                this->initFlags = other.initFlags;
                return (*this);
            }
                
            inline ~ScopedSDLMixerExt()
            {
                if(this->isOwner)
                {
                    Mix_Quit();
                }
            }
        };
    }
}

#endif /* SDL2UTILS_SCOPEDSDLMIXEREXT_H */

