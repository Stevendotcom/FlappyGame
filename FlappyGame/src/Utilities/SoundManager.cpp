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
	}




}