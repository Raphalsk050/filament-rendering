#include "camera_controller.h"

#include <SDL.h>
#include <filament/Camera.h>
#include <math/mat4.h>

using namespace filament::math;

namespace sample {

    CameraController::CameraController(Renderer& renderer) : renderer_(renderer) {}

    void CameraController::Update(const Input& input, float dt) {
        const float move_speed = 2.0f;
        if (input.IsKeyPressed(SDLK_w)) position_.z -= move_speed * dt;
        if (input.IsKeyPressed(SDLK_s)) position_.z += move_speed * dt;
        if (input.IsKeyPressed(SDLK_a)) position_.x -= move_speed * dt;
        if (input.IsKeyPressed(SDLK_d)) position_.x += move_speed * dt;

        yaw_ += input.GetMouseDeltaX() * 0.002f;
        pitch_ += input.GetMouseDeltaY() * 0.002f;

        float3 dir;
        dir.x = cosf(pitch_) * sinf(yaw_);
        dir.y = sinf(pitch_);
        dir.z = cosf(pitch_) * cosf(yaw_);

        filament::Camera* cam = renderer_.GetCamera();
        cam->lookAt(position_, position_ + dir, float3{0,1,0});
    }

} // namespace sample