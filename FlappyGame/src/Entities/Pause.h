#pragma once
#include "UI/Button.h"

namespace game::entities::pause
{

	void Update(button::Button resume, button::Button menu);

	void Draw(button::Button resume, button::Button menu, std::string message, std::string messageScore, std::string messagePause, float fontSizeLost, float fontSizeScore, bool lost);

}