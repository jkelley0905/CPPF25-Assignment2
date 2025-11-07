#include "bmp.hpp"
#include <iostream>
#include <time.h>

void add_gradient (BMP &bmp, color a, color b){
    int width = bmp.get_width();
    int height = bmp.get_height();

    float gradient = (float) 1 / height; 

    for (int y = 0; y < height; y++) {
        int r_val = (a.r * (1 - (gradient * y)))+(b.r * (gradient * y));
        int g_val = (a.g * (1 - (gradient * y)))+(b.g * (gradient * y));
        int b_val = (a.b * (1 - (gradient * y)))+(b.b * (gradient * y));

        for (int x = 0; x < width; x++) {
            bmp.set_pixel(x, y, r_val, g_val, b_val);
        }
    }
}

int main () {
    BMP bmp (1000,500);
    color a (0,0,0);
    color b (0, 0, 255);

    add_gradient (bmp, a, b);

    bmp.write("gradient.bmp"); // Save the image to a file

    return 0;
}

    
