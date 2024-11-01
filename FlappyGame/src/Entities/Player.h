#pragma once

#include "raylib.h"

namespace game
{
	namespace player
	{
		struct Player
		{
			Rectangle body;

			Vector2 velocity;

			float speed;

			bool isAlive;
		};

		Player Create(Rectangle body, float speed = 100.f, bool isAlive = true);

		void Input(Player& p);
		void Update(Player& p);
		void Draw(Player& p);
	}
}