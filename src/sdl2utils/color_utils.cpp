#include "../../include/sdl2utils/color_utils.h"

namespace sdl2utils
{
    static Uint8 lerpComponent(const Uint8 a, const Uint8 b, const double amount)
    {
        short diff = b - a;
        short result = static_cast<short>(a) + static_cast<short>(diff * amount);

        // Cap at 0 at 0xFF to prevent UB (overflow)
        return (result > 0
                    ? result <= 0xFF
                        ? result
                        : 0xFF
                    : 0);
    }

    SDL_Color lerp(const SDL_Color& a, const SDL_Color& b, double amount)
    {
        SDL_Color result;

        result.r = lerpComponent(a.r, b.r, amount);
        result.g = lerpComponent(a.g, b.g, amount);
        result.b = lerpComponent(a.b, b.b, amount);
        result.a = lerpComponent(a.a, b.a, amount);

        return result;
    }
}
