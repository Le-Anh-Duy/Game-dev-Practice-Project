#Use the lib file to link

all: code/src/*.cpp
	g++ -I src/include -I assets/ -I code/headers -L src/lib $^ -o ./bin/main -lmingw32 -lSDL2main -lSDL2 SDL2_image.lib