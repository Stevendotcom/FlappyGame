#pragma once

#include "raylib.h"

namespace game
{
	namespace obstacle
	{
		struct Obstacle
		{
			Rectangle body1;
			Rectangle body2;

			Vector2 dir;

			float speed;

			bool isAlive;
		};


		Obstacle Create(float x, float y, float width, float height, float speed = 50.f, bool isAlive = false);

		void Update(Obstacle &o);
		void Draw(Obstacle &o);

		void SetPosition(Obstacle &o, Vector2 newPos);
	}
}