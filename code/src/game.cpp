#include "game.hpp"
#include "gun.hpp"

Game::Game()
{}

Game::~Game()
{}

gun* pistal;

SDL_Renderer* GLOBAL_RENDERER;

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
		GLOBAL_RENDERER = renderer;
		pistal = new gun();
		pistal->init("assets/gun.png", renderer);
		std::cout << pistal->x << ' ' << pistal->y << '\n';
	}

}

void do_key_down(SDL_KeyboardEvent *event) {
		std::cout << "fucnasdfkas 22222222\n";

	if (event->repeat == 0)
		{
			switch (event->keysym.scancode)
			{
			case SDL_SCANCODE_UP:
				pistal->up = 1;
				break;
			case SDL_SCANCODE_DOWN:
				pistal->down = 1;
				break;
			case SDL_SCANCODE_LEFT:
				pistal->left = 1;
				break;
			case SDL_SCANCODE_RIGHT:
				pistal->right = 1;
				break;
			case SDL_SCANCODE_SPACE:
				pistal->shoot();
				pistal->fired_tail->init("assets/bullet.png", GLOBAL_RENDERER);
				break;
			default:
				break;
			}
		}
}
void do_key_up(SDL_KeyboardEvent *event) {
	if (event->repeat == 0)
		{
			switch (event->keysym.scancode)
			{
			case SDL_SCANCODE_UP:
				pistal->up = 0;
				break;
			case SDL_SCANCODE_DOWN:
				pistal->down = 0;
				break;
			case SDL_SCANCODE_LEFT:
				pistal->left = 0;
				break;
			case SDL_SCANCODE_RIGHT:
				pistal->right = 0;
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
			do_key_down(&event.key);
			break;
		case SDL_KEYUP:
			do_key_up(&event.key);
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
	pistal->fixed_dir();
	pistal->move();

	bullet* head = pistal->fired_head;
	while (head) {
		head->move();
		bullet* prev = head;
		head = head->pNext;
		if (prev->x > 500) pistal->vanish(prev);		
	}	
}

void Game::render() // reder all entities
{
	SDL_RenderClear(renderer);
	blit(pistal->texture, pistal->x, pistal->y);

	bullet* head = pistal->fired_head;
	
	while (head) {
		blit(head->texture, head->x, head->y);
		head = head->pNext;
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}