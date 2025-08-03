CXX := g++
CXXFLAGS := -I dependencies/include
LDFLAGS := -L dependencies/lib
LDLIBS := -lmingw32 -lSDL2main -lSDL2

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)

engine: $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@ $(LDLIBS)
	$(MAKE) clean

# Pattern rule to compile each .cpp to .o
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o
