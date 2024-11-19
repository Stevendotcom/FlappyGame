#include "HowToPlay.h"

#include "GameLoop.h"
#include "UI/Button.h"
#include "Utilities/SoundManager.h"

namespace game::scenes::howToPlay
{
	button::Button back;

	bool wasOnTop = false;
	bool isOnTop = false ;
	
	void Init()
	{


		Rectangle graph = { button::ButtonWidth / 2 + 60, button::ButtonHeight / 2 + 10, button::ButtonWidth + 100, button::ButtonHeight - 10};

		back = button::Create(graph, "Back");
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
		button::Draw(back);
	}



	void DeInit()
	{}
}