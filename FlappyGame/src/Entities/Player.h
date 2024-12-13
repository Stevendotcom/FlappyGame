#pragma once

#include "raylib.h"

namespace game::entities::player
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

	Player Create(Rectangle body, float speed = 100.f, bool isAlive = true, bool secondPlayer = false);

	void Input(Player& player, int key = KEY_SPACE);
	void Update(Player& player);
	void Draw(Player& player);
	void Restart(Player& player, float x, float y);
	void DeInit(Player& player);
}