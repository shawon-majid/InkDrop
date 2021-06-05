#include <iostream>

char inkName[7][20] = {
	"ink\\purple.bmp",
	"ink\\blue.bmp",
	"ink\\sky.bmp",
	"ink\\green.bmp",
	"ink\\yellow.bmp",
	"ink\\orange.bmp",
	"ink\\red.bmp",
};
struct inkDrop{
	double x, y;
	int type;
};