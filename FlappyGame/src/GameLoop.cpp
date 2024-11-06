#include "GameLoop.h"

#include "raylib.h"

#include "Scenes/MainMenu.h"
#include "Scenes/GamePlay.h"
#include "Scenes/Credits.h"

using namespace game::scenes;

namespace game
{
	const std::string GameName = "FlappyBird";

	int screenWidth = 1024;
	int screenHeight = 768;

	SCENE currentScene = SCENE::MENU;

	SCENE prevScene = SCENE::MENU;

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

		mainmenu::Init();
		gameplay::Init();
		credits::Init();
	}

	void Input()
	{
		switch (currentScene)
		{
		case game::SCENE::MENU:
			mainmenu::Input();
			break;

		case game::SCENE::GAMEPLAY:
			gameplay::Input();
			break;

		case game::SCENE::CREDITS:
			credits::Input();
			break;
		}
	}

	void Update()
	{
		switch (currentScene)
		{
		case game::SCENE::MENU:
			mainmenu::Update();
			break;

		case game::SCENE::GAMEPLAY:
			gameplay::Update();
			break;

		case game::SCENE::CREDITS:
			credits::Update();
			break;

		case game::SCENE::EXIT:
			programLoop = false;
			break;
		}
	}

	void Draw()
	{
		BeginDrawing();

		ClearBackground(WHITE);

		switch (currentScene)
		{
		case game::SCENE::MENU:
			mainmenu::Draw();
			break;

		case game::SCENE::GAMEPLAY:
			gameplay::Draw();
			break;

		case game::SCENE::CREDITS:
			credits::Draw();
			break;
		}

		DrawText("Version 0.1", 1, screenHeight - 10, 10, BLACK);

		EndDrawing();
	}

	void DeInit()
	{
		mainmenu::DeInit();
		gameplay::DeInit();
		credits::DeInit();

		CloseWindow();
	}
}

