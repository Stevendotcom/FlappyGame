#pragma once

#include <iostream>

namespace game
{
	enum class Scene
	{
		Menu,
		Gameplay,
		//OPTIONS,
		Credits,
		Exit,
		None
	};

	extern int screenWidth;
	extern int screenHeight;

	extern const std::string GameName;

	extern Scene currentScene;

	extern bool programLoop;

	void Play();
}