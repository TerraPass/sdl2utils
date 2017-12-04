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
            explicit inline ScopedSDLMixerExt(
                const int frequency,
                const Uint16 format,
                const int channels,
                const int chunksize,
                const int mandatoryInitFlags
            )
            : isOwner(true), initFlags(0)
            {
                if(Mix_OpenAudio(frequency, format, channels, chunksize) < 0)
                {
                    throw SDLErrorException(true, "Mix_OpenAudio() in ScopedSDLMixerExt ctor has failed");
                }

                // if(mandatoryInitFlags != 0 && Mix_Init(mandatoryInitFlags) != mandatoryInitFlags)
                // {
                    // IMG_Quit();
                    // //throw SDLImageExtException(true, "ScopedSDLImageExt failed to init SDL_image with mandatory flags");
                    // throw SDLErrorException(true, "Mix_Init() with specified mandatory flags in ScopedSDLMixerExt ctor has failed");
                // }
                // else
                // {
                    // this->initFlags = mandatoryInitFlags;
                // }
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
                    //Mix_Quit();
                    Mix_CloseAudio();
                }
            }
        };
    }
}

#endif /* SDL2UTILS_SCOPEDSDLMIXEREXT_H */

