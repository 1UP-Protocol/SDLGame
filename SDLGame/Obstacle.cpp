#include "Obstacle.h"

Obstacle::Obstacle()
	: x(0), y(0), velocity(0), width(0), height(0), texture(0, 0, 0, 0), renderer(nullptr) {}

Obstacle::Obstacle(int xPos, int yPos, float velocityV, int w, int h, Texture tex, SDL_Renderer* renderer)
	: x(xPos), y(yPos), velocity(velocityV), width(w), height(h), texture(tex), renderer(renderer) {}

void Obstacle::draw() {

	texture.setPosition(x, y);
	texture.renderTexture(renderer);	

}

void Obstacle::move(int x, int y) {
	texture.setPosition(x, y);
}

int i = 1;
bool Obstacle::collided(SDL_Rect& targetRect)
{
	
	if (x + 5 < (targetRect.x + targetRect.w) && (y + 8 < (targetRect.y + targetRect.h)) && ((x + width - 5) > targetRect.x) && ((y + height - 8) > targetRect.y))
	{
		printf("Collision!\n%d", i);
		i++;
		return true;
	}
	
	else {
		return false;
	}
	

}

int Obstacle::getWidth() const
{
	return width;
}

int Obstacle::getHeight() const
{
	return height;
}
