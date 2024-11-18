#include "SoundManager.h"

#include <array>
#include <raylib.h>
namespace game::utils::soundManager
{
	static const int bufferSpace = 10;

	static Music mainMenu;

	static Music gameMusic;

	static Music music;

	static Sound Jump;

	static Sound Hover;

	static Sound Click;

	static Sound Crash;

	static Sound PauseUp;

	static std::array<Sound, bufferSpace> soundBuffer;

	static int bufferCounter = 0;
	static int newSoundPos = 0;



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
			PlaySound(soundBuffer.at(bufferCounter));
			bufferCounter++;
			bufferCounter %= bufferSpace;
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