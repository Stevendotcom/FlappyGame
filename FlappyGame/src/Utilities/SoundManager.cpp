#include "SoundManager.h"

#include "raylib.h"
#include <array>
#include <iostream>

namespace game::utils::soundManager
{
	static const int bufferSpace = 10;

	static Music mainMenu;

	static Music gameMusic;

	static Music music;

	static Sound jump;

	static Sound hover;

	static Sound click;

	static Sound crash;

	static Sound pauseUp;

	static std::array<Sound, bufferSpace> soundBuffer;

	static int bufferCounter = 0;

	static int newSoundPos = 0;



	void Init()
	{
		mainMenu = LoadMusicStream("res/StrangeFarm.ogg");
		gameMusic = LoadMusicStream("res/InTheCastle.ogg");
		jump = LoadSound("res/cannon-firing.mp3");
		hover = LoadSound("res/JDSherbert-Ultimate_UI_SFX_Pack-Cursor-4.ogg");
		click = LoadSound("res/JDSherbert-Ultimate_UI_SFX_Pack-Select-2.ogg");
		crash = LoadSound("res/JDSherbert-Ultimate_UI_SFX_Pack-Error-1.ogg");
		pauseUp = LoadSound("res/JDSherbert-Ultimate_UI_SFX_Pack-Swipe-2.ogg");
		music = mainMenu;
		PlayMusicStream(music);
	}



	void Update()
	{
		UpdateMusicStream(music);

		if (newSoundPos != bufferCounter)
		{
			bufferCounter++;
			bufferCounter %= bufferSpace;
			PlaySound(soundBuffer.at(bufferCounter));
		}
	}



	void ChangeMusic(Musics nextMusic)
	{
		StopMusicStream(music);

		switch (nextMusic)
		{

		case Musics::MainMenu:
			music = mainMenu;
			break;

		case Musics::Game:
			music = gameMusic;
			break;

		default:
			std::cerr << "Music index not expected";
			music = gameMusic;
			break;

		}

		PlayMusicStream(music);
	}



	void AddToBuffer(Sounds sound)
	{
		newSoundPos++;
		newSoundPos %= bufferSpace;

		switch (sound)
		{

		case Sounds::Jump:
			soundBuffer.at(newSoundPos) = LoadSoundAlias(jump);
			break;

		case Sounds::Hover:
			soundBuffer.at(newSoundPos) = LoadSoundAlias(hover);
			break;

		case Sounds::Click:
			soundBuffer.at(newSoundPos) = LoadSoundAlias(click);
			break;

		case Sounds::Crash:
			soundBuffer.at(newSoundPos) = LoadSoundAlias(crash);
			break;

		case Sounds::PauseUp:
			soundBuffer.at(newSoundPos) = LoadSoundAlias(pauseUp);
			break;

		default:
			std::cerr << "Sound index not expected";
			break;
		}
	}



	void DeInit()
	{
		for (auto sound : soundBuffer)
		{
			UnloadSoundAlias(sound);
		}

		UnloadMusicStream(mainMenu);
		UnloadMusicStream(gameMusic);
		UnloadSound(jump);
		UnloadSound(hover);
		UnloadSound(click);
		UnloadSound(crash);
		UnloadSound(pauseUp);
	}

}