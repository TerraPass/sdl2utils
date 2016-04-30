#ifndef SDL2UTILS_EVENT_UTILS_H
#define SDL2UTILS_EVENT_UTILS_H

#include <SDL2/SDL.h>

namespace sdl2utils
{
    /**
     * Check for ESC keypress or user clicking X and return.
     * 
     * @return false until ESC is pressed or user X-s out of the window, then true.
     */
    bool escOrCrossPressed();
}

#endif /* SDL2UTILS_EVENT_UTILS_H */

