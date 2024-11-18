#pragma once

namespace game::utils::soundManager
{
	enum class Musics
	{
		MainMenu,
		Game
	};

	enum class Sounds
	{
		Jump,
		Hover,
		Click,
		Crash,
		PauseUp
	};


	void Init();

	void Update();

	void ChangeMusic(Musics nextMusic);

	void AddToBuffer(Sounds sound);

	void DeInit();

}