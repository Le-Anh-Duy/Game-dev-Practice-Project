#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// SDL_Texture* playerTex;
class Game
{
public:

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	SDL_Texture* loadTexture(const char* filename, SDL_Renderer *&rend); // load texture from file name into game
	void blit(SDL_Texture* texture, int x, int y); // move a texture to a specific coordinate on the window
	
	Game();
	~Game();
private:
	SDL_Renderer *renderer;
	SDL_Window *window;
	bool isRunning = false;
	int cnt = 0;
};
