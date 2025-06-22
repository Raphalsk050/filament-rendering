#ifndef FILAMENT_SDL_INPUT_H
#define FILAMENT_SDL_INPUT_H

#include <SDL.h>
#include <unordered_set>

namespace sample {

    class Input {
    public:
        void HandleEvent(const SDL_Event& e);
        bool IsKeyPressed(SDL_Keycode key) const;
        bool IsMouseButtonPressed(uint8_t button) const;
        int GetMouseDeltaX() const { return mouse_dx_; }
        int GetMouseDeltaY() const { return mouse_dy_; }
        void ResetMouseDelta();

    private:
        std::unordered_set<SDL_Keycode> keys_;
        std::unordered_set<uint8_t> buttons_;
        int mouse_dx_ = 0;
        int mouse_dy_ = 0;
    };

} // namespace sample

#endif // FILAMENT_SDL_INPUT_H