#include <ore/components/light_component.h>
#include <ore/components/position_3d_component.h>
#include <ore/entity.h>

#include <ore/lib/catch.hpp>
#include <vector>

using namespace ore;

TEST_CASE("Can query and add components to entity") {
    entity e;

    CHECK(e.get_components().size() == 0);

    e.emplace_component<position_3d_component>();
    REQUIRE(e.get_components().size() == 1);
    REQUIRE(e.get_component<position_3d_component>() != nullptr);
    REQUIRE(e.get_component<light_component>() == nullptr);
}
