default:
	g++ ../src/*.cpp -o Game.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopeng132 -lgdi32 -lwinmm
