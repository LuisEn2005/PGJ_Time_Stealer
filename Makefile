CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET = game

RAYLIB_TOOLS = RaylibTools
RAYLIB_TOOLS_OBJ = $(RAYLIB_TOOLS)/buttons/button.o \
                   $(RAYLIB_TOOLS)/buttons/textbutton.o \
                   $(RAYLIB_TOOLS)/buttons/texturebutton.o \
                   $(RAYLIB_TOOLS)/utils/rng.o \
                   $(RAYLIB_TOOLS)/utils/text.o \
                   $(RAYLIB_TOOLS)/utils/timer.o

SOURCES = main.cpp \
	  Entities/player.cpp \
	  Entities/obstacle.cpp

OBJECTS = $(SOURCES:.cpp=.o)

ALL_OBJECTS = $(OBJECTS) $(RAYLIB_TOOLS_OBJ)

all: $(TARGET)

$(TARGET): $(ALL_OBJECTS)
	$(CXX) $(CXXFLAGS) $(ALL_OBJECTS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(RAYLIB_TOOLS)/%.o: $(RAYLIB_TOOLS)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -f $(TARGET) $(OBJECTS)
	$(MAKE) -C $(RAYLIB_TOOLS) clean

.PHONY: all clean
