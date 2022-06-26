#ifndef BASICSHAPES_H_
#define BASICSHAPES_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>


#include "appManager.h"
#include "myEngine.h"


struct rgb_color {
public:
    rgb_color(char r,char g,char b,char a){_r=r;_g=g;_b=b;_a=a;};
    unsigned char r() const {return _r;};
    unsigned char g() const {return _g;};
    unsigned char b() const {return _b;};
    unsigned char a() const {return _a;};
private:
    unsigned char _r,_g,_b,_a;
};
typedef struct rgb_color rgb_color;

extern struct rgb_color* const std_red;
extern struct rgb_color* const std_blue;
extern struct rgb_color* const std_green;
extern struct rgb_color* const std_yellow;


void setcolor(rgb_color* color);
void line(int x1,int y1,int x2,int y2,rgb_color* color);

void bs_sqr(int x1,int y1,int width,rgb_color* border);
void bs_sqr(int x1,int y1,int width,rgb_color* border,rgb_color* fill);


#endif /* BASICSHAPES_H_ */
