all:
	g++ -I src/include -L src/lib -o visualizer visualizer.cpp -lmingw32 -lSDL2main -lSDL2