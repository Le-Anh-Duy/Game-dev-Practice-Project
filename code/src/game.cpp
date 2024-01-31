#include <deque>
#include "game.hpp"

entity::entity() {
	up = down = right = left = 0;
};

SDL_Renderer* GLOBAL_RENDERER;

entity::~entity() {
	std::cout << "this is being called" << std::endl;
	return;
	// SDL_DestroyTexture(texture);
};
void entity::move() {};
void entity::update() {
	if (up) y -= speed;
	if (down) y += speed;
	if (right) x += speed;
	if (left) x -= speed;
};

entity* gun = NULL;
Game::Game()
{}

Game::~Game()
{
	delete gun;
	return;
}

void entity::init(const char* name, SDL_Renderer* &rend) {
	std::cout << "after pass " << &rend << '\n';
	texture = loadTexture(name, rend);
	x = y = 0;
	speed = 4;
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

		GLOBAL_RENDERER = renderer;

	}

	gun = new entity;
	gun->init("assets/gun.png", renderer);
}

void shoot();
void handleKeyDown(SDL_KeyboardEvent *event) {
	if (event->repeat == 0)
	{
		switch (event->keysym.scancode)
		{
		case SDL_SCANCODE_UP:
			gun->up = 1;
			break;
		case SDL_SCANCODE_DOWN:
			gun->down = 1;
			break;
		case SDL_SCANCODE_LEFT:
			gun->left = 1;
			break;
		case SDL_SCANCODE_RIGHT:
			gun->right = 1;
			break;
		case SDL_SCANCODE_SPACE:
			shoot();
		default:
			break;
		}
	}
}

std::deque <entity*> bullets;

void shoot() {
	entity* bullet = new entity;
	bullet->init("assets/bullet.png", GLOBAL_RENDERER);
	bullet->speed = 10;
	bullet->x = gun->x;
	bullet->y = gun->y;
	bullet->right = true;
	bullet->left = bullet->up = bullet->down = false;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
	bullets.push_back(bullet);
}

void handleKeyUp(SDL_KeyboardEvent *event) {
	if (event->repeat == 0)
	{
		switch (event->keysym.scancode)
		{
		case SDL_SCANCODE_UP:
			gun->up = 0;
			break;
		case SDL_SCANCODE_DOWN:
			gun->down = 0;
			break;
		case SDL_SCANCODE_LEFT:
			gun->left = 0;
			break;
		case SDL_SCANCODE_RIGHT:
			gun->right = 0;
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
// SDL_Texture*       loadTexture(const char* tex_name, SDL_Renderer *&rend); // load texture from file name

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
	for (entity* bullet: bullets) 
		bullet->update();

	while (!bullets.empty()) {
		if (bullets.front()->x <= 1200) break;
		std::cout << "preparing for delete bullet" << std::endl;
		SDL_DestroyTexture(bullets.front()->texture);
		std::cout << "deleted successfully texture bullet" << std::endl;
		std::cout << "deleted successfully bullet" << std::endl;
		delete bullets.front();
		bullets.pop_front();
	}

	gun->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (entity* bullet: bullets)
		blit(bullet->texture, bullet->x, bullet->y);
	blit(gun->texture, gun->x, gun->y);
	
	
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}