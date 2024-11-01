#include "GameLoop.h"

#include "raylib.h"

#include "Entities/Obstacule.h"
#include "Entities/Player.h"

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

		pl = player::Create(Rectangle{ static_cast<float>(screenWidth / 4),
										   static_cast<float>(screenHeight) / 2,
										   60,60});

		obs = obstacule::Create(Rectangle{ static_cast<float>(screenWidth + 20),
										   static_cast<float>(screenHeight) / 2,
										   40,120 });
	}

	void Input()
	{
		player::Input(pl);
	}

	void Update()
	{
		player::Update(pl);
		obstacule::Update(obs);
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

