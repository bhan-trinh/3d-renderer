#include "framebuffer.h"
#include <algorithm> 
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

std::vector<uint32_t> pixels;

Framebuffer::Framebuffer(int w, int h) 
    : WIDTH(w), HEIGHT(h), pixels(WIDTH * HEIGHT, 0)
{}

uint32_t* Framebuffer::getPixels() {
    return pixels.data();
}

void Framebuffer::drawLine(int x0, int y0, int x1, int y1, uint32_t color){
    // Bresenham Algorithm
    int dx, dy, x, y, e, state;

    putPixel(x0, y0, color ^ 0x00FFFFFF);
    putPixel(x1, y1, color ^ 0x00FFFFFF);

    // Swap if start > end
    if (x0 > x1){
        int temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    dx = x1 - x0;
    dy = y1 - y0;

    state = 1;


    // Refactor this!
    // slope > 1
    if (dy > dx)
    {
        state = 2;
        // Flips x and y coordinates
        
        // Flips dx and dy
        dx = y1 - y0;
        dy = x1 - x0;

        // Flips x0 and y0
        x = x0;
        x0 = y0;
        y0 = x;

        // Flips x1 and y1
        x = x1;
        x1 = y1;
        y1 = x;
    } 

    // slope < 0
    else if (dx * dy < 0)
    {
        state = 0;

        // reflects y0 and y1 along the x-axis
        y0 = 0 - y0;
        y1 = 0 - y1;
        dy = y1 - y0;

        // slope < -1
        if (abs(dy) > abs(dx))
        {
            state = 3;        
            // Flips x and y coordinates
        
            // Flips dx and dy
            dx = y1 - y0;
            dy = x1 - x0;

            // Flips x0 and y0
            x = x0;
            x0 = y0;
            y0 = x;

            // Flips x1 and y1
            x = x1;
            x1 = y1;
            y1 = x;
        }
    }

    x = x0;
    y = y0;
    e = 0;

    while (x != x1){
        switch(state)
        {
            // slope < 0
            case 0:
                putPixel(x, 0 - y, color);
                break;
            // 0 <= slope <= 1
            case 1:
                putPixel(x, y, color);
                break;
            // slope > 1
            case 2:
                putPixel(y, x, color);
                break;
            // slop < -1
            case 3:
                putPixel(y, 0 - x, color);
        }

        e = e + dy;
        if (2 * e > dx) {
            y++;
            e = e - dx;
        }

        x++;
    }




}

void Framebuffer::putPixel(int x, int y, uint32_t color){
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    pixels[y * WIDTH + x] = color;
}

void Framebuffer::clear(uint32_t color){
    std::fill(pixels.begin(), pixels.end(), color);
}

void Framebuffer::printPixels() {
}
