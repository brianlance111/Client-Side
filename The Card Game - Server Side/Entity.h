#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.h"

class Entity {
protected:
	Vector2f pos;
	SDL_Rect originalFrame;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	float scale;
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, int height, int width, int scale);
	Vector2f& getPos() { return pos; }
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	SDL_Rect getOriginalFrame() { return originalFrame; }
	float getScale() { return scale; }
	float getX();
	float getY();

	void changePOS(float a, float b);
	void changeScale(float a);

	bool isMouseOver(int mouseX, int mouseY);
};

class Card : public Entity {
	using Entity::Entity;
private:
	bool front = false;
	bool under = false;
public:
	bool isFront() { return front; }
	void setFront() { front = true; }
	void notFront() { front = false; }
	bool isUnder() { return under; }
	void setUnder() { under = true; }
	void notUnder() { under = false; }
};
