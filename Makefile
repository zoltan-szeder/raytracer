LINT = cppcheck
SW = --enable=all
CPP = g++
LIB = -lm -lGL -lGLU -lglut
SRC = main.cpp
EXTENSIONS = --check-config
OUT = raytracer
SET = -finput-charset=latin2 -std=c++98 -Wall -Wextra -g
FIN = *.cpp

SRCS := $(wildcard *.cpp)

build:
	$(CPP) $(LIB) $(SET) $(SRCS) -o $(OUT)
