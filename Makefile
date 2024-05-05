LIB = -lm -lGL -lGLU -lglut
SRC = main.cpp
OUT = raytracer
SET = -finput-charset=latin2 -std=c++98 -Wall -Wextra -g

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS)) 

%.o: %.cpp
	$(CXX) $(SET) -c $<

raytracer: $(OBJS)
	$(CXX) $(LIB) $(SET) -o $(@) $^
