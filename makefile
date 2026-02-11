CXX = g++
CXXFLAGS = `sdl2-config --cflags --libs`

TARGET = sdl2-program
SRC = openWindow.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS)

clean:
	rm -f $(TARGET)