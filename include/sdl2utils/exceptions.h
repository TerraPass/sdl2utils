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
         * @param clearError If true, invokes clears SDL error after initializing exception.
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
}

#endif /* EXCEPTIONS_H */

