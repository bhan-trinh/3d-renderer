#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <cstdint>
#include <vector>

class Framebuffer {
    public:
        const int WIDTH;
        const int HEIGHT;
        std::vector<uint32_t> pixels;

        Framebuffer(int w, int h);
        uint32_t* getPixels();
        void putPixel(int x, int y, uint32_t color);
        void clear(uint32_t color);
};

#endif