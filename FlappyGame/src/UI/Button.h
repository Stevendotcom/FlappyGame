#pragma once

#include "raylib.h"

#include "Text.h"

namespace button
{
	const float ButtonWidth = 180;
	const float ButtonHeight = 60;
	const int ButtonFont = 20;

	struct Button
	{
		text::Text text;

		Rectangle graph;

		bool isPressed;
		bool isReleased;
		bool isMouseOnTop;
	};

	Button Create(Rectangle graph = {0,0,ButtonWidth, ButtonHeight}, std::string text = "example", int fontSize = ButtonFont, Color textColor = WHITE);

	Vector2 GetCenterPosition(Button);

	void SetPosition(Button& button, Vector2 newPosition);

	bool MouseOnTop(Button&);
	bool IsPressed(Button&);

	void SetText(Button& button, std::string text);

	void Draw(Button);
}