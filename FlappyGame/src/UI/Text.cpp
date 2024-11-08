#include "Text.h"

namespace text
{
    Text Create(const std::string &text, float x, float y, int font, Color color)
    {
        Text newText;

        newText.text = text;

        newText.position.x = x - static_cast<float>(MeasureText(text.c_str(), font)) / 2.0f;
        newText.position.y = y + static_cast<float>(font) / 2.0f;

        newText.font = font;

        newText.color = color;

        return newText;
    }

    void Draw(const Text &text)
    {
        DrawText(text.text.c_str(), static_cast<int>(text.position.x), static_cast<int>(text.position.y), text.font, text.color);
    }
}


