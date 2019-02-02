#pragma once

#include <ore/lib/stb_image.h>
#include <glm/glm.hpp>

namespace ore {
    struct image {
        unsigned char *data;
        int width;
        int height;
        int channels;

        image();
        image(unsigned char* data, int width, int height, int channels);
        ~image();
        glm::vec3 getPixel(int x, int y);
    };
}
