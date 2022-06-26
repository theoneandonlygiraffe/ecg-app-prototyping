#ifndef APPMANAGER_H_
#define APPMANAGER_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "Timer.h"



#define STANDARD_WINPOS_X 100
#define STANDARD_WINPOS_Y 100




class appManager {
public:

//constructor&deconstructor
	appManager(int width,int height,int fps,std::string titel = "test");
	~appManager();

//start&stop
	void start();//start app loop
	void stop() {_running=false;};
	bool running() const {return _running;};

//width&height of th window
	//at start of frame
	int width() const {return _width-1;};
	int height() const {return _height-1;};
	//at time of call
//	int rwidth() const { int w,h; SDL_GetWindowSize(sdl_window,&w,&h); return w-1;};
//	int rheight() const { int w,h; SDL_GetWindowSize(sdl_window,&w,&h); return h-1;};

//mouse coordinates
	//at start of frame
	int mousex() const {return _mousex;};
	int mousey() const {return _mousey;};
	//at time of call
	int rmousex() const {int x,y;SDL_GetMouseState(&x,&y);return x;};
	int rmousey() const {int x,y;SDL_GetMouseState(&x,&y);return y;};

//SDL renderer for SDL drawing
	SDL_Renderer * renderer() const {return sdl_renderer;}

private:

//repetetive
	void update(); //update window and mouse status. called at start of frame
	void drawScreen();//clear & render new frame (SDL)

//get&set
	int fps() const {return _fps;};

//SDL2
	int createWindow(std::string titel,int width ,int height, int x = STANDARD_WINPOS_X, int y = STANDARD_WINPOS_Y );
	int createRenderer();



//status
	int _width,_height;
	int _mousex,_mousey;
	int _fps;
	bool _running;

//SDL2
	SDL_Window * sdl_window;
	SDL_Renderer *  sdl_renderer;

};


namespace udef {
void setup(appManager * appname);
void draw(appManager * appname);
void setup();//for use with global app object
void draw();
}

#endif /* APPMANAGER_H_ */
