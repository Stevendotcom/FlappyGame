#include "Credits.h"

#include "GameLoop.h"

#include "UI/Button.h"

namespace game
{
	namespace scenes
	{
		namespace credits
		{
			button::Button back;
			button::Button emaButton;

			void Init()
			{
				float x = button::ButtonWidth / 2;
				float y = button::ButtonHeight / 2;

				Rectangle graph = { x,y,button::ButtonWidth,button::ButtonHeight };

				back = button::Create(graph,"Back");

				graph.x = (static_cast<float>(GetScreenWidth()) / 2.f);
				graph.y = (static_cast<float>(GetScreenHeight()) / 2.f);
				emaButton = button::Create(graph, "Emanuel Parajon");
			}

			void Input()
			{
				if (button::IsPressed(back))
					currentScene = Scene::Menu;
				if (button::IsPressed(emaButton))
					OpenURL("https://frostpower.itch.io/");
			}
			void Update()
			{
				button::MouseOnTop(back);
				button::MouseOnTop(emaButton);
			}
			void Draw()
			{
				button::Draw(back);
				button::Draw(emaButton);
			}

			void DeInit()
			{

			}
		}
	}
}