#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "RenderWindow.h"
#include "Texture.h"
#include "Mouse.h"
#include <cmath>

const int screenWidth = 720;
const int screenHeight = 600;
RenderWindow gWindow("My SDL Game", screenWidth, screenHeight);
Texture heart;
SDL_Rect rectangle = { 150, 150, 50, 50 };
MouseEvents mouse;

void quit();
bool init();
void movingDVD(SDL_Rect& rectangle);
void rectMouseMovement(SDL_Rect& targetRectangle, int xMousePos, int yMousePos);
void setBorder(SDL_Rect& targetRect);
void drawCircleAroundPoint(int centerX, int centerY, int radius);

int main(int args, char* argv[]) {

	SDL_Event e;
	
	// Initialize Shit
	heart.createSourceRectangle(0, 0, 346, 330);
	bool gameRunning = true;
	if (init())
	{
		// Enter Main Game Loop
		while (gameRunning)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					gameRunning = false;
				}
			}

			
			gWindow.Clear();

			// Draw Geometry here ==============================================
			SDL_SetRenderDrawColor(gWindow.getRenderer(), 255, 255, 255, 255);
			SDL_RenderFillRect(gWindow.getRenderer(), &rectangle);
			// Geometry End here ================================================

			heart.renderTexture(gWindow.getRenderer());
			
			// Draw a dot
			SDL_SetRenderDrawColor(gWindow.getRenderer(), 255, 0, 0, 255);
			SDL_RenderDrawPoint(gWindow.getRenderer(), rectangle.x + (rectangle.w / 2), rectangle.y + (rectangle.h / 2));
			

			drawCircleAroundPoint(rectangle.x + (rectangle.w / 2), rectangle.y + (rectangle.h / 2), 150);
			drawCircleAroundPoint(rectangle.x + (rectangle.w / 2), rectangle.y + (rectangle.h / 2), 5);
			// Display Screen THIS GOES LAST SO EVERYTHING THAT SHOULD BE RENDERED ON SCREEN GOES ON TOP OF THIS!!11!!!!
			gWindow.setColor(0, 0, 0, 255);
			gWindow.Present();

			// Update Shit here lol---------------------------------------------------
			
			mouse.getMousePosition();
			
			mouse.moveAwayFromMouse(rectangle, static_cast<float>(rectangle.x) + (rectangle.w / 2.0f), static_cast<float>(rectangle.y) + (rectangle.h / 2.0f));
			setBorder(rectangle);
			// rectMouseMovement(rectangle, mouse.getMouseX() , mouse.getMouseY());
		}
		// End Main Game Loop
	}
	
	gWindow.Quit();
	quit();
	return 0;
}

void quit() {

	SDL_Quit();
	IMG_Quit();
}

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error, could not initialize the video! ERROR: %s", SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		printf("Error, could not initialize PNG! ERROR: %s", IMG_GetError());
		return false;
	}
	if (!gWindow.CreateWindow())
		return false;

	if (!heart.loadTexture("Assets/MinecraftHeart.png", gWindow.getRenderer()))
		return false;

	return true;
}
int moveSpeedDVD = 1;
int moveY = moveSpeedDVD;
int moveX = moveSpeedDVD;

void movingDVD(SDL_Rect &rectangle)
{
	
	if (rectangle.x + rectangle.w >= screenWidth)
		moveX = -moveSpeedDVD;
	if (rectangle.x <= 0)
		moveX = moveSpeedDVD;
	if (rectangle.y + rectangle.h >= screenHeight)
		moveY = -moveSpeedDVD;
	if (rectangle.y <= 0)
		moveY = moveSpeedDVD;

	rectangle.x += moveX;
	rectangle.y += moveY;

}

int distanceLimit = 60;
void rectMouseMovement(SDL_Rect& targetRectangle, int xMousePos, int yMousePos)
{
	// Left <-

	if ((targetRectangle.x - xMousePos) < distanceLimit && (targetRectangle.x - xMousePos) > 0 && (targetRectangle.y < yMousePos && targetRectangle.y + targetRectangle.h > yMousePos) )
		targetRectangle.x += moveSpeedDVD;

	// Top 
	if ((targetRectangle.y - yMousePos) < distanceLimit && (targetRectangle.y - yMousePos) > 0 && (targetRectangle.x < xMousePos && targetRectangle.x + targetRectangle.w > xMousePos))
		targetRectangle.y += moveSpeedDVD;

	// Right ->
	if ((xMousePos - (targetRectangle.x + targetRectangle.w)) < distanceLimit && (xMousePos - (targetRectangle.x + targetRectangle.w) > 0 && (targetRectangle.y < yMousePos && targetRectangle.y + targetRectangle.h > yMousePos)))
		targetRectangle.x -= moveSpeedDVD;

	// Bottom \/
	if ((yMousePos - (targetRectangle.y + targetRectangle.h)) < distanceLimit && (yMousePos - (targetRectangle.y + targetRectangle.h) > 0 && (targetRectangle.x < xMousePos && targetRectangle.x + targetRectangle.w > xMousePos)))
		targetRectangle.y -= moveSpeedDVD;	
	
}

void setBorder(SDL_Rect& targetRect)
{
	if (targetRect.x <= 0)
		targetRect.x = 0;
	if (targetRect.y <= 0)
		targetRect.y = 0;
	if (targetRect.x + targetRect.w >= screenWidth)
		targetRect.x = screenWidth - targetRect.w;
	if (targetRect.y + targetRect.h >= screenHeight)
		targetRect.y = screenHeight - targetRect.h;
}

// Draws a circle around a point lol
void drawCircleAroundPoint(int centerX, int centerY, int radius)
{
	
	int radiusSquared = pow(radius, 2);
	int y;
	// Draw a circle
	for (int x = -radius; x != radius; x++)
	{
		y = sqrt(radiusSquared - pow(x, 2));
		SDL_RenderDrawPoint(gWindow.getRenderer(), centerX - x, centerY - y);
		SDL_RenderDrawPoint(gWindow.getRenderer(), centerX - x, centerY + y);
		
	}
	
}
