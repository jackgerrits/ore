#include <ore/entity.hpp>
#include <ore/model.hpp>

using namespace std;

namespace ore {
    std::vector<Component*> entity::getComponents() {
        std::vector<Component*> results;
        for(auto const& kv : components) {
            results.push_back(kv.second);
        }
        return results;
    }    
}
