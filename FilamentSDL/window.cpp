#include "window.h"
#include "input.h"

namespace sample {

    Window::Window(const std::string& title, uint32_t width, uint32_t height) {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    }

    Window::~Window() {
        if (window_) {
            SDL_DestroyWindow(window_);
        }
        SDL_Quit();
    }

    bool Window::ProcessEvents(Input* input) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (input) input->HandleEvent(e);
            if (e.type == SDL_QUIT) {
                should_close_ = true;
            }
        }
        return !should_close_;
    }

} // namespace sample