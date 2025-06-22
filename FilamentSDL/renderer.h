#ifndef FILAMENT_SDL_RENDERER_H
#define FILAMENT_SDL_RENDERER_H

#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/SwapChain.h>
#include <filament/View.h>
#include <filament/Camera.h>

#include "window.h"

namespace sample {

    class Renderer {
    public:
        explicit Renderer(Window& window);
        ~Renderer();

        void Render();
        filament::Camera* GetCamera() { return camera_; }

    private:
        Window& window_;
        filament::Engine* engine_ = nullptr;
        filament::SwapChain* swap_chain_ = nullptr;
        filament::Renderer* renderer_ = nullptr;
        filament::Scene* scene_ = nullptr;
        filament::View* view_ = nullptr;
        filament::Camera* camera_ = nullptr;
    };

} // namespace sample

#endif // FILAMENT_SDL_RENDERER_H