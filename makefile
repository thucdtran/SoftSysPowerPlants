draw: draw.cpp  Model.h Model.cpp
	g++ draw.cpp Model.cpp -lm -lGL -lGLU -lglut -o draw