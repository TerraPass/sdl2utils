#include "../../include/sdl2utils/event_utils.h"

#include <SDL.h>
#include <SDL_events.h>

#include "../../include/sdl2utils/guards.h"

namespace sdl2utils
{
    using namespace guards::abbr;

    static constexpr const auto WAIT_EVENT_ERROR_DETAIL = "error occurred in SDL_WaitEvent()";
    
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
        SDL_Event event;
        do
        {
            nz(SDL_WaitEvent(&event), WAIT_EVENT_ERROR_DETAIL);
        }
        while(!isEscOrCrossPressedEvent(event));
    }

    const SDL_Event waitKeyPressed(bool waitRelease)
    {
        SDL_Event event;
        do
        {
            nz(SDL_WaitEvent(&event), WAIT_EVENT_ERROR_DETAIL);
        }
        while(
            event.type != (waitRelease ? SDL_KEYUP : SDL_KEYDOWN)
        );
        return std::move(event);
    }
}
