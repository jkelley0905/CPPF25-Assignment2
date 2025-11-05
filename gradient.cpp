#include "bmp.hpp"
#include <iostream>
#include <time.h>

void add_gradient (BMP &bmp, color a, color b){
    int width = bmp.get_width();
    int height = bmp.get_height();

    float gradient = (float) (height / 100); 

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            bmp.set_pixel(j, i, ((a.r * (100 - (gradient * i)))+(b.r * (gradient * i))),((a.g * (100 - (gradient * i)))+(b.g * (gradient * i))),((a.b * (100 - (gradient * i)))+(b.b * (gradient * i))));
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

    
