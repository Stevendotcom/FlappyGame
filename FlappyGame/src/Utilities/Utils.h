#pragma once

#include "raylib.h"

enum class CollisionPlace
{
	Horizontal,
	Vertical,
	None
};

bool CheckCollision(const Rectangle &, const Rectangle &);

bool CheckBorderCollision(const Rectangle &, int maxWidth, int minWidth, int maxHeight, int minHeight);

CollisionPlace SolveCollisionMap(Rectangle&, int maxWidth, int minWidth, int maxHeight, int minHeight);

void DrawRect(const Rectangle &rect, Color color);

Vector2 NormalizeVector(Vector2 vector);

void NormalizeVector(float& x, float& y);

float GetMagnitud(const Vector2& vector);

double RadiansToGrades(double r);

double GradesToRadians(double r);

