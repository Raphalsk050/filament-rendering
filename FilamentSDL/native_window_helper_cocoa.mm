#include "native_window_helper.h"
#include <Cocoa/Cocoa.h>
#include <SDL_syswm.h>

void* GetNativeWindow(SDL_Window* window) {
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    SDL_GetWindowWMInfo(window, &wmi);
    NSWindow* win = wmi.info.cocoa.window;
    NSView* view = [win contentView];
    return (__bridge void*)view;
}