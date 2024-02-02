#include "game.hpp"
#include "gun.hpp"

Game::Game()
{}

Game::~Game()
{}

gun* pistal;

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}

	{
		pistal = new gun;
		pistal->init("assets/gun.png", renderer);
	}

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT :
			isRunning = false;
			break;
		default:
			break;
	}
}


SDL_Texture* Game::loadTexture(const char* filename, SDL_Renderer* &rend) {
	SDL_Texture* tex;
	tex = IMG_LoadTexture(rend, filename);
	return tex;
}

void Game::blit(SDL_Texture* texture, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Game::update()
{
	cnt++;	
}

void Game::render() // reder all entities
{
	SDL_RenderClear(renderer);
	blit(pistal->texture, pistal->x, pistal->y);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}