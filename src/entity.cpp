#include <ore/entity.hpp>
#include <ore/model.hpp>

using namespace std;

namespace ore {
    std::vector<component*> entity::get_components() {
        std::vector<component*> results;
        for (auto const& kv : components) {
            results.push_back(kv.second);
        }
        return results;
    }    
}
