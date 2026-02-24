CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++98 -I include
TARGET = mazechart

SRCS = src/main.cpp src/args.cpp src/maze_io.cpp src/renderer.cpp \
       src/jgraph_util.cpp \
       src/symbol_wall.cpp src/symbol_open.cpp src/symbol_start.cpp \
       src/symbol_end.cpp src/symbol_path.cpp

OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
