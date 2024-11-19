#pragma once

#include "raylib.h"

namespace game::entities::obstacle
{
	struct Obstacle
	{
		Rectangle body1;
		Rectangle body2;
		Texture2D texture;
		Vector2 dir;

		float speed;

		bool isAlive;
	};


	Obstacle Create(float x, float y, float width, float height, float speed = 50.f, bool isAlive = false);

	void Update(Obstacle &obstacle);
	void Draw(const Obstacle &obstacle);
	void SetPosition(Obstacle &obstacle, Vector2 newPos);
	void DeInit(Obstacle &Obstacle);
}