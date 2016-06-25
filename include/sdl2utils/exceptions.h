#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace sdl2utils
{
    using std::string;
    using std::runtime_error;
    
    class SDL2Exception : public runtime_error
    {
    private:
        constexpr static const auto DEFAULT_MESSAGE = "Unknown SDL related error has occurred";

    public:
        explicit SDL2Exception(const string& message = DEFAULT_MESSAGE)
            : runtime_error(message)
        {
            
        }

        virtual ~SDL2Exception() = 0;
    };
    
    class SDLErrorException : public SDL2Exception
    {
    private:
        constexpr static const auto MESSAGE_TEMPLATE    = "SDL error occurred: %1% (%2%)";
        constexpr static const auto DEFAULT_DETAILS     = "no details available";

        const string sdlError;
        const string details;
        
    public:
        /**
         * Uses SDL_GetError() to initialize exception message, 
         * then invokes SDL_ClearError() if passed true as the 2nd parameter.
         * 
         * @param clearError If true, clears SDL error after initializing exception.
         * Defaults to true.
         * @param details Details as to what operation may have caused the error.
         */
        explicit SDLErrorException(bool clearError = true, const string& details = DEFAULT_DETAILS);
        
        /**
         * Initializes the exception with the provided SDL error string.
         * Does not invoke SDL_ClearError().
         * 
         * @param sdlError SDL error string (such as the one produced by SDL_GetError()). Must not be empty.
         * @param details Details as to what operation may have caused the error.
         */
        explicit SDLErrorException(const string& sdlError, const string& details = DEFAULT_DETAILS);

        virtual ~SDLErrorException() = default;

        inline const string& getSdlError() const
        {
            return this->sdlError;
        }

        inline const string& getDetails() const
        {
            return this->details;
        }
    };

    class SDLInitFailedException : public SDLErrorException
    {
        using SDLErrorException::SDLErrorException;
    };

    class SDLExtensionLibraryException : public SDL2Exception
    {
    protected:
        constexpr static const auto DEFAULT_DETAILS     = "No details available";

    private:
        constexpr static const auto MESSAGE_TEMPLATE    = "Error in SDL extension library %1%: %2%";

        const string extensionLibraryName;
        const string details;

    public:
        explicit SDLExtensionLibraryException(const string& extensionLibraryName, const string& details = DEFAULT_DETAILS);

        virtual ~SDLExtensionLibraryException() = default;

        inline const string& getExtensionLibraryName()
        {
            return this->extensionLibraryName;
        }
        
        inline const string& getDetails() const
        {
            return this->details;
        }
    };
    
    class SDLImageExtException : public SDLExtensionLibraryException
    {
    private:
        static constexpr const auto EXTENSION_LIBRARY_NAME = "SDL_image";

        static constexpr const auto PARENT_DETAILS_FORMAT = "%1% (%2%)";

    public:
        /**
         * Uses IMG_GetError() to initialize exception message, 
         * then invokes IMG_ClearError() if passed true as the 2nd parameter.
         * 
         * @param clearError If true, clears SDL_image error after initializing exception.
         * Defaults to true.
         * @param details Details as to what operation may have caused the error.
         */
        explicit SDLImageExtException(bool clearError = true, const string& details = DEFAULT_DETAILS);
    };
}

#endif /* EXCEPTIONS_H */

