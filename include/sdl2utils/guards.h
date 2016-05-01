#ifndef SDL2UTILS_ERROR_UTILS_H
#define SDL2UTILS_ERROR_UTILS_H

#include <string>

#include "exceptions.h"

namespace sdl2utils
{
    namespace guards
    {
        using std::string;

        enum class SuccessCondition
        {
            ZERO    = 0,
            NONZERO = 1
        };

        namespace detail
        {
            template<SuccessCondition Cond>
            struct EnsureErrorDetailMessage
            {
                constexpr static const auto value = "detected by an sdl2utils::guards::ensure<Cond> check";
            };

            template<>
            struct EnsureErrorDetailMessage<SuccessCondition::ZERO>
            {
                constexpr static const auto value = "sdl2utils::guards::ensure<ZERO> detected a non-zero return code";
            };
            
            template<>
            struct EnsureErrorDetailMessage<SuccessCondition::NONZERO>
            {
                constexpr static const auto value = "sdl2utils::guards::ensure<NONZERO> detected a zero return code";
            };

            
            template<SuccessCondition Cond>
            bool satisfies(int value);

            template<>
            inline bool satisfies<SuccessCondition::ZERO>(int value)
            {
                return value == 0;
            }

            template<>
            inline bool satisfies<SuccessCondition::NONZERO>(int value)
            {
                return value != 0;
            }
        }

        template<SuccessCondition Cond>
        inline void ensure(int sdlCallResult, const string& errorDetailMessage = detail::template EnsureErrorDetailMessage<Cond>::value)
        {
            if(!detail::satisfies<Cond>(sdlCallResult))
            {
                throw SDLErrorException(true, errorDetailMessage);
            }
        }

        namespace abbr
        {
            inline void z(int sdlCallResult)
            {
                ensure<SuccessCondition::ZERO>(sdlCallResult);
            }
            
            inline void z(int sdlCallResult, const string& errorDetailMessage)
            {
                ensure<SuccessCondition::ZERO>(sdlCallResult, errorDetailMessage);
            }
            
            inline void nz(int sdlCallResult)
            {
                ensure<SuccessCondition::NONZERO>(sdlCallResult);
            }
            
            inline void nz(int sdlCallResult, const string& errorDetailMessage)
            {
                ensure<SuccessCondition::NONZERO>(sdlCallResult, errorDetailMessage);
            }
        }

#ifdef SDL2UTILS_ENABLE_ABBR_GUARD_MACROS

#define SDL2UTILS_ABBR_DETAIL_PREFIX(RETURN_CODE) "the following call returned " #RETURN_CODE": "

// TODO: Extend these macros to specify the exact return code.
#define Z(SDL_CALL)     sdl2utils::guards::abbr::z(SDL_CALL, SDL2UTILS_ABBR_DETAIL_PREFIX(non-zero) #SDL_CALL)
#define NZ(SDL_CALL)    sdl2utils::guards::abbr::nz(SDL_CALL, SDL2UTILS_ABBR_DETAIL_PREFIX(zero) #SDL_CALL)

#else

// Defining Z and NZ as no-op to prevent code from disappearing
// when SDL2UTILS_ENABLE_ABBR_GUARD_MACROS is not defined.

#ifndef Z
#define Z(SDL_CALL) SDL_CALL
#endif

#ifndef NZ
#define NZ(SDL_CALL) SDL_CALL
#endif

#endif

    }
}

#endif /* SDL2UTILS_ERROR_UTILS_H */

