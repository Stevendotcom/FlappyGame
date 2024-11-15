#include "Player.h"

#include "Utilities/Utils.h"

namespace game::entities::player
{
	void Gravity(Player& p);
	void Move(Player& p);
	void Jump(Player& p);

	void Animation(Player& p);

	Player Create(Rectangle body, float speed, bool isAlive)
	{
		Player newP;

		body.x -= body.width / 2;
		body.y -= body.height / 2;

		newP.body = body;
		newP.velocity = Vector2{ 0, 0 };

		newP.origin = Vector2{ body.width, body.height };
		newP.source = Rectangle{ 0, 0, 32, 32 };

		newP.texture = LoadTexture("res/Cannon.png");

		newP.animationStage = 0;
		newP.maxAnimationStage = 4;

		newP.speed = speed;

		newP.timer = 0.f;
		newP.resetTimer = 0.05f;

		newP.activeAnimation = false;
		newP.isAlive = isAlive;

		return newP;
	}

	void Input(Player& p, int key)
	{
		if (IsKeyPressed(key))
		{
			Jump(p);
		}
	}

	void Update(Player& p)
	{
		Move(p);
		//Jump(p);
		Gravity(p);

		Animation(p);

		p.timer -= (GetFrameTime() < p.timer) ? GetFrameTime() : p.timer;
	}

	void Draw(Player& p)
	{
#ifdef _DEBUG
		DrawRect(p.body, BLUE);
#endif // _DEBUG

		DrawTexturePro(p.texture, p.source, p.body, p.origin, 195, WHITE);
	}

	void DeInit(Player& p)
	{
		UnloadTexture(p.texture);
	}

	void Gravity(Player& p)
	{
		p.velocity.y += 980.f * GetFrameTime();
	}

	void Move(Player& p)
	{
		p.body.x += p.velocity.x * p.speed * GetFrameTime();
		p.body.y += p.velocity.y * GetFrameTime();
	}
	void Jump(Player& p)
	{
		p.velocity.y = -350.f;
		p.activeAnimation = true;
		p.animationStage = 1;

	}
	void Animation(Player& p)
	{
		if (p.activeAnimation && p.timer <= 0)
		{
			p.source.y = p.source.height * static_cast<float>(p.animationStage);

			switch (p.animationStage) {
			case 0:
				p.activeAnimation = false;
				p.animationStage++;
				break;

			case 4:
				p.animationStage = 0;
				break;
			}

			if (p.animationStage != 0)
				p.animationStage++;

			p.timer = p.resetTimer;
		}
	}
}