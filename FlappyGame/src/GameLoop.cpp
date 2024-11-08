#include "GameLoop.h"

#include "raylib.h"

#include "Scenes/MainMenu.h"
#include "Scenes/GamePlay.h"
#include "Scenes/Credits.h"

using namespace game::scenes;

namespace game
{
	const std::string GameName = "FlappyBird";
	const std::string GameVersion = "Version 0.3";

	int screenWidth = 1024;
	int screenHeight = 768;

	Scene currentScene = Scene::Menu;

	auto prevScene = Scene::Menu;

	bool programLoop = true;

	static void Init();

	static void Input();
	static void Update();
	static void Draw();

	static void DeInit();

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
		case Scene::Menu:
			mainmenu::Input();
			break;

		case Scene::Gameplay:
			gameplay::Input();
			break;

		case Scene::Credits:
			credits::Input();
			break;
		}
	}

	void Update()
	{
		switch (currentScene)
		{
		case Scene::Menu:
			mainmenu::Update();
			break;

		case Scene::Gameplay:
			gameplay::Update();
			break;

		case Scene::Credits:
			credits::Update();
			break;

		case Scene::Exit:
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
		case Scene::Menu:
			mainmenu::Draw();
			break;

		case Scene::Gameplay:
			gameplay::Draw();
			break;

		case Scene::Credits:
			credits::Draw();
			break;
		}

		DrawText(GameVersion.c_str(), 1, screenHeight - 10, 10, BLACK);

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

