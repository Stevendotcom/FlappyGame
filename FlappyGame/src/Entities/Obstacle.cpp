#include "Obstacle.h"

#include "Utilities/Utils.h"

namespace game::entities::obstacle
{
	const float separation = 1.7f;

	void Move(Obstacle &obstacle);



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

		newObstacle.texture = LoadTexture("res/giraffe.png");

		return newObstacle;
	}



	void Update(Obstacle &obstacle)
	{
		obstacle.dir.x = -1.f;

		Move(obstacle);
	}



	void Draw(const Obstacle &obstacle)
	{
#ifdef _DEBUG
		DrawRect(obstacle.body1, RED);
		DrawRect(obstacle.body2, RED);
#endif

		const float scale = 5;

		const float spriteHeight = (static_cast<float>(obstacle.texture.height) / 2.0f);

		Rectangle source = { 0, 0, static_cast<float>(obstacle.texture.width), spriteHeight };

		Rectangle dest;

		float body1Start = obstacle.body1.y - spriteHeight * scale  * 2;

		//body 1
		dest = { obstacle.body1.x - spriteHeight * scale / 4, body1Start , spriteHeight * scale, spriteHeight * scale };
		DrawTexturePro(obstacle.texture, source, dest, {spriteHeight * scale, 0}, -180 ,WHITE);

		source = { 0, spriteHeight, static_cast<float>(obstacle.texture.width), spriteHeight };
		for (int i = static_cast<int>(dest.y / spriteHeight); i >= 0; i--)
		{
			dest.y -= spriteHeight * scale;
			DrawTexturePro(obstacle.texture, source, dest, {spriteHeight * scale, 0}, -180 ,WHITE);
		}

		// body 2
		source = { 0, 0, static_cast<float>(obstacle.texture.width), spriteHeight };
		dest = { obstacle.body2.x - spriteHeight * scale / 4,  body1Start + spriteHeight * scale  * 2 - 10, spriteHeight * scale, spriteHeight * scale };
		DrawTexturePro(obstacle.texture, source, dest, {0, 0}, 0 ,WHITE);
		source = { 0, spriteHeight, static_cast<float>(obstacle.texture.width), spriteHeight };
		for (int i = 0; i < static_cast<int>(obstacle.body2.height / (spriteHeight * scale)); i++)
		{
			dest.y += spriteHeight * scale;
			DrawTexturePro(obstacle.texture, source, dest, {0, 0}, 0 ,WHITE);
		}

	}



	void SetPosition(Obstacle &obstacle, const Vector2 newPos)
	{
		obstacle.body1.x = newPos.x;
		obstacle.body1.y = newPos.y + obstacle.body1.height / separation;

		obstacle.body2.x = newPos.x;
		obstacle.body2.y = newPos.y - obstacle.body2.height / separation;
	}



	void Move(Obstacle &obstacle)
	{
		obstacle.body1.x += obstacle.dir.x * obstacle.speed * GetFrameTime();
		obstacle.body1.y += obstacle.dir.y * obstacle.speed * GetFrameTime();

		obstacle.body2.x += obstacle.dir.x * obstacle.speed * GetFrameTime();
		obstacle.body2.y += obstacle.dir.y * obstacle.speed * GetFrameTime();
	}
}