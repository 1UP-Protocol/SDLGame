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

		// Square will only move if distance is less than 150
		if (distance <= 150)
		{
			// Creates a speed that depends on how far/close the cursor is to the center
			speed = (1 / (.5 * distance)) * multiplier;

			xSpeed = -(speed * cos(invertedAngleTheta - pi));
			ySpeed = speed * sin(invertedAngleTheta - pi);
		}
		
	}

	// Quadrant II
	if (xMousePosition < centerX && yMousePosition < centerY)
	{
		oppositeSide = (centerX - xMousePosition) * 1.00;

		distance = getDistanceMouseToCenter(centerX, centerY);
		angleTheta = (getAngleTheta(distance, oppositeSide)  + pi/2);
		// Creates an angle that goes the opposite direction, angle is now in Quadrant IV
		invertedAngleTheta = angleTheta + pi;

		if (distance <= 150)
		{
			// Creates a speed that depends on how far/close the cursor is to the center
			speed = (1 / (.5 * distance)) * multiplier;
			// Apply opposite quadrant stuff
			 
			xSpeed = speed * sin(invertedAngleTheta - 3 * pi / 2);
			ySpeed = (speed * cos(invertedAngleTheta - 3 * pi / 2));
			
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
			speed = (1 / (.5 * distance)) * multiplier;

			xSpeed = speed * cos(invertedAngleTheta);
			ySpeed = -(speed * sin(invertedAngleTheta));
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
			speed = (1 / (.5 * distance)) * multiplier;

			xSpeed = round(-speed * sin(invertedAngleTheta - pi / 2));
			ySpeed = round(- (speed * cos(invertedAngleTheta - pi / 2)));
			
		}
		
		
	}

	if (xSpeed >= 1 || xSpeed <= -1)
	{
		targetRectangle.x += (int)xSpeed;
		xSpeed = 0;
	}
	if (ySpeed >= 1 || ySpeed <= -1)
	{
		targetRectangle.y += (int)ySpeed;
		ySpeed = 0;
	}
	printf("Distance: %f, Angle: %f rad", distance, angleTheta);
	printf(" | The opposite angle: %f | ", invertedAngleTheta);
	printf("The speed: %f | ", speed);
	printf("x: %f, y: %f\n", xSpeed, ySpeed);
	// Move the Rectangle
	
}

float MouseEvents::getDistanceMouseToCenter(int targetX, int targetY)
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