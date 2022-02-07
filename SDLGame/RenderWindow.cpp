#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* title, int width, int height)
	: title(title), screenWidth(width), screenHeight(height) {}

bool RenderWindow::CreateWindow() {
	bool s = true;
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		printf("Error, could not create the window! ERROR: %s", SDL_GetError());
		s = false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		printf("Error, could not create the renderer! ERROR: %s", SDL_GetError());
		s = false;
	}


	return s;
}

void RenderWindow::Clear() {
	
	SDL_RenderClear(renderer);
}

void RenderWindow::Present() {

	SDL_RenderPresent(renderer);

}

void RenderWindow::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
// Getters =====================================================================

SDL_Renderer* RenderWindow::getRenderer() {

	return renderer;
}



void RenderWindow::Quit() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	renderer = nullptr;

}
