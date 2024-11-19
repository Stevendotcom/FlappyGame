#include "GameLoop.h"

#include "raylib.h"

#include "Scenes/Credits.h"
#include "Scenes/GamePlay.h"
#include "Scenes/HowToPlay.h"
#include "Scenes/MainMenu.h"
#include "Utilities/SoundManager.h"

using namespace game::scenes;
using namespace game::utils;

namespace game
{
	static Scene prevScene = Scene::Menu;

	const std::string GameName = "FlappyBird";

	int screenWidth = 1024;
	int screenHeight = 768;

	Scene currentScene = Scene::Menu;

	bool programLoop = true;

	bool isMultiplayer = false;

	float timer = 0;

	float score = 0;

	Font defFont;

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
		SetConfigFlags(FLAG_VSYNC_HINT);
		SetExitKey(KEY_NULL);

		InitAudioDevice();

		mainmenu::Init();
		gameplay::Init();
		credits::Init();
		soundManager::Init();
		howToPlay::Init();

		defFont = LoadFontEx("res/Beholden-Regular.ttf", 64, nullptr, 0);
	}

	void Input()
	{
		switch (currentScene)
		{
		case Scene::Menu:
			mainmenu::Input();
			break;

		case Scene::GameplayMultiplayer:
		case Scene::Gameplay:
			gameplay::Input();
			break;

		case Scene::HowToPlay:
			howToPlay::Input();
			break;

		case Scene::Credits:
			credits::Input();
			break;
		}
	}

	void Update()
	{
		soundManager::Update();

		switch (currentScene)
		{
		case Scene::Menu:
			mainmenu::Update();
			break;

		case Scene::GameplayMultiplayer:
		case Scene::Gameplay:
			gameplay::Update();
			break;

		case Scene::HowToPlay:
			howToPlay::Update();
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

		case Scene::GameplayMultiplayer:
		case Scene::Gameplay:
			gameplay::Draw();
			break;

		case Scene::HowToPlay:
			howToPlay::Draw();
			break;

		case Scene::Credits:
			credits::Draw();
			break;
		}

		EndDrawing();
	}

	void DeInit()
	{
		mainmenu::DeInit();
		gameplay::DeInit();
		credits::DeInit();
		soundManager::DeInit();
		howToPlay::DeInit();
		CloseAudioDevice();
		CloseWindow();

		UnloadFont(defFont);
	}
} // namespace game
