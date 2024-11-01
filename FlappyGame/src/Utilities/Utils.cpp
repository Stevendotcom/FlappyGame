#include "Utils.h"

#include <iostream>

bool CheckCollision(Rectangle r1, Rectangle r2)
{
	float r1X2 = r1.x + r1.width;

	float r1Y = r1.y + r1.height;

	float r2X2 = r2.x + r2.width;

	float r2Y = r2.y + r2.height;

	return	(r1X2 >= r2.x &&
		r2X2 >= r1.x &&
		r1Y >= r2.y &&
		r2Y >= r1.y);
}

bool CheckBorderCollision(Rectangle rect, int maxWidth, int minWidth, int maxHeight, int minHeight)
{
	if (rect.y >= maxHeight - rect.height || rect.y <= minHeight)
		return true;

	if (rect.x >= maxWidth - rect.width || rect.x <= minWidth)
		return true;

	return false;
}

TYPE_PENETRATION SolveCollisionMap(Rectangle& entity, int maxWidth, int minWidth, int maxHeight, int minHeight)
{
	TYPE_PENETRATION typeOfPenetration = TYPE_PENETRATION::NONE;

	float halfWidth = (entity.width / 2);
	float halfHeight = (entity.height / 2);

	float entityCenteredPosX = entity.x + halfWidth;
	float entityCenteredPosY = entity.y + halfHeight;

	float minHorDistance = entityCenteredPosX - halfWidth - minWidth;
	float maxHorDistance = entityCenteredPosX + halfWidth;

	float minVerDistance = entityCenteredPosY - halfHeight - minHeight;
	float maxVerDistance = entityCenteredPosY + halfHeight;

	bool downHorPenetration = maxHorDistance > maxWidth - halfWidth;
	bool upHorPenetration = minHorDistance < minWidth;

	bool downVerPenetration = maxVerDistance > maxHeight - halfHeight;
	bool upVerPenetration = minVerDistance < minHeight;

	Vector2 separation;
	separation.x = 0;
	separation.y = 0;

	if (downHorPenetration)
		separation.x = maxHorDistance - minWidth;
	else if (upHorPenetration)
		separation.x = minHorDistance;

	if (downVerPenetration)
		separation.y = maxVerDistance - maxHeight;
	else if (upVerPenetration)
		separation.y = minVerDistance;

	if (downVerPenetration || upVerPenetration)
		typeOfPenetration = VERTICAL;

	if (downHorPenetration || upHorPenetration)
		typeOfPenetration = HORIZONTAL;

	entity.x -= separation.x;
	entity.y -= separation.y;

	return typeOfPenetration;
}

Vector2 NormalizeVector(Vector2 vector)
{
	Vector2 zero;
	zero.x = 0;
	zero.y = 0;

	float length = sqrt(vector.x * vector.x + vector.y * vector.y);

	vector.x = (length > 0.f) ? vector.x / length : zero.x;
	vector.y = (length > 0.f) ? vector.y / length : zero.y;

	return vector;
}

void NormalizeVector(float& x, float& y)
{
	Vector2 zero;
	zero.x = 0;
	zero.y = 0;

	float length = sqrt(x * x + y * y);

	x = (length > 0.f) ? x / length : zero.x;
	y = (length > 0.f) ? y / length : zero.y;
}

float GetMagnitud(Vector2 vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

double RadiansToGrades(double r)
{
	return r * (180.0 / PI);
}

double GradesToRadians(double r)
{
	return r * (PI / 180.0);
}
