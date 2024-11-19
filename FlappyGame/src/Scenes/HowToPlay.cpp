#include "HowToPlay.h"

#include "GameLoop.h"
#include "UI/Button.h"
#include "Utilities/SoundManager.h"

namespace game::scenes::howToPlay
{
	button::Button back;

	bool wasOnTop = false;
	bool isOnTop = false ;
	
	Texture2D background;
	Texture2D midground;
	Texture2D foreground;
	Texture2D rules;

	void Init()
	{


		back = button::Create({ button::ButtonWidth / 2 + 60, button::ButtonHeight / 2 + 10, button::ButtonWidth + 100, button::ButtonHeight - 10 }, "Back");

		background = LoadTexture("res/BackGround.png");
		midground = LoadTexture("res/MidGround.png");
		foreground = LoadTexture("res/ForeGround.png");
		rules = LoadTexture("res/HowToPlay.png");
	}



	void Input()
	{
		if (IsPressed(back))
		{
			AddToBuffer(utils::soundManager::Sounds::Click);
			currentScene = Scene::Menu;
		}
	}



	void Update()
	{
		isOnTop = MouseOnTop(back);
		if (isOnTop)
		{
			if (!wasOnTop)
				AddToBuffer(utils::soundManager::Sounds::Hover);
			wasOnTop = true;
		} else
			wasOnTop = false;
	}



	void Draw()
	{

		DrawTexturePro(background, { 0, 0, static_cast<float>(background.width), static_cast<float>(background.height) },
			       { 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0, 0 }, 0, WHITE);
		DrawTexturePro(midground, { 0, 0, static_cast<float>(midground.width), static_cast<float>(midground.height) },
			       { 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0, 0 }, 0, WHITE);
		DrawTexturePro(foreground, { 0, 0, static_cast<float>(foreground.width), static_cast<float>(foreground.height) },
			       { 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0, 0 }, 0, WHITE);

		DrawRectangle(0, 0, screenWidth, screenHeight, { 50, 50, 50, 200 });
		
		DrawTexturePro(rules, { 0, 0, static_cast<float>(rules.width), static_cast<float>(rules.height) },
			       { 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0, 0 }, 0, WHITE);

		button::Draw(back);


	}



	void DeInit()
	{
		button::DeInit(back);
		UnloadTexture(background);
		UnloadTexture(midground);
		UnloadTexture(foreground);
		UnloadTexture(rules);
	}
}