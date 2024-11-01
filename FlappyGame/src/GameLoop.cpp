#include "GameLoop.h"

#include "raylib.h"

#include "Entities/Obstacule.h"
#include "Entities/Player.h"

#include "Utilities/Utils.h"

namespace game
{
	const std::string GameName = "FlappyBird";

	int screenWidth = 1024;
	int screenHeight = 768;

	SCENE currentScene = SCENE::MENU;

	SCENE prevScene = SCENE::MENU;

	player::Player pl;
	obstacule::Obstacule obs;

	bool programLoop = true;

	void Init();

	void InitEntities();

	void Input();
	void Update();
	void Draw();

	void DeInit();

	void Play()
	{
		Init();

		while (!WindowShouldClose() && programLoop)
		{
			Input();
			Update();
			Draw();

			prevScene = currentScene;
		}

		DeInit();
	}

	void Init()
	{
		InitWindow(screenWidth, screenHeight, GameName.c_str());
		SetExitKey(KEY_NULL);

		InitEntities();
	}

	void InitEntities()
	{
		float randomY = static_cast<float>(GetRandomValue(20, GetScreenHeight() - static_cast<int>(obs.body.height / 2)));

		pl = player::Create(Rectangle{ static_cast<float>(screenWidth / 4),
								   static_cast<float>(screenHeight) / 2,
								   60,60 }, 300.f);

		obs = obstacule::Create(Rectangle{ static_cast<float>(screenWidth + 20),
										   randomY,
										   40,400 }, 500.f);
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
		}

		if (CheckBorderCollision(pl.body, screenWidth, 0, screenHeight, 0))
		{
			if (pl.body.y < 0)
				pl.body.y = 0;
			if (pl.body.y + pl.body.height > screenHeight)
				pl.body.y = screenHeight - pl.body.height;
		}
	}

	void Draw()
	{
		BeginDrawing();

		ClearBackground(WHITE);

		player::Draw(pl);
		obstacule::Draw(obs);

		EndDrawing();
	}

	void DeInit()
	{
		CloseWindow();
	}
}

