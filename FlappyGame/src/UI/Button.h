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

		Texture2D texture;

		bool isPressed;
		bool isReleased;
		bool isMouseOnTop;
	};

	Button Create(const Rectangle &graph = {0,0,ButtonWidth, ButtonHeight}, const std::string &text = "example", int fontSize = ButtonFont, Color textColor = BLACK);

	Vector2 GetCenterPosition(const Button &);

	void SetPosition(Button& button, const Vector2& newPosition);

	bool MouseOnTop(Button &button);

	bool IsPressed(Button &button);

	void SetText(Button &button, const std::string &text);

	void Draw(const Button &button);

	void DeInit(Button &button);
}