#include "Obstacle.h"

#include "Utilities/Utils.h"

namespace game::entities::obstacle
{
	const float separation = 1.7f;

	void Move(Obstacle& obstacle);

	Obstacle Create(float x, float y, float width, float height, float speed, bool isAlive)
	{
		Obstacle newObstacle;

		Rectangle newRectangle;

		newRectangle.x = x - width / 2;
		newRectangle.y = y - height / 2;

		newRectangle.width = width;
		newRectangle.height = height;

		newObstacle.body1 = newRectangle;
		newObstacle.body1.y += newObstacle.body1.height / separation;

		newObstacle.body2 = newRectangle;
		newObstacle.body2.y -= newObstacle.body2.height / separation;

		newObstacle.dir = Vector2{ 0, 0 };

		newObstacle.speed = speed;
		newObstacle.isAlive = isAlive;

		return newObstacle;
	}

	void Update(Obstacle& obstacle)
	{
		obstacle.dir.x = -1.f;

		Move(obstacle);
	}

	void Draw(const Obstacle& obstacle)
	{
		DrawRect(obstacle.body1, RED);
		DrawRect(obstacle.body2, RED);
	}

	void SetPosition(Obstacle& obstacle, const Vector2 newPos)
	{
		obstacle.body1.x = newPos.x;
		obstacle.body1.y = newPos.y + obstacle.body1.height / separation;

		obstacle.body2.x = newPos.x;
		obstacle.body2.y = newPos.y - obstacle.body2.height / separation;
	}

	void Move(Obstacle& obstacle)
	{
		obstacle.body1.x += obstacle.dir.x * obstacle.speed * GetFrameTime();
		obstacle.body1.y += obstacle.dir.y * obstacle.speed * GetFrameTime();

		obstacle.body2.x += obstacle.dir.x * obstacle.speed * GetFrameTime();
		obstacle.body2.y += obstacle.dir.y * obstacle.speed * GetFrameTime();
	}
}