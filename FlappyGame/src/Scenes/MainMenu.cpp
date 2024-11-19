#include "MainMenu.h"

#include "GameLoop.h"

#include "UI/Button.h"
#include "Utilities/SoundManager.h"

namespace game::scenes::mainmenu
{
	static const std::string GameVersion = "Version 1.0";
	static const int maxButtons = 5;

	static button::Button buttons[maxButtons];

	static button::Button mute;

	static bool wasOnTop[maxButtons] = { false };
	static bool isOnTop[maxButtons] = { false };

	static bool muted = false;

	static Texture2D header;
	static Texture2D background;
	static Texture2D midground;
	static Texture2D foreground;

	static Texture2D muteOn;
	static Texture2D muteOff;



	void Init()
	{
		header = LoadTexture("res/Header.png");
		background = LoadTexture("res/BackGround.png");
		midground = LoadTexture("res/MidGround.png");
		foreground = LoadTexture("res/ForeGround.png");
		muteOn = LoadTexture("res/UI_Flat_ToggleOn01a.png");
		muteOff = LoadTexture("res/UI_Flat_ToggleOff01a.png");

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
		SetText(buttons[2], "How To Play");
		SetText(buttons[3], "Credits");
		SetText(buttons[4], "Exit");

		mute = button::Create({ 60, static_cast<float>(screenHeight) - 80, 30, 30 });
		SetText(mute, "");
		mute.texture = muteOff;
		
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
			if (IsPressed(mute))
			{
				if (!muted)
					SetMasterVolume(0);
				
				else
					SetMasterVolume(1);
				muted = !muted;
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
		MouseOnTop(mute);
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

		if (muted)
			mute.texture = muteOn;
		else
			mute.texture = muteOff;

		button::Draw(mute);	
		DrawText("Mute Sounds", static_cast<int>(mute.graph.x) + 40, static_cast<int>(mute.graph.y) + 3, 20, WHITE);
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