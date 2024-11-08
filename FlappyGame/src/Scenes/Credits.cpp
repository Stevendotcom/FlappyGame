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
			button::Button nicoButton;

			void Init()
			{
				float x = button::ButtonWidth / 2;
				float y = button::ButtonHeight / 2;

				Rectangle graph = { x,y,button::ButtonWidth,button::ButtonHeight };

				back = button::Create(graph,"Back");

				graph.x = (static_cast<float>(GetScreenWidth()) / 2.f);
				graph.y = (static_cast<float>(GetScreenHeight()) / 2.f);
				emaButton = button::Create(graph, "Emanuel Parajon");

				graph.y = (static_cast<float>(GetScreenHeight()) / 2.f + 100);
				nicoButton = button::Create(graph, "Nicolas Gallardo");
			}

			void Input()
			{
				if (button::IsPressed(back))
					currentScene = Scene::Menu;
				if (button::IsPressed(emaButton))
					OpenURL("https://frostpower.itch.io/");
				if (button::IsPressed(nicoButton))
					OpenURL("https://projectbifron.itch.io");
			}
			void Update()
			{
				button::MouseOnTop(back);
				button::MouseOnTop(emaButton);
				button::MouseOnTop(nicoButton);
			}
			void Draw()
			{
				button::Draw(back);
				DrawText("Lead Programmer", static_cast<int>(GetCenterPosition(emaButton).x) - MeasureText("Lead Programmer",32), static_cast<int>(GetCenterPosition(emaButton).y) - 60, 32, BLACK );
				button::Draw(emaButton);

				DrawText("Junior Programmer", static_cast<int>(GetCenterPosition(nicoButton).x), static_cast<int>(GetCenterPosition(nicoButton).y)
					         - 60, 32, BLACK );
				button::Draw(nicoButton);
			}

			void DeInit()
			{

			}
		}
	}
}