#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Texture {

public:
	Texture();
	bool loadTexture(const char* path, SDL_Renderer* renderer);
	void renderTexture(SDL_Renderer* renderer);
	void createSourceRectangle(int x, int y, int w, int h);

	SDL_Rect getDestinationRect();
private:

	SDL_Texture* texture;
	SDL_Rect source;
	SDL_Rect destination;

	bool useSource;
};