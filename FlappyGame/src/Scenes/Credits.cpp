#include "Credits.h"

#include "GameLoop.h"

#include "UI/Button.h"
#include "Utilities/SoundManager.h"

namespace game::scenes::credits
{
	const int maxButtons = 3;

	button::Button buttons[maxButtons];

	static bool wasOnTop[maxButtons] = {false};
	static bool isOnTop[maxButtons] = {false};

	enum Buttons
	{
		back,
		emaButton,
		nicoButton,
	};



	void Init()
	{
		float x = button::ButtonWidth / 2;
		float y = button::ButtonHeight / 2;

		Rectangle graph = { x, y, button::ButtonWidth, button::ButtonHeight };

		buttons[back] = button::Create(graph, "Back");

		graph.x = (static_cast<float>(GetScreenWidth()) / 2.f);
		graph.y = (static_cast<float>(GetScreenHeight()) / 2.f);
		buttons[emaButton] = button::Create(graph, "Emanuel Parajon");

		graph.y = (static_cast<float>(GetScreenHeight()) / 2.f + 100);
		buttons[nicoButton] = button::Create(graph, "Nicolas Gallardo");
	}



	void Input()
	{
		for (int i = 0; i < maxButtons; i++)
		{
			if (button::IsPressed(buttons[i]))
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
				}
			}
		}
	}



	void Update()
	{
		for (int i = 0; i < maxButtons; i++)
		{
			isOnTop[i] = button::MouseOnTop(buttons[i]);
			if (isOnTop[i])
			{
				if (!wasOnTop[i])
					AddToBuffer(utils::soundManager::Sounds::Hover);
				wasOnTop[i] = true;
			}
			else
				wasOnTop[i] = false;
		}
	}



	void Draw()
	{
		button::Draw(buttons[back]);
		DrawText("Lead Programmer", static_cast<int>(GetCenterPosition(buttons[emaButton]).x) - MeasureText("Lead Programmer", 32),
		         static_cast<int>(GetCenterPosition(buttons[emaButton]).y) - 60, 32, BLACK);
		button::Draw(buttons[emaButton]);

		DrawText("Junior Programmer", static_cast<int>(GetCenterPosition(buttons[nicoButton]).x), static_cast<int>(GetCenterPosition(buttons[nicoButton]).y) - 60, 32, BLACK);
		button::Draw(buttons[nicoButton]);
	}



	void DeInit()
	{}
}