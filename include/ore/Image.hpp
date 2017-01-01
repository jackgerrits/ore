#ifndef ENTITY_H
#define ENTITY_H

#include <ore/lib/stb_image.h>
#include <glm/glm.hpp>

namespace ore {
    struct Image {
        unsigned char *data;
        int width;
        int height;
        int channels;

        Image();
        Image(unsigned char* data, int width, int height, int channels);
        ~Image();
        glm::vec3 getPixel(int x, int y);
    };
}

#endif
