#include "../../include/sdl2utils/event_utils.h"

#include <SDL2/SDL.h>
#include <SDL/SDL_events.h>

#include "../../include/sdl2utils/guards.h"

namespace sdl2utils
{
    using namespace guards::abbr;

    static inline bool isEscOrCrossPressedEvent(const SDL_Event& event)
    {
        return event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE);
    }
    
    bool escOrCrossPressed()
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        return isEscOrCrossPressedEvent(event);
    }

    void waitEscOrCrossPressed()
    {
        static constexpr const auto ERROR_DETAIL = "error occurred in SDL_WaitEvent()";

        SDL_Event event;
        do
        {
            nz(SDL_WaitEvent(&event), ERROR_DETAIL);
        }
        while(!isEscOrCrossPressedEvent(event));
    }
}
