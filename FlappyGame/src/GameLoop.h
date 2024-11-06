#pragma once

#include <iostream>

namespace game
{
	enum class SCENE
	{
		MENU,
		GAMEPLAY,
		//OPTIONS,
		CREDITS,
		EXIT,
		NONE
	};

	extern int screenWidth;
	extern int screenHeight;

	extern const std::string GameName;

	extern SCENE currentScene;

	extern bool programLoop;

	void Play();
}