#include "Player.h"

#include "Utilities/SoundManager.h"
#include "Utilities/Utils.h"

namespace game::entities::player
{
	void Gravity(Player &player);

	void Move(Player &player);

	void Jump(Player &player);

	void Animation(Player &player);



	Player Create(Rectangle body, float speed, bool isAlive, bool secondPlayer)
	{
		Player newPlayer;

		body.x -= body.width / 2;
		body.y -= body.height / 2;

		newPlayer.body = body;
		newPlayer.velocity = Vector2{ 0, 0 };

		newPlayer.origin = Vector2{ body.width, body.height };
		newPlayer.source = Rectangle{ 0, 0, 32, 32 };

		if (secondPlayer)
			newPlayer.texture = LoadTexture("res/Cannon2.png");
		else
			newPlayer.texture = LoadTexture("res/Cannon.png");

		newPlayer.animationStage = 0;
		newPlayer.maxAnimationStage = 4;

		newPlayer.speed = speed;

		newPlayer.timer = 0.f;
		newPlayer.resetTimer = 0.05f;

		newPlayer.activeAnimation = false;
		newPlayer.isAlive = isAlive;

		return newPlayer;
	}



	void Input(Player &player, int key)
	{
		if (IsKeyPressed(key))
		{
			AddToBuffer(utils::soundManager::Sounds::Jump);
			Jump(player);
		}
	}



	void Update(Player &player)
	{
		Move(player);
		//Jump(p);
		Gravity(player);

		Animation(player);

		player.timer -= (GetFrameTime() < player.timer) ? GetFrameTime() : player.timer;
	}



	void Draw(Player &player)
	{
#ifdef _DEBUG
		DrawRect(player.body, BLUE);
#endif // _DEBUG

		DrawTexturePro(player.texture, player.source, player.body, player.origin, 195, WHITE);
	}



	void Restart(Player &player, float x, float y)
	{
		player.body.x = x;
		player.body.y = y;
		player.velocity = {0,0};
		player.isAlive = true;
	}



	void DeInit(Player &player)
	{
		UnloadTexture(player.texture);
	}



	void Gravity(Player &player)
	{
		player.velocity.y += 980.f * GetFrameTime();
	}



	void Move(Player &player)
	{
		player.body.x += player.velocity.x * player.speed * GetFrameTime();
		player.body.y += player.velocity.y * GetFrameTime();
	}



	void Jump(Player &player)
	{
		player.velocity.y = -350.f;
		player.activeAnimation = true;
		player.animationStage = 1;

	}



	void Animation(Player &player)
	{
		if (player.activeAnimation && player.timer <= 0)
		{
			player.source.y = player.source.height * static_cast<float>(player.animationStage);

			switch (player.animationStage)
			{
			case 0:
				player.activeAnimation = false;
				player.animationStage++;
				break;

			case 4:
				player.animationStage = 0;
				break;
			}

			if (player.animationStage != 0)
				player.animationStage++;

			player.timer = player.resetTimer;
		}
	}
}