#include "../../include/sdl2utils/event_utils.h"

namespace sdl2utils
{
    bool escOrCrossPressed()
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        return event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE);
    }
}
