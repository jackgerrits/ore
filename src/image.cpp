#include <ore/image.h>

using namespace ore;

image::image(unsigned char* data, int width, int height, int channels)
    : data(data), width(width), height(height), channels(channels) {}

image::~image() { stbi_image_free(this->data); }

glm::vec3 image::get_pixel(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        // Returns a vector of -1 to indicate the image does not contain a pixel
        // at that location.
        return glm::vec3(-1.0f, -1.0f, -1.0f);
    }

    // Determine the position in data to start reading. Each pixel is 1 byte.
    int offset = ((width * y) + x) * channels;

    return glm::vec3((float)data[offset] / 255, (float)data[offset + 1] / 255,
                     (float)data[offset + 2] / 255);
}
