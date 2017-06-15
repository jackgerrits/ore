#include <ore/lib/catch.hpp>

#include <ore/Entity.hpp>
#include <ore/components/Position3DComponent.hpp>
#include <ore/components/LightComponent.hpp>

#include <vector>

using namespace ore;

TEST_CASE("Can query and add components to entity") {
    Entity e;

    CHECK(e.getComponents().size() == 0);

    e.assignComponent(new Position3DComponent());
    REQUIRE(e.getComponents().size() == 1);
    REQUIRE(e.getComponent<Position3DComponent>() != nullptr);
    REQUIRE(e.getComponent<LightComponent>() == nullptr);
}
