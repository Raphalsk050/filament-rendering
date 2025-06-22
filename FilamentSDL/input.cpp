#include "input.h"

namespace sample {

    void Input::HandleEvent(const SDL_Event& e) {
        switch (e.type) {
        case SDL_KEYDOWN:
            keys_.insert(e.key.keysym.sym);
            break;
        case SDL_KEYUP:
            keys_.erase(e.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            buttons_.insert(e.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            buttons_.erase(e.button.button);
            break;
        case SDL_MOUSEMOTION:
            mouse_dx_ += e.motion.xrel;
            mouse_dy_ += e.motion.yrel;
            break;
        default:
            break;
        }
    }

    bool Input::IsKeyPressed(SDL_Keycode key) const {
        return keys_.count(key) > 0;
    }

    bool Input::IsMouseButtonPressed(uint8_t button) const {
        return buttons_.count(button) > 0;
    }

    void Input::ResetMouseDelta() {
        mouse_dx_ = mouse_dy_ = 0;
    }

} // namespace sample