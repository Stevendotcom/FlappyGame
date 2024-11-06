#pragma once

#include "raylib.h"

namespace game
{
	namespace obstacule
	{
		struct Obstacule
		{
			Rectangle body1;
			Rectangle body2;

			Vector2 dir;

			float speed;

			bool isAlive;
		};

		Obstacule Create(float x, float y, float width, float height, float speed = 50.f, bool isAlive = false);

		void Update(Obstacule& o);
		void Draw(Obstacule& o);

		void SetPosition(Obstacule& o, Vector2 newPos);
	}
}