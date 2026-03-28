CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Iinclude
TARGET   = pathfinder
SRCDIR   = src
SRCS     = $(SRCDIR)/main.cpp \
           $(SRCDIR)/Graph.cpp \
           $(SRCDIR)/DataLoader.cpp \
           $(SRCDIR)/Dijkstra.cpp \
           $(SRCDIR)/AStar.cpp \
           $(SRCDIR)/Menu.cpp

OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf data/
