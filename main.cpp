#include <SDL.h>
#include <SDL_syswm.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/View.h>
#include <filament/Scene.h>
#include <filament/Camera.h>
#include <filament/Viewport.h>
#include <utils/EntityManager.h>

#ifdef __APPLE__
#include "cocoa_helper.h"
#endif

using namespace filament;
using namespace utils;

int main() {
    const uint WIDTH = 800, HEIGHT = 600;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) return -1;

    SDL_Window* window = SDL_CreateWindow(
        "Filament + SDL2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_METAL
    );

    if (!window) {
        SDL_Quit();
        return -1;
    }

    // Obter o native window handle
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);

    void* nativeWindow = nullptr;
#ifdef __APPLE__
    nativeWindow = createMetalLayer(wmInfo.info.cocoa.window);
#elif defined(_WIN32)
    nativeWindow = wmInfo.info.win.window;
#elif defined(__linux__)
    nativeWindow = (void*)(uintptr_t)wmInfo.info.x11.window;
#endif

    // Criar Engine e SwapChain
    Engine* engine = Engine::create();
    SwapChain* sc = engine->createSwapChain(nativeWindow);

    // Criar componentes de renderização
    Renderer* renderer = engine->createRenderer();
    View* view = engine->createView();
    Scene* scene = engine->createScene();
    view->setScene(scene);

    // Configurar opções de limpeza da tela
    Renderer::ClearOptions opts;
    opts.clearColor = { 0.1f, 0.1f, 0.1f, 1.0f };  // Cinza escuro
    opts.clear = true;
    renderer->setClearOptions(opts);

    // Configurar viewport
    view->setViewport(Viewport{ 0, 0, WIDTH, HEIGHT });

    // Criar e configurar câmera
    Entity camEntity = EntityManager::get().create();
    Camera* camera = engine->createCamera(camEntity);
    view->setCamera(camera);
    camera->setProjection(
        45.0,                                    // fovInDegrees
        double(WIDTH) / double(HEIGHT),         // aspectRatio
        0.1,                                    // near
        100.0                                   // far
    );

    // Loop principal de eventos e renderização
    bool running = true;
    SDL_Event event;

    while (running) {
        // Processar eventos SDL2
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;

                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        int newWidth = event.window.data1;
                        int newHeight = event.window.data2;

                        // Atualizar viewport e proporção da câmera
                        view->setViewport(Viewport{ 0, 0, (uint32_t)newWidth, (uint32_t)newHeight });
                        camera->setProjection(
                            90.0f,
                            double(newWidth) / double(newHeight),
                            0.1,
                            1000.0
                        );

#ifdef __APPLE__
                        updateMetalLayerFrame(nativeWindow, newWidth, newHeight);
#endif
                    }
                    break;
            }
        }

        // Renderizar o frame
        if (renderer->beginFrame(sc)) {
            renderer->render(view);
            renderer->endFrame();
        }
    }

    // Limpeza dos recursos na ordem inversa da criação
    engine->destroyCameraComponent(camEntity);
    EntityManager::get().destroy(camEntity);

    engine->destroy(view);
    engine->destroy(scene);
    engine->destroy(renderer);
    engine->destroy(sc);
    Engine::destroy(&engine);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}