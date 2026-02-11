#include "framebuffer.h"
#include <algorithm> 
#include <cstdint>
#include <vector>

std::vector<uint32_t> pixels;

Framebuffer::Framebuffer(int w, int h) 
    : WIDTH(w), HEIGHT(h), pixels(WIDTH * HEIGHT, 0)
{}

uint32_t* Framebuffer::getPixels() {
    return pixels.data();
}

void Framebuffer::putPixel(int x, int y, uint32_t color){
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
        pixels[y * WIDTH + x] = color;
}

void Framebuffer::clear(uint32_t color){
    std::fill(pixels.begin(), pixels.end(), color);
}