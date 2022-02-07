#include "Mouse.h"
#define pi 3.14159
MouseEvents::MouseEvents()
{
	SDL_GetMouseState(&xMousePosition, &yMousePosition);
}

void MouseEvents::getMousePosition()
{
	SDL_GetMouseState(&xMousePosition, &yMousePosition);
}

void MouseEvents::moveAwayFromMouse(SDL_Rect& targetRectangle, int centerX, int centerY)
{
	// First, we determine in which quadrant the cursor is ========================================
	// Quadrant I
	if (xMousePosition > centerX && yMousePosition < centerY)
	{
		oppositeSide = (centerY - yMousePosition);

		distance = getDistanceMouseToCenter(centerX, centerY);
		angleTheta = getAngleTheta(distance, oppositeSide);
		// Creates an angle that goes the opposite direction, angle is now in Quadrant III
		invertedAngleTheta = angleTheta + pi;
	}

	// Quadrant II
	else if (xMousePosition < centerX && yMousePosition < centerY)
	{
		oppositeSide = (centerX - xMousePosition);

		distance = getDistanceMouseToCenter(centerX, centerY);
		angleTheta = (getAngleTheta(distance, oppositeSide)  + pi/2);
		// Creates an angle that goes the opposite direction, angle is now in Quadrant IV
		invertedAngleTheta = angleTheta + pi;
	}

	// Quadrant III
	else if (xMousePosition < centerX && yMousePosition > centerY)
	{
		oppositeSide = (yMousePosition - centerY);

		distance = getDistanceMouseToCenter(centerX, centerY);
		angleTheta = (getAngleTheta(distance, oppositeSide) + pi);
		// Creates an angle that goes the opposite direction, angle is now in Quadrant I
		invertedAngleTheta = angleTheta - pi;
	}

	// Quadrant IV
	else if (xMousePosition > centerX && yMousePosition > centerY)
	{
		oppositeSide = (xMousePosition - centerX);

		distance = getDistanceMouseToCenter(centerX, centerY);
		angleTheta = (getAngleTheta(distance, oppositeSide) + (3*pi)/2);
		// Creates an angle that goes the opposite direction, angle is now in Quadrant II
		invertedAngleTheta = angleTheta - pi;
	}

	printf("The distance is: %f, and the angle from the center is: %f degrees", distance, angleTheta);
	printf(" | The opposite angle is %f\n", invertedAngleTheta);
}

float MouseEvents::getDistanceMouseToCenter(float targetX, float targetY)
{
	float d = sqrt(pow((xMousePosition - targetX), 2) + pow((yMousePosition - targetY), 2 ));
	return d;
}

float MouseEvents::getAngleTheta(float distance, float oppositeSide)
{
	float angle = asin(oppositeSide / distance);
	return angle;
}


int MouseEvents::getMouseX() const
{
	return xMousePosition;
}

int MouseEvents::getMouseY() const
{
	return yMousePosition;
}