#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) :window(NULL), renderer(NULL) {
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
		std::cout << "Window failed to init. STD_ERROR: " << SDL_GetError() << '\n';

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load a texture. SDL_ERROR: " << SDL_GetError() << '\n';

	return texture;
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}

void RenderWindow::cleanUp() {
	SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity)
{
	SDL_Rect destRect;
	destRect.x = static_cast<int>(entity.getPos().x);
	destRect.y = static_cast<int>(entity.getPos().y);
	destRect.w = entity.getOriginalFrame().w * entity.getScale();
	destRect.h = entity.getOriginalFrame().h * entity.getScale();

	SDL_RenderCopy(renderer, entity.getTex(), nullptr, &destRect);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}
