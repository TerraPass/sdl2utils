#ifndef SCOPEDSDLIMAGEEXT_H
#define SCOPEDSDLIMAGEEXT_H

#include "../exceptions.h"

namespace sdl2utils
{
    namespace raii
    {
        class ScopedSDLImageExt final
        {
        private:
            bool isOwner;
            int initFlags;

        public:
            explicit inline ScopedSDLImageExt(const int mandatoryFlags = 0)
                : isOwner(true), initFlags(0)
            {
                if(mandatoryFlags != 0 && IMG_Init(mandatoryFlags) != mandatoryFlags)
                {
                    IMG_Quit();
                    throw SDLImageExtException(true, "ScopedSDLImageExt failed to init SDL_image with mandatory flags");
                }
                else
                {
                    this->initFlags = mandatoryFlags;
                }
            }

            // Copy constructor and assignment are deleted
            ScopedSDLImageExt(const ScopedSDLImageExt& other) = delete;
            ScopedSDLImageExt& operator=(const ScopedSDLImageExt& other) = delete;
            
            // Move constructor
            inline ScopedSDLImageExt(ScopedSDLImageExt&& other)
                : isOwner(true)
            {
                other.isOwner = false;
            }
            
            // Move assignment
            inline ScopedSDLImageExt& operator=(ScopedSDLImageExt&& other)
            {
                this->isOwner = true;
                other.isOwner = false;
                return (*this);
            }
                
            inline ~ScopedSDLImageExt()
            {
                if(this->isOwner)
                {
                    IMG_Quit();
                }
            }
            
            inline int getInitializedImageFormatFlags() const
            {
                return this->initFlags;
            }

            inline int tryInitializeImageFormats(const int flags)
            {
                this->initFlags = IMG_Init(flags);
                return this->initFlags;
            }
        };
    }
}

#endif /* SCOPEDSDLIMAGEEXT_H */
