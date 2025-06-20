#include <iostream>
#include <filament/FilamentAPI.h>
#include <filament/Engine.h>
#include <utils/Entity.h>

int main() {
    auto engine = filament::Engine::create();
    utils::Entity entity;
    engine->createCamera(entity);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}