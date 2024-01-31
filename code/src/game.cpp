#include "game.hpp"
entity::entity() {
	up = down = right = left = 0;
};
entity::~entity() {};
void entity::move() {};
void entity::update() {

	if (up) y -= 4;
	if (down) y += 4;
	if (right) x += 4;
	if (left) x -= 4;

};

entity* mainChar = NULL;
Game::Game()
{}

Game::~Game()
{
	delete mainChar;
}



void entity::init(const char* name, SDL_Renderer* &rend) {
	std::cout << "after pass " << &rend << '\n';
	texture = loadTexture(name, rend);
	x = y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	w = 100; h = 100;
}


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
		std::cout << "init renderer" << ' ' << &renderer << std::endl;
		isRunning = true;
	}

	mainChar = new entity;
	std::cout << "should renderer" << ' ' << &renderer << std::endl;
	mainChar->init("assets/player.png", renderer);
}


void handleKeyDown(SDL_KeyboardEvent *event) {
	if (event->repeat == 0)
	{
		switch (event->keysym.scancode)
		{
		case SDL_SCANCODE_UP:
			mainChar->up = 1;
			break;
		case SDL_SCANCODE_DOWN:
			mainChar->down = 1;
			break;
		case SDL_SCANCODE_LEFT:
			mainChar->left = 1;
			break;
		case SDL_SCANCODE_RIGHT:
			mainChar->right = 1;
			break;
		default:
			break;
		}
	}
}

void handleKeyUp(SDL_KeyboardEvent *event) {
	if (event->repeat == 0)
	{
		switch (event->keysym.scancode)
		{
		case SDL_SCANCODE_UP:
			mainChar->up = 0;
			break;
		case SDL_SCANCODE_DOWN:
			mainChar->down = 0;
			break;
		case SDL_SCANCODE_LEFT:
			mainChar->left = 0;
			break;
		case SDL_SCANCODE_RIGHT:
			mainChar->right = 0;
			break;
		
		default:
			break;
		}
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
		case SDL_KEYDOWN:
			handleKeyDown(&event.key);
			break;
		case SDL_KEYUP:
			handleKeyUp(&event.key);
			break;
		default:
			break;
	}
}

SDL_Texture* Game::loadTexture(const char* filename, SDL_Renderer* &rend) {
	SDL_Texture* tex;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	std::cout << filename << ' ' << "after renderer" << &rend << std::endl;
	tex = IMG_LoadTexture(rend, filename);
	std::cout << "successfully loaded" << ' ' << filename << std::endl;
	return tex;
}

void Game::blit(SDL_Texture* texture, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	std::cout << "Move: " << x << ' ' << y << '\n';

	// SDL_QueryTexture(texture, NULL, NULL, &dest.h, &dest.w);
	dest.h = dest.w = 100;
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Game::update()
{
	cnt++;
	std::cout << cnt << ' ' << &renderer << std::endl;
	mainChar->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	blit(mainChar->texture, mainChar->x, mainChar->y);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}