#include <ore/components/camera_component.h>
#include <ore/components/light_component.h>
#include <ore/components/model_component.h>
#include <ore/components/position_3d_component.h>
#include <ore/entity_manager.h>
#include <ore/loader.h>
#include <ore/systems/camera_system.h>
#include <ore/systems/entity_render_system.h>
#include <ore/window.h>

#include <cmath>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include "resource_path.h"

using namespace glm;

int main() {
    auto window = ore::window();
    auto barrel =
        ore::loader::get().load_model(BARREL_RES_DIR "/Barrel/Barrel02.obj");

    ore::entity_manager em;
    auto e = em.new_entity();
    e->emplace_component<ore::position_3d_component>();
    e->emplace_component<ore::model_component>(barrel);

    auto* camera = em.new_entity();
    auto* light = em.new_entity();

    ore::camera_system cs;
    ore::entity_render_system ers;

    auto p3d = e->get_component<ore::position_3d_component>();
    p3d->position = {0.f, 0.f, 0.f};
    p3d->scale = {5, 5, 5};

    auto lc = std::make_unique<ore::light_component>();
    lc->specular = vec3(1.0f, 1.0f, 1.0f);
    lc->diffuse = vec3(0.7f, 0.7f, 0.7f);
    lc->ambient = vec3(0.1f, 0.1f, 0.1f);
    lc->position = vec4{10.0f, 10.0f, 2.0f, 1.0f};
    lc->radius = 50.0f;
    light->assign_component(std::move(lc));

    auto cc = std::make_unique<ore::camera_component>();
    cc->position = vec4(0.0f, 3.0f, 3.0f, 0.0f);
    cc->projection = glm::perspective(M_PI / 4.0,
                                      static_cast<double>(window.get_width()) /
                                          static_cast<double>(window.get_height()),
                                      1.0, 100.0);
    camera->assign_component(std::move(cc));
    cs.look(camera, vec3(1.f, 1.0f, 0.0f));

    window.run_render_loop([&](){
      ers.process(em);

      auto et = em.new_entity();
      et->emplace_component<ore::position_3d_component>();
      et->emplace_component<ore::model_component>(barrel);
      auto p3d2 = et->get_component<ore::position_3d_component>();
      p3d2->position = {static_cast<float>((rand() % 40) - 20),
                        static_cast<float>((rand() % 40) - 20),
                        static_cast<float>((rand() % 40) - 20)};
      auto scale = rand() % 20;
      p3d2->scale = {scale, scale, scale};

      return ore::execution_state::continue_running;
    });

    window.stop();

    return 0;
}
