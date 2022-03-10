#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Texture {

public:
	
	Texture(int x, int y, int width, int height);
	bool loadTexture(const char* path, SDL_Renderer* renderer);
	void renderTexture(SDL_Renderer* renderer);
	void createSourceRectangle(int x, int y, int w, int h);
	void setPosition(int xPos, int yPos);
	SDL_Rect getDestinationRect();
	int getWidth() const;
	int getHeight() const;

private:
	int x;
	int y;
	int width;
	int height;
	SDL_Texture* texture;
	SDL_Rect source;
	SDL_Rect destination;
	bool useSource;
};