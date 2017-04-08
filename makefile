draw: draw.cpp Bridge.h Point.h 
	g++ draw.cpp -lm -lGL -lGLU -lglut -o draw -std=gnu++11 -g