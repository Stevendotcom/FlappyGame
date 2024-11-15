#include "GamePlay.h"

#include "GameLoop.h"

#include "Entities/obstacle.h"
#include "Entities/Player.h"
#include "Entities/Parallax.h"

#include "UI/Button.h"

#include "Utilities/Utils.h"

namespace game::scenes::gameplay
{
	using namespace entities;
	using namespace player;
	using namespace obstacle;
	using namespace parallax;

	Player pl;
	Player pl2;
	Obstacle obs;

	Parallax background;
	Parallax midground;
	Parallax foreground;

	button::Button resume;
	button::Button menu;



	float timerStart = 3.0f;
	bool pause;

	void InitEntities();



	void Init()
	{
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

			parallax::Update(background);
			parallax::Update(midground);
			parallax::Update(foreground);

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
			{
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

		parallax::Draw(background);

		parallax::Draw(midground);

		player::Draw(pl);

		if(isMultiplayer)
			player::Draw(pl2);

		obstacle::Draw(obs);

		parallax::Draw(foreground);

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
		parallax::Deinit(background);
		parallax::Deinit(midground);
		parallax::Deinit(foreground);

		player::DeInit(pl);
		if(isMultiplayer)
			player::DeInit(pl2);
	}



	void InitEntities()
	{
		float randomY = static_cast<float>(GetRandomValue(200, GetScreenHeight() - static_cast<int>(obs.body1.height / 2)));

		float x = static_cast<float>(GetScreenWidth()) / 4.0f;
		float y = static_cast<float>(GetScreenHeight()) / 2.0f;

		parallax::Init(background, "res/BackGround.png", 25.0f);
		parallax::Init(midground, "res/MidGround.png", 100.0f);
		parallax::Init(foreground, "res/ForeGround.png", 250.0f);

		pl = player::Create(Rectangle{ x, y, 60, 60 }, 300.f);
		pl2 = player::Create(Rectangle{ x, y, 60, 60 }, 300.f);

		x = static_cast<float>(GetScreenWidth() + 20);
		obs = obstacle::Create(x, randomY, 40, 1000, 500.f);
	}
}