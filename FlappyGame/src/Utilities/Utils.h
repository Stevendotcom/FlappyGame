#pragma once

#include "raylib.h"

enum TYPE_PENETRATION
{
	HORIZONTAL,
	VERTICAL,
	NONE
};

bool CheckCollision(Rectangle, Rectangle);


bool CheckBorderCollision(Rectangle, int maxWidth, int minWidth, int maxHeight, int minHeight);

TYPE_PENETRATION SolveCollisionMap(Rectangle&, int maxWidth, int minWidth, int maxHeight, int minHeight);

Vector2 NormalizeVector(Vector2 vector);
void NormalizeVector(float& x, float& y);

float GetMagnitud(Vector2 vector);

double RadiansToGrades(double r);
double GradesToRadians(double r);

