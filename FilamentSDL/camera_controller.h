#ifndef FILAMENT_SDL_CAMERA_CONTROLLER_H
#define FILAMENT_SDL_CAMERA_CONTROLLER_H

#include "renderer.h"
#include "input.h"

namespace sample {

    class CameraController {
    public:
        explicit CameraController(Renderer& renderer);
        void Update(const Input& input, float dt);

    private:
        Renderer& renderer_;
        float yaw_ = 0.0f;
        float pitch_ = 0.0f;
        filament::math::float3 position_ = {0.0f, 0.0f, 4.0f};
    };

} // namespace sample

#endif // FILAMENT_SDL_CAMERA_CONTROLLER_H