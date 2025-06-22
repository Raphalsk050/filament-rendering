#include "window.h"
#include "input.h"
#include "renderer.h"
#include "camera_controller.h"

#include <chrono>

int main() {
    sample::Window window("Filament SDL", 1280, 720);
    sample::Renderer renderer(window);
    sample::Input input;
    sample::CameraController camera(renderer);

    auto last = std::chrono::steady_clock::now();
    while (!window.ShouldClose()) {
        if (!window.ProcessEvents(&input)) {
            break;
        }
        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - last).count();
        last = now;

        camera.Update(input, dt);
        input.ResetMouseDelta();

        renderer.Render();
    }
    return 0;
}