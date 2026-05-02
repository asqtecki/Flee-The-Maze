PROJECT_NAME = game

RAYLIB_PATH = C:/raylib/raylib

SRC = $(wildcard *.cpp) $(wildcard src/*.cpp)

CXX = g++

CXXFLAGS = -std=c++17 -Wall \
	-Iinclude \
	-I$(RAYLIB_PATH)/src \
	-I$(RAYLIB_PATH)/src/external

LDFLAGS = -L$(RAYLIB_PATH)/src -lraylib \
	-lopengl32 -lgdi32 -lwinmm

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC) \
		$(RAYLIB_PATH)/src/raylib.rc.data \
		$(LDFLAGS)

clean:
	del $(PROJECT_NAME).exe 2>nul || true