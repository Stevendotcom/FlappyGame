#include "GamePlay.h"

#include "GameLoop.h"

#include "Entities/obstacle.h"
#include "Entities/Player.h"

#include "UI/Button.h"

#include "Utilities/Utils.h"

namespace game::scenes::gameplay
{
	entities::Player pl;
	entities::Player pl2;
	entities::Obstacle obs;

	button::Button resume;
	button::Button menu;

	Texture2D backGround;
	Texture2D midGround;
	Texture2D foreGround;

	float offsetBack;
	float offsetMid;
	float offsetFore;

	float velBack;
	float velMid;
	float velFore;

	constexpr float timerStart = 3.0f;
	float timer;

	bool pause;

	void InitEntities();

	void ParallaxUpdate();



	void Init()
	{
		backGround = LoadTexture("res/BackGround.png");
		midGround = LoadTexture("res/MidGround.png");
		foreGround = LoadTexture("res/ForeGround.png");

		backGround.width = GetScreenWidth();
		backGround.height = GetScreenHeight();

		midGround.width = GetScreenWidth();
		midGround.height = GetScreenHeight();

		foreGround.width = GetScreenWidth();
		foreGround.height = GetScreenHeight();

		offsetBack = 0.0;
		offsetMid = 0.0;
		offsetFore = 0.0;

		velBack = 25.f;
		velMid = 100.f;
		velFore = 250.f;

		pause = false;

		Rectangle posButton;

		posButton.x = static_cast<float>(screenWidth) / 2.0f;
		posButton.y = static_cast<float>(screenHeight) / 2.0f - button::ButtonHeight * 1.2f;
		posButton.width = button::ButtonWidth;
		posButton.height = button::ButtonHeight;

		resume = button::Create(posButton, "Resume");

		posButton.y = static_cast<float>(screenHeight) / 2.0f + button::ButtonHeight * 2.4f;

		menu = button::Create(posButton, "Menu");

		InitEntities();
	}



	void Input()
	{
		if (timer > timerStart || !isMultiplayer)
		{
			if (IsKeyPressed(KEY_ESCAPE))
				pause = !pause;

			if (pause) {
				if (button::IsPressed(resume))
					pause = !pause;

				if (button::IsPressed(menu)) {
					currentScene = Scene::Menu;
					pause = !pause;
					InitEntities();
				}

				return;
			}
			if(!isMultiplayer)
				player::Input(pl);
			else
			{
				player::Input(pl, KEY_W);
				player::Input(pl2, KEY_UP);
			}
		}
	}



	void Update()
	{
		timer += GetFrameTime();
		if (timer > timerStart || !isMultiplayer)
		{
			if (pause)
			{
				button::MouseOnTop(resume);
				button::MouseOnTop(menu);

				return;
			}

			ParallaxUpdate();

			player::Update(pl);

			if (isMultiplayer)
				player::Update(pl2);

			obstacle::Update(obs);

			if (obs.body1.x + obs.body1.width < 0)
			{
				Vector2 newPos;

				newPos.x = static_cast<float>(GetScreenWidth());
				newPos.y = static_cast<float>(
					GetRandomValue(0, GetScreenHeight() - static_cast<int>(obs.body1.height)));

				obstacle::SetPosition(obs, newPos);
			}

			if(isMultiplayer)
				if (CheckCollision(pl.body, obs.body1) || CheckCollision(pl.body, obs.body2) || CheckCollision(
					    pl2.body, obs.body1) || CheckCollision(pl2.body, obs.body2))
				{
					InitEntities();
					currentScene = Scene::Menu;
				}

				if (CheckBorderCollision(pl.body, GetScreenWidth(), 0, GetScreenHeight(), 0) || CheckBorderCollision(
					pl2.body, GetScreenWidth(), 0, GetScreenHeight(), 0))
				{
					if (pl.body.y < 0)
						pl.body.y = 0;

					if (pl.body.y + pl.body.height > static_cast<float>(GetScreenHeight()))
					{
						InitEntities();
						currentScene = Scene::Menu;
					}

					if (pl2.body.y < 0)
						pl2.body.y = 0;

					if (pl2.body.y + pl2.body.height > static_cast<float>(GetScreenHeight()))
					{
						InitEntities();
						currentScene = Scene::Menu;
					}
				}
			else
			{
				if (CheckCollision(pl.body, obs.body1) || CheckCollision(pl.body, obs.body2))
				{
					InitEntities();
					timer = 3.0f;
					currentScene = Scene::Menu;
				}
				if (CheckBorderCollision(pl.body, GetScreenWidth(), 0, GetScreenHeight(), 0))
				{
					if (pl.body.y < 0)
						pl.body.y = 0;
					if (pl.body.y + pl.body.height > static_cast<float>(GetScreenHeight()))
					{
						InitEntities();
						currentScene = Scene::Menu;
					}
				}
			}


		}
	}



	void Draw()
	{
		Color transparent = { 255, 255, 255, 200 };

		DrawTextureEx(backGround, { offsetBack, 0 }, 0, 1, WHITE);
		DrawTextureEx(backGround, { static_cast<float>(backGround.width) + offsetBack, 0 }, 0, 1, WHITE);

		DrawTextureEx(midGround, { offsetMid, 0 }, 0, 1, transparent);
		DrawTextureEx(midGround, { static_cast<float>(midGround.width) + offsetMid, 0 }, 0, 1, transparent);

		player::Draw(pl);

		if(isMultiplayer)
			player::Draw(pl2);

		obstacle::Draw(obs);

		DrawTextureEx(foreGround, { offsetFore, 0 }, 0, 1, WHITE);
		DrawTextureEx(foreGround, { static_cast<float>(foreGround.width) + offsetFore, 0 }, 0, 1, WHITE);

		DrawRect(Rectangle{ 0,
		                    static_cast<float>(screenHeight) / 5.0f,
		                    static_cast<float>(screenWidth),
		                    static_cast<float>(screenHeight) }, Color{ 37, 107, 122, 150 });

		if (pause)
		{
			DrawRect(Rectangle{ 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
			         Color{ 50, 50, 50, 200 });

			button::Draw(resume);
			button::Draw(menu);
		}

		if (timer < timerStart && isMultiplayer)
		{
			DrawRectangle(0,0, GetScreenWidth(), GetScreenWidth(), {0, 0, 0, 100} );
			DrawText("Player 1 jumps with W", 20, 100, 48, WHITE);
			DrawText("Player 2 jumps with Up key", 20, 160, 48, WHITE);
			DrawText(TextFormat("%0.1f", (timerStart - timer)), GetScreenWidth() / 2, 215, 48, WHITE);
		}
	}



	void DeInit()
	{
		UnloadTexture(backGround);
		UnloadTexture(midGround);
		UnloadTexture(foreGround);

		player::DeInit(pl);
		if(isMultiplayer)
			player::DeInit(pl2);
	}



	void InitEntities()
	{
		float randomY = static_cast<float>(GetRandomValue(200, GetScreenHeight() - static_cast<int>(obs.body1.height / 2)));

		float x = static_cast<float>(GetScreenWidth()) / 4.0f;
		float y = static_cast<float>(GetScreenHeight()) / 2.0f;

		pl = player::Create(Rectangle{ x, y, 60, 60 }, 300.f);
		if(isMultiplayer)
			pl2 = player::Create(Rectangle{ x, y, 60, 60 }, 300.f);

		x = static_cast<float>(GetScreenWidth() + 20);
		obs = obstacle::Create(x, randomY, 40, 1000, 500.f);
	}



	void ParallaxUpdate()
	{
		offsetBack -= (offsetBack <= static_cast<float>(-backGround.width)) ? offsetBack : velBack * GetFrameTime();
		offsetMid -= (offsetMid <= static_cast<float>(-midGround.width)) ? offsetMid : velMid * GetFrameTime();
		offsetFore -= (offsetFore <= static_cast<float>(-foreGround.width)) ? offsetFore : velFore * GetFrameTime();
	}
}