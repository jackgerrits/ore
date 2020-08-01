#include <ore/entity.h>
#include <ore/model.h>

using namespace std;

namespace ore {
std::vector<component*> entity::get_components() {
    std::vector<component*> results;
    for (auto const& kv : components) {
        results.push_back(kv.second.get());
    }
    return results;
}
}  // namespace ore
