#pragma once

#include "raylib.h"
#include <iostream>

namespace text
{
	struct Text
	{
		Vector2 position;
		std::string text;

		int font;

		Color color;
	};

	Text Create(const std::string &text, float x, float y, int font, Color color);

	void Draw(const Text &text);
}
