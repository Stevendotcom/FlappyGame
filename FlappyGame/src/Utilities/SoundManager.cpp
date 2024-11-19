#include "SoundManager.h"

#include <array>
#include <iostream>
#include <raylib.h>

namespace game::utils::soundManager
{
	const int bufferSpace = 10;

	Music mainMenu;

	Music gameMusic;

	Music music;

	Sound Jump;

	Sound Hover;

	Sound Click;

	Sound Crash;

	Sound PauseUp;

	std::array<Sound, bufferSpace> soundBuffer;

	int bufferCounter = 0;

	int newSoundPos = 0;



	void Init()
	{
		mainMenu = LoadMusicStream("res/StrangeFarm.ogg");
		gameMusic = LoadMusicStream("res/InTheCastle.ogg");
		Jump = LoadSound("res/cannon-firing.mp3");
		Hover = LoadSound("res/JDSherbert-Ultimate_UI_SFX_Pack-Cursor-4.ogg");
		Click = LoadSound("res/JDSherbert-Ultimate_UI_SFX_Pack-Select-2.ogg");
		Crash = LoadSound("res/JDSherbert-Ultimate_UI_SFX_Pack-Error-1.ogg");
		PauseUp = LoadSound("res/JDSherbert-Ultimate_UI_SFX_Pack-Swipe-2.ogg");
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
			soundBuffer.at(newSoundPos) = LoadSoundAlias(Jump);
			break;
		case Sounds::Hover:
			soundBuffer.at(newSoundPos) = LoadSoundAlias(Hover);
			break;
		case Sounds::Click:
			soundBuffer.at(newSoundPos) = LoadSoundAlias(Click);
			break;
		case Sounds::Crash:
			soundBuffer.at(newSoundPos) = LoadSoundAlias(Crash);
			break;
		case Sounds::PauseUp:
			soundBuffer.at(newSoundPos) = LoadSoundAlias(PauseUp);
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
		UnloadSound(Jump);
		UnloadSound(Hover);
		UnloadSound(Click);
		UnloadSound(Crash);
		UnloadSound(PauseUp);
	}

}