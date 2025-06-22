#include "renderer.h"
#include "native_window_helper.h"

#include <filament/Engine.h>
#include <utils/EntityManager.h>

namespace sample {

    Renderer::Renderer(Window& window) : window_(window) {
        engine_ = filament::Engine::create();
        swap_chain_ = engine_->createSwapChain(GetNativeWindow(window.Get()));
        renderer_ = engine_->createRenderer();
        scene_ = engine_->createScene();
        view_ = engine_->createView();
        camera_ = engine_->createCamera(utils::EntityManager::get().create());
        view_->setCamera(camera_);
        view_->setScene(scene_);
    }

    Renderer::~Renderer() {
        if (!engine_) return;
        engine_->destroy(camera_->getEntity());
        engine_->destroy(view_);
        engine_->destroy(scene_);
        engine_->destroy(renderer_);
        engine_->destroy(swap_chain_);
        filament::Engine::destroy(&engine_);
    }

    void Renderer::Render() {
        if (renderer_->beginFrame(swap_chain_)) {
            renderer_->render(view_);
            renderer_->endFrame();
        }
    }

} // namespace sample