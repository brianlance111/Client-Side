#include "Entity.h"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int height, int width, int scale)
	:pos(p_pos), tex(p_tex), scale(scale)
{
	std::cout << "pos: ";
	pos.print();
	originalFrame.w = width;
	originalFrame.h = height;
	originalFrame.x = p_pos.x;
	originalFrame.y = p_pos.y;

	currentFrame.w = width * scale;
	currentFrame.h = height * scale;
	currentFrame.x = p_pos.x;
	currentFrame.y = p_pos.y;
}

SDL_Texture* Entity::getTex() { return tex; }
SDL_Rect Entity::getCurrentFrame() { return currentFrame; }

float Entity::getX()
{
	return pos.x;
}

float Entity::getY()
{
	return pos.y;
}

void Entity::changePOS(float a, float b){
	pos.x = a;
	pos.y = b;
	currentFrame.x = a;
	currentFrame.y = b;
}

void Entity::changeScale(float a){
	scale = a;
	currentFrame.h = originalFrame.h * scale;
	currentFrame.w = originalFrame.w * scale;
}

bool Entity::isMouseOver(int mouseX, int mouseY)
{
	return (mouseX >= currentFrame.x && mouseX <= currentFrame.x + currentFrame.w
		&& mouseY >= currentFrame.y && mouseY <= currentFrame.y + currentFrame.h);
}
