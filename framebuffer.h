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
        void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
        void clear(uint32_t color);
        void printPixels();
};

#endif