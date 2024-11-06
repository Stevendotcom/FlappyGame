#include "GamePlay.h"

#include "GameLoop.h"

#include "Entities/Obstacule.h"
#include "Entities/Player.h"

#include "Utilities/Utils.h"

namespace game
{
	namespace scenes
	{
		namespace gameplay
		{
			player::Player pl;
			obstacule::Obstacule obs;

			void InitEntities();

			void Init()
			{

			}

			void Input()
			{
				player::Input(pl);

			}
			void Update()
			{
				player::Update(pl);
				obstacule::Update(obs);

				if (obs.body1.x + obs.body1.width < 0)
				{
					Vector2 newPos;

					newPos.x = static_cast<float>(GetScreenWidth());
					newPos.y = static_cast<float>(GetRandomValue(0, GetScreenHeight() - static_cast<int>(obs.body1.height)));

					obstacule::SetPosition(obs, newPos);
				}

				if (CheckCollision(pl.body, obs.body1) || CheckCollision(pl.body, obs.body2))
				{
					InitEntities();
					currentScene = SCENE::MENU;
				}

				if (CheckBorderCollision(pl.body, GetScreenWidth(), 0, GetScreenHeight(), 0))
				{
					if (pl.body.y < 0)
						pl.body.y = 0;
					if (pl.body.y + pl.body.height > GetScreenHeight())
					{
						InitEntities();
						currentScene = SCENE::MENU;
					}
				}
			}
			void Draw()
			{
				player::Draw(pl);
				obstacule::Draw(obs);
			}

			void DeInit()
			{
				player::DeInit(pl);
			}

			void InitEntities()
			{
				float randomY = static_cast<float>(GetRandomValue(200, GetScreenHeight() - static_cast<int>(obs.body1.height / 2)));

				float x = static_cast<float>(GetScreenWidth() / 4);
				float y = static_cast<float>(GetScreenHeight()) / 2;

				pl = player::Create(Rectangle{ x, y, 60, 60 }, 300.f);

				x = static_cast<float>(GetScreenWidth() + 20);
				obs = obstacule::Create(x, randomY, 40, 1000, 500.f);
			}

		}
	}
}