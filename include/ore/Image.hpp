#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

namespace ore {
    struct Image {
        unsigned char *data;
        int width;
        int height;
        int channels;

        Image();
        Image(unsigned char* data, int width, int height, int channels);
        glm::vec3 getPixel(int x, int y);
    };
}

#endif
