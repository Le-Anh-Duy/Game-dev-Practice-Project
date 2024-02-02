#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


class entity {
public:

	entity();
	~entity();

	SDL_Texture* texture;
	int w;
	int h;
	int x;
	int y;

	void init(const char* name, SDL_Renderer* rend);
private:

};