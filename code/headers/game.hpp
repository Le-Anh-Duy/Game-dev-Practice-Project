#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// SDL_Texture* playerTex;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	SDL_Texture* loadTexture(const char* tex_name, SDL_Renderer *&rend); // load texture from file name
	void blit(SDL_Texture* texture, int x, int y); // move a texture to a specific coordinate on the window
	SDL_Renderer *renderer;
	
private:
	SDL_Window *window;
	bool isRunning = false;
	int cnt = 0;
};

class entity: public Game {
public:

	entity();
	~entity();

	SDL_Texture* texture;
	int w;
	int h;
	int x;
	int y;

	bool up, down, left, right;

	void init(const char* name, SDL_Renderer *&rend);
	void move();
	void update();

private:

};