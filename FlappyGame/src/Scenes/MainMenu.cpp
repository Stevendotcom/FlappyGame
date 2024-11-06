#include "MainMenu.h"

#include "GameLoop.h"

#include "UI/Button.h"

namespace game
{
	namespace scenes
	{
		namespace mainmenu
		{
			const int maxButtons = 3;

			button::Button buttons[maxButtons];

			void Init()
			{
				float x = (GetScreenWidth() / 2.f);
				float y = 50;

				Rectangle graph = { x,y,button::ButtonWidth,button::ButtonHeight };

				for (int i = 0; i < maxButtons; i++)
				{
					buttons[i] = button::Create(graph);

					graph.y += button::ButtonHeight * 1.5f;
				}

				button::SetText(buttons[0], "Play");
				button::SetText(buttons[1], "Credits");
				button::SetText(buttons[2], "Exit");
			}

			void Input()
			{
				for (int i = 0; i < maxButtons; i++)
				{
					if (button::IsPressed(buttons[i]))
						currentScene = static_cast<SCENE>(i + 1);
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
			}

			void DeInit()
			{

			}
		}
	}
}