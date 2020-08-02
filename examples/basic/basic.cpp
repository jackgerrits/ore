#include <ore/loader.h>
#include <ore/systems/entity_render_system.h>
#include <ore/window.h>

#include "basic_render_system.h"

int main() {
    ore::window window;

    std::vector<float> vertices = {
        0.5f,  0.5f,  0.0f,  // top right
        0.5f,  -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f   // top left
    };

    // Triangles must be defined in counter clockwise order so that the front
    // face faces the camera. This is because the backface is culled.
    std::vector<unsigned int> indices = {
        3, 1, 0,  // first triangle
        3, 2, 1   // second triangle
    };

    auto vao = ore::loader::get().load_vao(vertices, indices);
    auto m = std::make_shared<ore::model>();
    m->add_model_part(ore::model_part(vao, indices.size(), 0));

    ore::entity_manager em;
    auto* e = em.new_entity();
    e->emplace_component<ore::model_component>(m);

    ore::basic_render_system brs;

    window.run_render_loop([&]() {
        // Process the entities with the render system.
        brs.process(em);

        return ore::execution_state::continue_running;
    });

    window.stop();
    return 0;
}
