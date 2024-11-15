#include "parallax.h"


namespace game::entities::parallax
{
	void Init(Parallax &parallax, const std::string &texturePath, float velocity) {
		parallax.texture = LoadTexture(texturePath.c_str());


		parallax.texture.width = GetScreenWidth();
		parallax.texture.height = GetScreenHeight();

		parallax.offset = 0.0;

		parallax.velocity = velocity;

	}



	void Update(Parallax &parallax) {
		parallax.offset -= (parallax.offset <= static_cast<float>(-parallax.texture.width)) ? parallax.offset : parallax.velocity * GetFrameTime();
	}



	void Draw(const Parallax &parallax) {
		DrawTextureEx(parallax.texture, { parallax.offset, 0 }, 0, 1, WHITE);
		DrawTextureEx(parallax.texture, { static_cast<float>(parallax.texture.width) + parallax.offset, 0 }, 0, 1, WHITE);
	}



	void Deinit(const Parallax &parallax) {
		UnloadTexture(parallax.texture);
	}
}