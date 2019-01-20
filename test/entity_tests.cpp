#include <ore/lib/catch.hpp>

#include <ore/entity.hpp>
#include <ore/components/position_3d_component.hpp>
#include <ore/components/light_component.hpp>

#include <vector>

using namespace ore;

TEST_CASE("Can query and add components to entity") {
    entity e;

    CHECK(e.getComponents().size() == 0);

    e.assignComponent(new Position3DComponent());
    REQUIRE(e.getComponents().size() == 1);
    REQUIRE(e.getComponent<Position3DComponent>() != nullptr);
    REQUIRE(e.getComponent<light_component>() == nullptr);
}
