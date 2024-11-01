#include "Player.h"

#include "Utilities/Utils.h"

namespace game
{
	namespace player
	{
		void Move(Player& p);

		Player Create(Rectangle body, float speed, bool isAlive)
		{
			Player newP;

			body.x -= body.width / 2;
			body.y -= body.height / 2;

			newP.body = body;
			newP.dirUD = Vector2{ 0, 0 };

			newP.speed = speed;
			newP.isAlive = isAlive;

			return newP;
		}

		void Input(Player& p)
		{
			if (IsKeyDown(KEY_W))
				p.dirUD.y = -1.f;
			else if (IsKeyDown(KEY_S))
				p.dirUD.y = 1.f;
			else if (p.dirUD.y != 0.f)
				p.dirUD.y = 0.f;
		}

		void Update(Player& p)
		{
			Move(p);
		}

		void Draw(Player& p)
		{
			DrawRect(p.body, BLUE);
		}

		void Move(Player& p)
		{
			p.body.x += p.dirUD.x * p.speed * GetFrameTime();
			p.body.y += p.dirUD.y * p.speed * GetFrameTime();
		}
	}
}
