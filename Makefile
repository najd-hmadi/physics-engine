all:
	g++ -I src/include -L src/lib -o engine engine.cpp -lmingw32 -lSDL2main -lSDL2