#pragma once
#include <SDL.h>
#include <stdio.h>

class RenderWindow {
public:
	RenderWindow(const char*, int, int);

	bool CreateWindow();
	void Clear();
	void Present();
	void Quit();
	SDL_Renderer* getRenderer();
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
private:
	//
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect source;
	SDL_Rect destination;

	// Window Creation Stuff
	const char* title;
	int screenWidth;
	int screenHeight;
};
