#include <ore/entity.h>
#include <ore/model.h>

namespace ore {
std::vector<component*> entity::get_components() {
    std::vector<component*> results;
    for (auto const& [id, component] : components) {
        results.push_back(component.get());
    }
    return results;
}
}  // namespace ore
