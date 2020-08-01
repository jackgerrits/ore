#pragma once

#include <stb_image.h>

#include <glm/glm.hpp>

namespace ore {
struct image {
    unsigned char* data = nullptr;
    int width = -1;
    int height = -1;
    int channels = -1;

    image(unsigned char* data, int width, int height, int channels);
    ~image();
    glm::vec3 get_pixel(int x, int y) const;
};
}  // namespace ore
