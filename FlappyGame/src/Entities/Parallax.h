#pragma once
#include "raylib.h"

#include <string>

namespace game::entities::parallax
{
	struct Parallax
	{
		Texture2D texture;
		float offset;
		float velocity;
	};


	void Init(Parallax& parallax, const std::string &texturePath, float velocity);
	void Update(Parallax& parallax);
	void Draw(const Parallax &parallax);
	void Deinit(const Parallax& parallax);
}
