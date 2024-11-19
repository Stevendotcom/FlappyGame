#include "Credits.h"

#include "GameLoop.h"

#include "UI/Button.h"
#include "Utilities/SoundManager.h"

namespace game::scenes::credits
{
	const int maxButtons = 8;

	button::Button buttons[maxButtons];

	static bool wasOnTop[maxButtons] = { false };
	static bool isOnTop[maxButtons] = { false };

	Texture2D background;
	Texture2D midground;
	Texture2D foreground;

	enum Buttons
	{
		back,
		emaButton,
		nicoButton,
		pixelRpgMusic,
		uiEssential,
		beholden,
		cannonSound,
		uiSfx

	};



	void Init()
	{
		float x = button::ButtonWidth / 2;
		float y = button::ButtonHeight / 2;

		Rectangle graph = { x + 60, y + 10, button::ButtonWidth + 100, button::ButtonHeight -10};

		buttons[back] = button::Create(graph, "Back");

		graph.x = (static_cast<float>(GetScreenWidth()) / 2.0f);
		graph.y = (120);
		buttons[emaButton] = button::Create(graph, "Emanuel Parajon");

		graph.y = graph.y + 100;
		buttons[nicoButton] = button::Create(graph, "Nicolas Gallardo");

		graph.y = graph.y + 100;
		buttons[pixelRpgMusic] = button::Create(graph, "alkakrab");

		graph.y = graph.y + 100;
		buttons[uiEssential] = button::Create(graph, "Crusehno");

		graph.y = graph.y + 100;
		buttons[beholden] = button::Create(graph, "Amorphous");

		graph.y = graph.y + 100;
		buttons[cannonSound] = button::Create(graph, "Alex_Jauk");

		graph.y = graph.y + 100;
		buttons[uiSfx] = button::Create(graph, "JDSherbert");

		background = LoadTexture("res/BackGround.png");
		midground = LoadTexture("res/MidGround.png");
		foreground = LoadTexture("res/ForeGround.png");

	}



	void Input()
	{
		for (int i = 0; i < maxButtons; i++)
		{
			if (IsPressed(buttons[i]))
			{
				AddToBuffer(utils::soundManager::Sounds::Click);
				switch (i)
				{
				case back:
					currentScene = Scene::Menu;
					break;
				case emaButton:
					OpenURL("https://frostpower.itch.io/");
					break;
				case nicoButton:
					OpenURL("https://projectbifron.itch.io");
					break;
				case pixelRpgMusic:
					OpenURL("https://alkakrab.itch.io/free-12-tracks-pixel-rpg-game-music-pack");
					break;
				case uiEssential:
					OpenURL("https://crusenho.itch.io/complete-ui-essential-pack");
					break;
				case beholden:
					OpenURL("https://amorphous.itch.io/beholden");
					break;
				case cannonSound:
					OpenURL("https://pixabay.com/sound-effects/cannon-firing-193247/");
					break;
				case uiSfx:
					OpenURL("https://jdsherbert.itch.io/ultimate-ui-sfx-pack");
					break;

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


		button::Draw(buttons[back]);

		for (int i = 0; i < maxButtons; i++)
		{
			button::Draw(buttons[i]);
		}

		DrawText("Lead Programmer and artist", screenWidth - 450, static_cast<int>(GetCenterPosition(buttons[emaButton]).y) - 60, 30, BLACK);

		DrawText("Programmer and artist", screenWidth - 450, static_cast<int>(GetCenterPosition(buttons[nicoButton]).y) - 60, 30, WHITE);

		DrawText("Pixel RPG Music Pack", screenWidth - 450, static_cast<int>(GetCenterPosition(buttons[pixelRpgMusic]).y) - 60, 30, WHITE);

		DrawText("UI Essential Pack", screenWidth - 450, static_cast<int>(GetCenterPosition(buttons[uiEssential]).y) - 60, 30, WHITE);

		DrawText("Beholden Font", screenWidth - 450, static_cast<int>(GetCenterPosition(buttons[beholden]).y) - 60, 30, WHITE);

		DrawText("Cannon Sound", screenWidth - 450, static_cast<int>(GetCenterPosition(buttons[cannonSound]).y) - 60, 30, WHITE);

		DrawText("Ultimate UI SFX Pack", screenWidth - 450, static_cast<int>(GetCenterPosition(buttons[uiSfx]).y) - 60, 30, WHITE);
	}



	void DeInit()
	{
		UnloadTexture(background);
		UnloadTexture(midground);
		UnloadTexture(foreground);
	}
}