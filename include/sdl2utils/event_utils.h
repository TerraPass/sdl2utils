#ifndef SDL2UTILS_EVENT_UTILS_H
#define SDL2UTILS_EVENT_UTILS_H

#include <SDL2/SDL_events.h>

namespace sdl2utils
{
    /**
     * Check for ESC keypress or user clicking X and return.
     * 
     * @return false until ESC is pressed or user X-s out of the window, then true.
     */
    bool escOrCrossPressed();

    /**
     * Blocks until user presses ESC or attempts to close the window by pressing X.
     * 
     * @throws SDLErrorException if an error occurs while waiting.
     */
    void waitEscOrCrossPressed();

    /**
     * Blocks until any key is pressed.
     * 
     * @param waitRelease If true, wait until the user releases the key before returning.
     * Defaults to false;
     * @return SDL_Event instance, describing the key press.
     */
    const SDL_Event waitKeyPressed(bool waitRelease = false);
}

#endif /* SDL2UTILS_EVENT_UTILS_H */

