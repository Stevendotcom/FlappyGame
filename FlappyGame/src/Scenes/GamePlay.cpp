#include "GamePlay.h"

#include "GameLoop.h"

#include "Entities/obstacle.h"
#include "Entities/Player.h"
#include "Entities/Parallax.h"

#include "UI/Button.h"
#include "Utilities/SoundManager.h"

#include "Utilities/Utils.h"

namespace game::scenes::gameplay
{
	using namespace entities;
	using namespace player;
	using namespace obstacle;
	using namespace parallax;

	Player player;
	Player player2;
	Obstacle obstacle;

	Parallax background;
	Parallax midground;
	Parallax foreground;

	button::Button resume;
	button::Button menu;

	float timerStart = 3.0f;
	bool pause;

	static void InitEntities();

	static void RestartEntities();



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
			{
				AddToBuffer(utils::soundManager::Sounds::PauseUp);
				pause = !pause;
			}

			if (pause)
			{
				if (button::IsPressed(resume))
					pause = !pause;

				if (button::IsPressed(menu))
				{
					currentScene = Scene::Menu;
					pause = !pause;
					RestartEntities();
					ChangeMusic(utils::soundManager::Musics::MainMenu);
				}

				return;
			}
			if (!isMultiplayer)
				player::Input(player);
			else
			{
				player::Input(player, KEY_W);
				player::Input(player2, KEY_UP);
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

			player::Update(player);

			if (isMultiplayer)
				player::Update(player2);

			obstacle::Update(obstacle);

			if (obstacle.body1.x + obstacle.body1.width < 0)
			{
				Vector2 newPos;

				newPos.x = static_cast<float>(GetScreenWidth());
				newPos.y = static_cast<float>(GetRandomValue(0, GetScreenHeight() - static_cast<int>(obstacle.body1.height)));

				obstacle::SetPosition(obstacle, newPos);
			}

			if (isMultiplayer)
			{
				if (CheckCollision(player.body, obstacle.body1) || CheckCollision(player.body, obstacle.body2) || CheckCollision(player2.body, obstacle.body1) || CheckCollision(
					    player2.body, obstacle.body2))
				{
					RestartEntities();
					currentScene = Scene::Menu;
				}

				if (CheckBorderCollision(player.body, GetScreenWidth(), 0, GetScreenHeight(), 0) || CheckBorderCollision(player2.body, GetScreenWidth(), 0, GetScreenHeight(), 0))
				{
					if (player.body.y < 0)
						player.body.y = 0;

					if (player.body.y + player.body.height > static_cast<float>(GetScreenHeight()))
					{
						RestartEntities();
						currentScene = Scene::Menu;
					}

					if (player2.body.y < 0)
						player2.body.y = 0;

					if (player2.body.y + player2.body.height > static_cast<float>(GetScreenHeight()))
					{
						RestartEntities();
						currentScene = Scene::Menu;
					}
				}
			} else
			{
				if (CheckCollision(player.body, obstacle.body1) || CheckCollision(player.body, obstacle.body2))
				{
					RestartEntities();
					timer = 3.0f;
					currentScene = Scene::Menu;
				}
				if (CheckBorderCollision(player.body, GetScreenWidth(), 0, GetScreenHeight(), 0))
				{
					if (player.body.y < 0)
						player.body.y = 0;
					if (player.body.y + player.body.height > static_cast<float>(GetScreenHeight()))
					{
						RestartEntities();
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

		player::Draw(player);

		if (isMultiplayer)
			player::Draw(player2);

		obstacle::Draw(obstacle);

		parallax::Draw(foreground);

		DrawRect(Rectangle{ 0, static_cast<float>(screenHeight) / 5.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight) }, Color{ 37, 107, 122, 150 });

		if (pause)
		{
			DrawRect(Rectangle{ 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) }, Color{ 50, 50, 50, 200 });

			button::Draw(resume);
			button::Draw(menu);
		}

		if (timer < timerStart && isMultiplayer)
		{
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenWidth(), { 0, 0, 0, 100 });
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

		player::DeInit(player);
		if (isMultiplayer)
			player::DeInit(player2);
	}



	void InitEntities()
	{
		float randomY = static_cast<float>(GetRandomValue(200, GetScreenHeight() - static_cast<int>(obstacle.body1.height / 2)));

		float x = static_cast<float>(GetScreenWidth()) / 4.0f;
		float y = static_cast<float>(GetScreenHeight()) / 2.0f;

		parallax::Init(background, "res/BackGround.png", 25.0f);
		parallax::Init(midground, "res/MidGround.png", 100.0f);
		parallax::Init(foreground, "res/ForeGround.png", 250.0f);

		player = player::Create(Rectangle{ x, y, 60, 60 }, 300.f);
		player2 = player::Create(Rectangle{ x, y, 60, 60 }, 300.f, true, true);

		x = static_cast<float>(GetScreenWidth() + 20);
		obstacle = obstacle::Create(x, randomY, 40, 1000, 500.f);
	}



	void RestartEntities()
	{
		float randomY = static_cast<float>(GetRandomValue(0, GetScreenHeight() - static_cast<int>(obstacle.body1.height)));

		float x = static_cast<float>(GetScreenWidth()) / 4.0f;
		float y = static_cast<float>(GetScreenHeight()) / 2.0f;

		Restart(player, x, y);
		Restart(player2, x, y);

		x = static_cast<float>(GetScreenWidth() + 20);
		SetPosition(obstacle, { x, randomY });
	}
}