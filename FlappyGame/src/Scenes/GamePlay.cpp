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

				if (obs.body.x + obs.body.width < 0)
				{
					obs.body.x = static_cast<float>(GetScreenWidth());
					obs.body.y = static_cast<float>(GetRandomValue(0, GetScreenHeight() - static_cast<int>(obs.body.height)));
				}

				if (CheckCollision(pl.body, obs.body))
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

			}

			void InitEntities()
			{
				float randomY = static_cast<float>(GetRandomValue(200, GetScreenHeight() - static_cast<int>(obs.body.height / 2)));

				pl = player::Create(Rectangle{ static_cast<float>(GetScreenWidth() / 4),
										   static_cast<float>(GetScreenHeight()) / 2,
										   60,60 }, 300.f);

				obs = obstacule::Create(Rectangle{ static_cast<float>(GetScreenWidth() + 20),
												   randomY,
												   40,400 }, 500.f);
			}

		}
	}
}