#include "Texture.h"

Texture::Texture(int x, int y, int width, int height)
:	x(x), y(y), width(width), height(height), useSource(false)
{
	destination.w = width;
	destination.h = height;
	setPosition(x, y);
}

bool Texture::loadTexture(const char* path, SDL_Renderer* renderer) {

	texture = IMG_LoadTexture(renderer, path);
	if (texture == nullptr)
	{
		printf("Error, could not load the texture! ERROR: %s", IMG_GetError());
		return false;
	}

	return texture != nullptr;
}
void Texture::createSourceRectangle(int x, int y, int w, int h)
{
	source.x = x;
	source.y = y;
	source.w = w;
	source.h = h;

	useSource = true;
}

void Texture::setPosition(int xPos, int yPos)
{
	destination.x = xPos;
	destination.y = yPos;
}

SDL_Rect Texture::getDestinationRect()
{
	return destination;
}


void Texture::renderTexture(SDL_Renderer* renderer) {

	if (useSource)
		SDL_RenderCopy(renderer, texture, &source, &destination);
	else
		SDL_RenderCopy(renderer, texture, nullptr, &destination);
}