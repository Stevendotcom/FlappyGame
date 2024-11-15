#include "MainMenu.h"

#include "GameLoop.h"

#include "UI/Button.h"

namespace game
{
	namespace scenes
	{
		namespace mainmenu
		{
			const std::string GameVersion = "Version 0.4";
			constexpr int maxButtons = 4;

			button::Button buttons[maxButtons];

			void Init()
			{
				float x = (static_cast<float>(GetScreenWidth()) / 2.f);
				float y = 50;

				Rectangle graph = { x,y,button::ButtonWidth,button::ButtonHeight };

				for (int i = 0; i < maxButtons; i++)
				{
					buttons[i] = button::Create(graph);

					graph.y += button::ButtonHeight * 1.5f;
				}

				button::SetText(buttons[0], "1 Player");
				button::SetText(buttons[1], "2 Players");
				button::SetText(buttons[2], "Credits");
				button::SetText(buttons[3], "Exit");
			}

			void Input()
			{
				for (int i = 0; i < maxButtons; i++)
				{
					if (button::IsPressed(buttons[i]))
					{
						currentScene = static_cast<Scene>(i + 1);
						if(static_cast<Scene>(i + 1) == Scene::GameplayMultiplayer)
						{
							isMultiplayer = true;
						}
						else
						{
							isMultiplayer = false;
						}
					}
				}
			}
			void Update()
			{
				for (int i = 0; i < maxButtons; i++)
				{
					button::MouseOnTop(buttons[i]);
				}
			}
			void Draw()
			{
				for (int i = 0; i < maxButtons; i++)
				{
					button::Draw(buttons[i]);
				}

				DrawText(GameVersion.c_str(), 1, screenHeight - 10, 10, BLACK);
			}

			void DeInit()
			{

			}
		}
	}
}