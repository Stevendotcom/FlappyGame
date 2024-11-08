#include "Utils.h"

#include <iostream>

bool CheckCollision(const Rectangle &r1, const Rectangle &r2)
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

bool CheckBorderCollision(const Rectangle &rect, int maxWidth, int minWidth, int maxHeight, int minHeight)
{
	if (rect.y >= static_cast<float>(maxHeight) - rect.height || rect.y <= static_cast<float>(minHeight))
		return true;

	if (rect.x >= static_cast<float>(maxWidth) - rect.width || rect.x <= static_cast<float>(minWidth))
		return true;

	return false;
}

CollisionPlace SolveCollisionMap(Rectangle& entity, int maxWidth, int minWidth, int maxHeight, int minHeight)
{
	auto typeOfPenetration = CollisionPlace::None;

	float halfWidth = (entity.width / 2);
	float halfHeight = (entity.height / 2);

	float entityCenteredPosX = entity.x + halfWidth;
	float entityCenteredPosY = entity.y + halfHeight;

	float minHorDistance = entityCenteredPosX - halfWidth - static_cast<float>(minWidth);
	float maxHorDistance = entityCenteredPosX + halfWidth;

	float minVerDistance = entityCenteredPosY - halfHeight - static_cast<float>(minHeight);
	float maxVerDistance = entityCenteredPosY + halfHeight;

	bool downHorPenetration = maxHorDistance > static_cast<float>(maxWidth) - halfWidth;
	bool upHorPenetration = minHorDistance < static_cast<float>(minWidth);

	bool downVerPenetration = maxVerDistance > static_cast<float>(maxHeight) - halfHeight;
	bool upVerPenetration = minVerDistance < static_cast<float>(minHeight);

	Vector2 separation;
	separation.x = 0;
	separation.y = 0;

	if (downHorPenetration)
		separation.x = maxHorDistance - static_cast<float>(minWidth);
	else if (upHorPenetration)
		separation.x = minHorDistance;

	if (downVerPenetration)
		separation.y = maxVerDistance - static_cast<float>(maxHeight);
	else if (upVerPenetration)
		separation.y = minVerDistance;

	if (downVerPenetration || upVerPenetration)
		typeOfPenetration = CollisionPlace::Vertical;

	if (downHorPenetration || upHorPenetration)
		typeOfPenetration = CollisionPlace::Horizontal;

	entity.x -= separation.x;
	entity.y -= separation.y;

	return typeOfPenetration;
}

void DrawRect(const Rectangle &rect, Color color)
{
	DrawRectangle(static_cast<int>(rect.x), 
				  static_cast<int>(rect.y),
				  static_cast<int>(rect.width),
				  static_cast<int>(rect.height),
		          color);
}

Vector2 NormalizeVector(Vector2 vector)
{
	Vector2 zero;
	zero.x = 0;
	zero.y = 0;

	float length = sqrt(vector.x * vector.x + vector.y * vector.y);

	vector.x = (length > 0.0f) ? vector.x / length : zero.x;
	vector.y = (length > 0.0f) ? vector.y / length : zero.y;

	return vector;
}

void NormalizeVector(float& x, float& y)
{
	Vector2 zero;
	zero.x = 0;
	zero.y = 0;

	float length = sqrt(x * x + y * y);

	x = (length > 0.0f) ? x / length : zero.x;
	y = (length > 0.0f) ? y / length : zero.y;
}

float GetMagnitud(const Vector2& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

double RadiansToGrades(double r)
{
	return r * (180.0f / PI);
}

double GradesToRadians(double r)
{
	return r * (PI / 180.0f);
}
