#include "bmp.hpp"
#include <iostream>
#include <time.h>

void add_gradient (BMP &bmp, color a, color b){
  int width = bmp.get_width();
  int height = bmp.get_height();
  
  for (int y = 0; y < height; y++) {
    int numerator = y;
    int denominator = height - 1;
    
    int r_val = ((a.r * (numerator - denominator)) + (b.r * numerator)) / denominator;
    int g_val = ((a.g * (numerator - denominator)) + (b.g * numerator)) / denominator;
    int b_val = ((a.b * (numerator - denominator)) + (b.b * numerator)) / denominator;

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

    
