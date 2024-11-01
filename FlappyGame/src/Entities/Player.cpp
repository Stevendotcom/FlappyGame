#include "Player.h"

#include "Utilities/Utils.h"

namespace game
{
	namespace player
	{
		void Gravity(Player& p);
		void Move(Player& p);
		void Jump(Player& p);

		Player Create(Rectangle body, float speed, bool isAlive)
		{
			Player newP;

			body.x -= body.width / 2;
			body.y -= body.height / 2;

			newP.body = body;
			newP.velocity = Vector2{ 0, 0 };

			newP.speed = speed;
			newP.isAlive = isAlive;

			return newP;
		}

		void Input(Player& p)
		{
	/*		if (IsKeyDown(KEY_W))
				p.velocity.y = -1.f;
			else if (IsKeyDown(KEY_S))
				p.velocity.y = 1.f;
			else if (p.velocity.y != 0.f)
				p.velocity.y = 0.f;*/
			p;
		}

		void Update(Player& p)
		{
			Move(p);
			Jump(p);
			Gravity(p);
		}

		void Draw(Player& p)
		{
			DrawRect(p.body, BLUE);
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
			if (IsKeyPressed(KEY_SPACE))
			{
				p.velocity.y = -350.f;
			}
		}
	}
}
