#include "GamePlay.h"

#include "GameLoop.h"

#include "Entities/Obstacle.h"
#include "Entities/Parallax.h"
#include "Entities/Pause.h"
#include "Entities/Player.h"

#include "UI/Button.h"
#include "Utilities/SoundManager.h"

#include "Utilities/Utils.h"

namespace game::scenes::gameplay
{
	using namespace entities;
	using namespace player;
	using namespace obstacle;
	using namespace parallax;
	using namespace utils::soundManager;

	static Player player;
	static Player player2;
	static Obstacle obstacle;

	static Parallax background;
	static Parallax midground;
	static Parallax foreground;

	static button::Button resume;
	static button::Button menu;

	static float timerStart = 3.0f;
	static float fontSizeLost = 52;
	static float fontSizeScore = 64;

	static bool pause;
	static bool lost;

	static std::string message = "You lost!";
	static std::string messagePause = "Pause";
	static std::string messageScore = "Score";

	static Vector2 size;
	static Vector2 sizePause;
	static Vector2 sizeScore;

	static void InitEntities();

	static void Reset();



	void Init()
	{
		pause = false;

		Rectangle posButton;

		posButton.x = static_cast<float>(screenWidth) / 2.0f;
		posButton.y = static_cast<float>(screenHeight) / 2.0f - button::ButtonHeight * 1.2f;
		posButton.width = button::ButtonWidth;
		posButton.height = button::ButtonHeight;

		resume = button::Create(posButton, "Resume");

		posButton.y = static_cast<float>(screenHeight) / 2.0f + button::ButtonHeight;

		menu = button::Create(posButton, "Menu");

		InitEntities();
	}



	void Input()
	{
		if (timer > timerStart || !isMultiplayer)
		{
			if (IsKeyPressed(KEY_ESCAPE) && !lost)
			{
				AddToBuffer(Sounds::PauseUp);
				pause = !pause;
			}

			if (pause)
			{
				if (IsPressed(resume) && !lost)
				{
					pause = !pause;
					AddToBuffer(Sounds::Click);
				}

				if (IsPressed(menu))
				{
					AddToBuffer(Sounds::Click);
					currentScene = Scene::Menu;
					Reset();
					ChangeMusic(Musics::MainMenu);
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
				pause::Update(resume, menu, lost);
				return;
			}

			score += 100 * GetFrameTime();

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

				SetPosition(obstacle, newPos);
			}

			if (CheckCollision(player.body, obstacle.body1) || CheckCollision(player.body, obstacle.body2))
			{
				message = "Player 1 lost, nearly there buddy";
				pause = true;
				lost = true;
				messageScore.append(" " + std::to_string(static_cast<int>(score)));
				AddToBuffer(Sounds::Crash);
			}
			if (CheckBorderCollision(player.body, GetScreenWidth(), 0, GetScreenHeight(), 0))
			{
				if (player.body.y < 0)
					player.body.y = 0;
				if (player.body.y + player.body.height > static_cast<float>(GetScreenHeight()))
				{
					message = "Player 1 lost. Remember you *have* to jump";
					pause = true;
					lost = true;
					messageScore.append(" " + std::to_string(static_cast<int>(score)));
					AddToBuffer(Sounds::Crash);

				}
			}

			if (isMultiplayer && !lost)
			{
				player.body.x = player2.body.x + 60;
				if (CheckCollision(player2.body, obstacle.body1) || CheckCollision(player2.body, obstacle.body2))
				{
					fontSizeLost = 40;
					message = "Player 2 lost. Is your part of the keyboard connected?";
					pause = true;
					lost = true;
					messageScore.append(" " + std::to_string(static_cast<int>(score)));
					AddToBuffer(Sounds::Crash);

				}

				if (CheckBorderCollision(player2.body, GetScreenWidth(), 0, GetScreenHeight(), 0))
				{
					if (player2.body.y < 0)
						player2.body.y = 0;

					if (player2.body.y + player2.body.height > static_cast<float>(GetScreenHeight()))
					{
						message = "Player 2 lost. This has to be further, right?";
						pause = true;
						lost = true;
						messageScore.append(" " + std::to_string(static_cast<int>(score)));
						AddToBuffer(Sounds::Crash);


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
		{
			DrawText("Player 1", static_cast<int>(player.body.x) + 20, static_cast<int>(player.body.y) - 8, 16, { 32, 218, 254, 255 });
			player::Draw(player2);
			DrawText("Player 2", static_cast<int>(player2.body.x) + 20, static_cast<int>(player2.body.y) - 8, 16, { 40, 223, 170, 255 });
		}

		obstacle::Draw(obstacle);

		parallax::Draw(foreground);

		DrawRect(Rectangle{ 0, static_cast<float>(screenHeight) / 5.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight) }, Color{ 37, 107, 122, 150 });

		if (pause)
		{
			pause::Draw(resume, menu, message, messageScore, messagePause, fontSizeLost, fontSizeScore, lost);
		}

		if (timer < timerStart && isMultiplayer)
		{
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenWidth(), { 50, 50, 50, 200 });

			DrawTexturePro(player.texture, player.source, { 80, static_cast<float>(screenHeight) / 2.0f - 30.0f, player.body.width, player.body.width }, player.origin, 0, WHITE);
			DrawText("Player 1 jumps with W", 100, screenHeight / 2- 75, 48, WHITE);

			DrawTexturePro(player2.texture, player2.source, { 80, static_cast<float>(screenHeight) / 2.0f + 120.0f, player2.body.width, player2.body.width }, player2.origin, 0, WHITE);
			DrawText("Player 2 jumps with Up key", 100, screenHeight / 2 + 75, 48, WHITE);
			
			DrawText(TextFormat("%0.1f", (timerStart - timer)), GetScreenWidth() / 2, 215, 48, WHITE);
		}
	}



	void DeInit()
	{
		Deinit(background);
		Deinit(midground);
		Deinit(foreground);

		player::DeInit(player);
		player::DeInit(player2);

		button::DeInit(resume);
		button::DeInit(menu);

		obstacle::DeInit(obstacle);
	}



	void InitEntities()
	{
		float randomY = static_cast<float>(GetRandomValue(200, GetScreenHeight()));

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



	void Reset()
	{
		pause = !pause;
		lost = false;
		messageScore = "";
		timer = 0;
		score = 0;

		float randomY = static_cast<float>(GetRandomValue(0, GetScreenHeight() - static_cast<int>(obstacle.body1.height)));

		float x = static_cast<float>(GetScreenWidth()) / 4.0f;
		float y = static_cast<float>(GetScreenHeight()) / 2.0f;

		Restart(player, x, y);
		Restart(player2, x, y);

		x = static_cast<float>(GetScreenWidth() + 20);
		SetPosition(obstacle, { x, randomY });
	}
}