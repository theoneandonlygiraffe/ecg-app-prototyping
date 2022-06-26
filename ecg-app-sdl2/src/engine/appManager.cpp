#include "appManager.h"
appManager::appManager(int width, int height, int fps, std::string titel) {
	SDL_Quit();
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
		delete this;
	}
	else
	{
		std::clog << "SDL_Init successfull" << std::endl;
	}

	sdl_window=nullptr;
	sdl_renderer=nullptr;

	_running=true;
	_fps=fps;

	createWindow(titel,width,height);
	createRenderer();
}

appManager::~appManager() {
	std::clog << "stopping SDL" << std::endl << "stopping windowManager" << std::endl;
	SDL_Quit();
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	this->stop();
	if (sdl_window != nullptr){
		SDL_DestroyWindow(sdl_window);
	}
	if (sdl_renderer != nullptr){
		SDL_DestroyRenderer(sdl_renderer);
	}
}

void appManager::start() {
	Timer timer_sincelastframe;

		int time_delta;
		//called once on app start
		//std::cout<<"setup();"<<std::endl;
		udef::setup();

		//apploop
		while(running()){
			if (timer_sincelastframe.getTime()>=1000/fps()){
				//std::cout<<"draw();"<<std::endl;

				timer_sincelastframe.reset();


				update();
				udef::draw();//called until app object is stopped
				drawScreen();


				time_delta=(1000/fps())-timer_sincelastframe.getTime();

				if(time_delta >= 0){
					SDL_Delay(time_delta);
				}
				else{
					std::cerr << "Error :: " << "framerate to high for this machine" << std::endl;
				}

				if(!running()){
					break;
				}
			}
		}
}



void appManager::update() {
	SDL_GetWindowSize(sdl_window,&_width,&_height);
	SDL_GetMouseState(&_mousex,&_mousey);
}

void appManager::drawScreen() {
	SDL_RenderPresent(sdl_renderer);
	SDL_RenderClear(sdl_renderer);
}

int appManager::createWindow(std::string titel,int width, int height, int x, int y) {
	sdl_window = SDL_CreateWindow(titel.c_str(), x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if (sdl_window == nullptr){
		std::cerr << "Error :: " << "SDL_CreateWindow : " << SDL_GetError() << std::endl;
		delete this;
		return 1;
	}
	else
	{
		std::clog << "SDL_CreateWindow successfull" << std::endl;
		return 0;
	}
}

int appManager::createRenderer() {
	sdl_renderer= SDL_CreateRenderer(sdl_window, -1 ,SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == nullptr){
		std::cerr << "Error :: " <<  "SDL_CreateRenderer : " << SDL_GetError() << std::endl;
		delete this;
		return 1;
	}
	else
	{
		std::clog << "SDL_CreateRenderer successfull" << std::endl;
		return 0;
	}
}
