#include "basicshapes.h"

rgb_color* const std_red = new rgb_color(255,0,0,255);
rgb_color* const std_green = new rgb_color(0,255,0,255);
rgb_color* const std_blue = new rgb_color(0,0,255,255);
rgb_color* const std_yellow = new rgb_color(255,255,0,255);

void setcolor(rgb_color* color) {
	SDL_SetRenderDrawColor(APP_NAME.renderer(), color->r(), color->g(), color->b(), color->a());
}

void line(int x1, int y1, int x2, int y2, rgb_color* color) {
	SDL_SetRenderDrawColor(APP_NAME.renderer(), color->r(), color->g(), color->b(), color->a());
	SDL_RenderDrawLine(APP_NAME.renderer(),x1,y1,x2,y2);
}
