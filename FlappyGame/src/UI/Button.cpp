#include "Button.h"

#include "Utilities/Utils.h"

namespace button
{
	Button Create(const Rectangle &graph, const std::string &text, int fontSize, Color textColor)
	{
		Button newButton;

		newButton.graph = graph;

		SetPosition(newButton, Vector2{ graph.x, graph.y });

		newButton.text.text = text;
		newButton.text.font = fontSize;
		newButton.text.color = textColor;

		newButton.isMouseOnTop = false;
		newButton.isPressed = false;
		newButton.isReleased = false;

		newButton.texture = LoadTexture("res/UI_Flat_Banner01a.png");

		SetText(newButton, text);

		return newButton;
	}



	Vector2 GetCenterPosition(const Button &button)
	{
		Vector2 centerPosition;

		centerPosition.x = button.graph.x + (button.graph.width / 2);
		centerPosition.y = button.graph.y + (button.graph.height / 2);

		return centerPosition;
	}



	void SetPosition(Button &button, const Vector2 &newPosition)
	{
		button.graph.x = newPosition.x - (button.graph.width / 2);
		button.graph.y = newPosition.y - (button.graph.height / 2);
	}



	bool MouseOnTop(Button &button)
	{
		Vector2 mousePosition = GetMousePosition();

		float minValueX = button.graph.x;
		float minValueY = button.graph.y;

		float maxValueX = button.graph.x + button.graph.width;
		float maxValueY = button.graph.y + button.graph.height;

		bool onTopX = (mousePosition.x >= minValueX && mousePosition.x <= maxValueX);
		bool onTopY = (mousePosition.y >= minValueY && mousePosition.y <= maxValueY);

		if (onTopX && onTopY)
		{
			button.isMouseOnTop = true;
		} else
		{
			button.isMouseOnTop = false;
		}

		return button.isMouseOnTop;
	}



	bool IsPressed(Button &button)
	{
		bool isReleassed = false;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			if (button.isMouseOnTop)
				isReleassed = true;
			

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			if (button.isMouseOnTop)
				button.isPressed = true;
			else
				button.isPressed = false;
		} 
		else
			button.isPressed = false;

		return isReleassed;
	}



	void SetText(Button &button, const std::string &text)
	{
		button.text.text = text;

		button.text.position.x = button.graph.x + (button.graph.width / 2) - static_cast<float>(MeasureText(button.text.text.c_str(), button.text.font)) / 2.0f;
		button.text.position.y = button.graph.y + (button.graph.height / 2) - static_cast<float>((button.text.font)) / 2.0F + 5;
	}



	void Draw(const Button &button)
	{
		Color colorUsed;

		if (button.isPressed)
			colorUsed = GRAY;
		else if (button.isMouseOnTop)
			colorUsed = DARKGRAY;
		else
			colorUsed = WHITE;

		DrawTexturePro(button.texture, { 0, 0, static_cast<float>(button.texture.width), static_cast<float>(button.texture.height) }, button.graph, { 0, 0 }, 0, colorUsed);

		text::Draw(button.text);
	}



	void DeInit(Button &button) 
	{ 
		UnloadTexture(button.texture);
	}
}