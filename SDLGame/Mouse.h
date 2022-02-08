#pragma once
#include <SDL.h>
#include <stdio.h>
#include <cmath>


class MouseEvents
{
public:
	MouseEvents();
	void getMousePosition();

	// getters
	int getMouseX() const;
	int getMouseY() const;
	void moveAwayFromMouse(SDL_Rect& targetRectangle, int centerX, int centerY);
	float getDistanceMouseToCenter(float targetX, float targetY);
	float getAngleTheta(float distance, float oppositeSide);

private:
	int mouseDistance(int x, int y);
	int xMousePosition;
	int yMousePosition;

	// Trig stuff =+-=+-=+-=+-=+-=+-=+-=+-=+-=+-=+-=+-=+-
	
	// The opposite side relative to theta on a right triangle 
	float oppositeSide;
	// Distance from cursor to the center of the rectangle (hyponetuse)
	float distance;
	// Angle of mouse to center of rectangle
	float angleTheta;
	// Angle opposite to the position
	float invertedAngleTheta;
};
