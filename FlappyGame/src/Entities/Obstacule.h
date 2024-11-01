#pragma once

#include "raylib.h"

namespace game
{
	namespace obstacule
	{
		struct Obstacule
		{
			Rectangle body;

			Vector2 dir;

			float speed;

			bool isAlive;
		};

		Obstacule Create(Rectangle body, float speed = 50.f, bool isAlive = false);

		void Update(Obstacule& o);
		void Draw(Obstacule& o);
	}
}