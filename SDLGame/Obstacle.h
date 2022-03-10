#pragma once
#include <SDL.h>
#include "Texture.h"
#include <stdio.h>
class Obstacle
{
public:
	Obstacle();
	Obstacle(int xPos, int yPos, float VelocityV, int w, int h, Texture tex, SDL_Renderer* renderer);
	void move(int x, int y);
	void draw();
	bool collided(SDL_Rect& targetRect);
	int getWidth() const;
	int getHeight() const;
private:
	int x;
	int y;
	float velocity;
	int width;
	int height;
	Texture texture;
	SDL_Renderer* renderer;
};