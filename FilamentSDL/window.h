#ifndef FILAMENT_SDL_WINDOW_H
#define FILAMENT_SDL_WINDOW_H

#include <SDL.h>
#include <string>

namespace sample {

    class Window {
    public:
        Window(const std::string& title, uint32_t width, uint32_t height);
        ~Window();

        bool ProcessEvents(class Input* input = nullptr);
        SDL_Window* Get() const { return window_; }
        bool ShouldClose() const { return should_close_; }

    private:
        SDL_Window* window_ = nullptr;
        bool should_close_ = false;
    };

} // namespace sample

#endif // FILAMENT_SDL_WINDOW_H