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
float xSpeed;
float ySpeed;
float speed;
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

		// Square will only move if distance is less than 80
		if (distance <= 150)
		{
			// Creates a speed that depends on how far/close the cursor is to the center
			speed = (1 / (.5 * distance)) * 75;
			xSpeed = -(speed * cos(invertedAngleTheta - pi));
			ySpeed = speed * sin(invertedAngleTheta - pi);
		}
		else
		{
			xSpeed = 0;
			ySpeed = 0;
		}
	}

	// Quadrant II
	else if (xMousePosition < centerX && yMousePosition < centerY)
	{
		oppositeSide = (centerX - xMousePosition);

		distance = getDistanceMouseToCenter(centerX, centerY);
		angleTheta = (getAngleTheta(distance, oppositeSide)  + pi/2);
		// Creates an angle that goes the opposite direction, angle is now in Quadrant IV
		invertedAngleTheta = angleTheta + pi;

		if (distance <= 150)
		{
			// Creates a speed that depends on how far/close the cursor is to the center
			speed = (1 / (.5 * distance)) * 75;
			// Apply opposite quadrant stuff
			xSpeed = speed * sin(invertedAngleTheta - (3 * pi) / 2);
			ySpeed = (speed * cos(invertedAngleTheta - (3 * pi) / 2));
		}
		else
		{
			xSpeed = 0;
			ySpeed = 0;
		}
	}

	// Quadrant III
	else if (xMousePosition < centerX && yMousePosition > centerY)
	{
		oppositeSide = (yMousePosition - centerY);

		distance = getDistanceMouseToCenter(centerX, centerY);
		angleTheta = (getAngleTheta(distance, oppositeSide) + pi);
		// Creates an angle that goes the opposite direction, angle is now in Quadrant I
		invertedAngleTheta = angleTheta - pi;

		if (distance <= 150)
		{
			// Creates a speed that depends on how far/close the cursor is to the center
			speed = (1 / (.5 * distance)) * 75;

			xSpeed = speed * cos(invertedAngleTheta);
			ySpeed = -(speed * sin(invertedAngleTheta));
		}
		else
		{
			xSpeed = 0;
			ySpeed = 0;
		}
	}

	// Quadrant IV
	else if (xMousePosition > centerX && yMousePosition > centerY)
	{
		oppositeSide = (xMousePosition - centerX);

		distance = getDistanceMouseToCenter(centerX, centerY);
		angleTheta = (getAngleTheta(distance, oppositeSide) + (3*pi)/2);
		// Creates an angle that goes the opposite direction, angle is now in Quadrant II
		invertedAngleTheta = angleTheta - pi;

		if (distance <= 150)
		{
			// Creates a speed that depends on how far/close the cursor is to the center
			speed = (1 / (.5 * distance)) * 75;
			xSpeed = -speed * sin(invertedAngleTheta - pi / 2);
			ySpeed = -(speed * cos(invertedAngleTheta - pi / 2));
		}
		else
		{
			xSpeed = 0;
			ySpeed = 0;
		}
	}

	printf("Distance: %f, Angle: %f rad", distance, angleTheta);
	printf(" | The opposite angle: %f | ", invertedAngleTheta);
	printf("The speed: %f | ", speed);
	printf("x: %f, y: %f\n", xSpeed, ySpeed);
	// Move the Rectangle
	targetRectangle.x += xSpeed;
	targetRectangle.y += ySpeed;
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