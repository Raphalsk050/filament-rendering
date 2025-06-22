#include "native_window_helper.h"
#include <SDL_syswm.h>

void* GetNativeWindow(SDL_Window* window) {
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    if (!SDL_GetWindowWMInfo(window, &info)) {
        return nullptr;
    }
#if defined(__linux__)
    return (void*)info.info.x11.window;
#elif defined(_WIN32)
    return (void*)info.info.win.window;
#else
    return nullptr;
#endif
}
