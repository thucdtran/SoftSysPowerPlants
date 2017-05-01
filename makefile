draw: draw.cpp Bridge.h Point.h Beam.h
	g++ draw.cpp Beam.cpp Point.cpp -lm -lGL -lGLU -lglut -o draw -std=gnu++11 -g -lpthread