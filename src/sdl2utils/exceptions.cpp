#include "../../include/sdl2utils/exceptions.h"

#include <cassert>

#include <boost/format.hpp>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>

namespace sdl2utils
{
    SDL2Exception::~SDL2Exception() = default;

    SDLErrorException::SDLErrorException(const string& sdlError, const string& details)
        : SDL2Exception(
            boost::str(
                boost::format(MESSAGE_TEMPLATE)
                    % sdlError
                    % details
            )
        ),
        sdlError(sdlError), details(details)
    {
        // Using assert here, instead of throwing an exception, 
        // to avoid an if check in release build, as well as 
        // to indicate that providing an empty SDL error string
        // is a logic error.
        assert(
            !this->sdlError.empty() 
                && "Constructing SDLErrorException with empty SDL error string (maybe an extraneous call to SDL_ClearError() was made?)"
        );
    }
    
    SDLErrorException::SDLErrorException(bool clearError, const string& details)
        : SDLErrorException(
            static_cast<string>(SDL_GetError()),
            details
        )
    {
        if(clearError)
        {
            SDL_ClearError();
        }
    }

    SDLExtensionLibraryException::SDLExtensionLibraryException(const string& extensionLibraryName, const string& details)
        : SDL2Exception(
            boost::str(
                boost::format(MESSAGE_TEMPLATE)
                    % extensionLibraryName
                    % details
            )
        ), extensionLibraryName(extensionLibraryName), details(details)
    {
        
    }
    
    SDLImageExtException::SDLImageExtException(bool clearError, const string& details)
        : SDLExtensionLibraryException(
            EXTENSION_LIBRARY_NAME,
            boost::str(
                boost::format(PARENT_DETAILS_FORMAT)
                    % IMG_GetError()
                    % details
            )
        )
    {
        if(clearError)
        {
            // TODO: See if using SDL_ClearError() to clear SDL_image errors is acceptable.
            SDL_ClearError();
        }
    }
}
