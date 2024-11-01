#include "Obstacule.h"

#include "Utilities/Utils.h"

namespace game
{
	namespace obstacule
	{
		void Move(Obstacule& o);

		Obstacule Create(Rectangle body, float speed, bool isAlive)
		{
			Obstacule newO;

			body.x -= body.width / 2;
			body.y -= body.height / 2;

			newO.body = body;
			newO.dir = Vector2{ 0, 0 };

			newO.speed = speed;
			newO.isAlive = isAlive;

			return newO;
		}

		void Update(Obstacule& o)
		{
			o.dir.x = -1.f;

			Move(o);
		}

		void Draw(Obstacule& o)
		{
			DrawRect(o.body, RED);
		}

		void Move(Obstacule& o)
		{
			o.body.x += o.dir.x * o.speed * GetFrameTime();
			o.body.y += o.dir.y * o.speed * GetFrameTime();
		}
	}
}