#include "bmp.hpp"
#include <iostream>
#include <time.h>
void draw_rectangle(BMP &bmp,int x, int y, int l, int h, int b, color c ){
    for(int i=0;i<=l;i++){
        for(int ii=0;ii<=b;ii++){
            //top line
            bmp.set_pixel(i+x, y+ii, c.r,c.g,c.b);

            //botom line
            bmp.set_pixel(i+x, y+h-ii, c.r, c.g,c.b);
        }
    }
    for(int j=0;j<=h;j++){
        for(int ii=0;ii<=b;ii++){
            //left line
            bmp.set_pixel(x+ii, y+j, c.r,c.g,c.b);

            //right line
            bmp.set_pixel(x+l-ii, y+j,c.r, c.g,c.b);
        }
    }
}

void add_gradient (BMP &bmp, int x, int y, color a, color b){
  bmp width = x;
  bmp length = y;



