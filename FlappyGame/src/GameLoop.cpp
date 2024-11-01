#include "GameLoop.h"

#include "raylib.h"

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
	}

	void Input()
	{

	}

	void Update()
	{
		
	}

	void Draw()
	{
		BeginDrawing();

		ClearBackground(WHITE);



		EndDrawing();
	}

	void DeInit()
	{
		CloseWindow();
	}
}

