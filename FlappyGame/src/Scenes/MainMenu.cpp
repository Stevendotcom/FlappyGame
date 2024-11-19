#include "MainMenu.h"

#include "GameLoop.h"

#include "UI/Button.h"
#include "Utilities/SoundManager.h"

namespace game::scenes::mainmenu
{
	const std::string GameVersion = "Version 1.0";
	const int maxButtons = 5;

	button::Button buttons[maxButtons];

	bool wasOnTop[maxButtons] = { false };
	bool isOnTop[maxButtons] = { false };

	Texture2D header;
	Texture2D background;
	Texture2D midground;
	Texture2D foreground;



	void Init()
	{
		header = LoadTexture("res/Header.png");
		background = LoadTexture("res/BackGround.png");
		midground = LoadTexture("res/MidGround.png");
		foreground = LoadTexture("res/ForeGround.png");

		float x = (static_cast<float>(GetScreenWidth()) / 2.f);
		float y = 250;

		Rectangle graph = { x, y, button::ButtonWidth, button::ButtonHeight };

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i] = button::Create(graph);

			graph.y += button::ButtonHeight * 1.5f;
		}

		SetText(buttons[0], "1 Player");
		SetText(buttons[1], "2 Players");
		SetText(buttons[2], "Rules");
		SetText(buttons[3], "Credits");
		SetText(buttons[4], "Exit");
	}



	void Input()
	{
		for (int i = 0; i < maxButtons; i++)
		{
			if (IsPressed(buttons[i]))
			{
				AddToBuffer(utils::soundManager::Sounds::Click);
				currentScene = static_cast<Scene>(i + 1);
				if (static_cast<Scene>(i + 1) == Scene::GameplayMultiplayer)
				{
					ChangeMusic(utils::soundManager::Musics::Game);
					isMultiplayer = true;
				} else if (static_cast<Scene>(i + 1) == Scene::Gameplay)
				{
					ChangeMusic(utils::soundManager::Musics::Game);
					isMultiplayer = false;
				}
			}
		}
	}



	void Update()
	{
		for (int i = 0; i < maxButtons; i++)
		{
			isOnTop[i] = MouseOnTop(buttons[i]);
			if (isOnTop[i])
			{
				if (!wasOnTop[i])
					AddToBuffer(utils::soundManager::Sounds::Hover);
				wasOnTop[i] = true;
			} else
				wasOnTop[i] = false;
		}
	}



	void Draw()
	{

		DrawTexturePro(background, { 0, 0, static_cast<float>(background.width), static_cast<float>(background.height) },
		               { 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0, 0 }, 0, WHITE);
		DrawTexturePro(midground, { 0, 0, static_cast<float>(midground.width), static_cast<float>(midground.height) },
		               { 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0, 0 }, 0, WHITE);
		DrawTexturePro(foreground, { 0, 0, static_cast<float>(foreground.width), static_cast<float>(foreground.height) },
		               { 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0, 0 }, 0, WHITE);

		for (int i = 0; i < maxButtons; i++)
		{
			button::Draw(buttons[i]);
		}

		DrawTexturePro(header, { 0, 0, static_cast<float>(header.width), static_cast<float>(header.height) },
			       { (static_cast<float>(GetScreenWidth()) - static_cast<float>(header.width)) / 2, 0, static_cast<float>(header.width), static_cast<float>(header.height) }, { 0, 0 },
			       0, WHITE);
		DrawText(GameVersion.c_str(), 1, screenHeight - 10, 10, BLACK);
	}



	void DeInit()
	{
		UnloadTexture(header);
		UnloadTexture(background);
		UnloadTexture(midground);
		UnloadTexture(foreground);

		for (int i = 0; i < maxButtons; i++)
		{
			DeInit(buttons[i]);
		}
	}
}