#include "Pause.h"

#include "raylib.h"

#include "GameLoop.h"
#include "UI/Button.h"
#include "Utilities/SoundManager.h"

namespace game::entities::pause
{
	bool wasOnTop = false;
	bool isOnTop = false;

	void Update(button::Button& resume, button::Button& menu, bool lost)
	{
		isOnTop = MouseOnTop(resume) && !lost;
		isOnTop = MouseOnTop(menu) || isOnTop;
		if (isOnTop)
		{
			if (!wasOnTop)
				AddToBuffer(utils::soundManager::Sounds::Hover);
			wasOnTop = true;
		} else
			wasOnTop = false;
	}



	void Draw(button::Button resume, button::Button menu, std::string message, std::string messageScore, std::string messagePause, float fontSizeLost, float fontSizeScore, bool lost)
	{
		Vector2 size = MeasureTextEx(defFont, message.c_str(), fontSizeLost, 1);
		Vector2 sizePause = MeasureTextEx(defFont, messagePause.c_str(), fontSizeScore, 1);
		Vector2 sizeScore = MeasureTextEx(defFont, messageScore.c_str(), fontSizeScore, 1);

		DrawRectangle(0, 0, screenWidth, screenHeight, { 50, 50, 50, 200 });
		if (lost)
		{
			DrawTextEx(defFont, message.c_str(), { (static_cast<float>(GetScreenWidth()) - size.x) / 2, size.y }, fontSizeLost, 1, WHITE);
			DrawTextEx(defFont, messageScore.c_str(), { (static_cast<float>(GetScreenWidth()) - sizeScore.x) / 2, sizeScore.y + 100 }, fontSizeScore, 1, WHITE);
		} else
		{
			button::Draw(resume);
			DrawTextEx(defFont, messagePause.c_str(), { (static_cast<float>(GetScreenWidth()) - sizePause.x) / 2, sizePause.y }, fontSizeScore, 1, WHITE);
		}

		button::Draw(menu);
	}
}