#include <ore/Image.hpp>

namespace ore {

    Image::Image()
        : data(NULL), width(-1), height(-1), channels(-1) {
    }

    Image::Image(unsigned char* data, int width, int height, int channels)
        : data(data), width(width), height(height), channels(channels) {
    }

    Image::~Image() {
        stbi_image_free(this->data);
    }

    glm::vec3 Image::getPixel(int x, int y){
        if(x < 0 || x >= width || y < 0 || y >= height) {
            return glm::vec3(-1.0f, -1.0f, -1.0f);    // Returns a vector of -1 to indicate the image does not contain a pixel at that location.
        }

        int offset = ((width * y) + x) * channels;  // Determine the position in data to start reading. Each pixel is 1 byte.
        return glm::vec3((float)data[offset] / 255, (float)data[offset + 1] / 255, (float)data[offset + 2] / 255);
    }
}
