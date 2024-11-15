#pragma once

#include "raylib.h"

namespace game::entities
{
	struct Player
	{
		Rectangle source;
		Rectangle body;
		Vector2 origin;

		Texture2D texture;

		Vector2 velocity;

		int animationStage;
		int maxAnimationStage;

		float speed;

		float timer;
		float resetTimer;

		bool activeAnimation;
		bool isAlive;
	};

	Player Create(Rectangle body, float speed = 100.f, bool isAlive = true);

	void Input(Player& p, int key = KEY_SPACE);
	void Update(Player& p);
	void Draw(Player& p);

	void DeInit(Player& p);
}