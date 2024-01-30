#Use the lib file to link

all:
	g++ -I src/include -L src/lib game.cpp main.cpp -o main -lmingw32 -lSDL2main -lSDL2 SDL2_image.lib