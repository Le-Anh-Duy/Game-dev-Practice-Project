#include "entities.hpp"

entity::entity() {}
entity::~entity() {}

SDL_Texture* loadTexture(const char* filename, SDL_Renderer* &rend) {
	SDL_Texture* tex;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	std::cout << filename << ' ' << "after renderer" << &rend << std::endl;
	tex = IMG_LoadTexture(rend, filename);
	std::cout << "successfully loaded" << ' ' << filename << std::endl;
	return tex;
}

// void init(const char* name, SDL_Renderer *&rend);
void entity::init(const char* name, SDL_Renderer* rend) {
	texture = loadTexture(name, rend);
	x = y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}