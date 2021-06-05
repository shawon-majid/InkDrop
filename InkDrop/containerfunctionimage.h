#include <iostream>

char ContainerImage[30] = "container\\container.bmp";

struct containers{
	double x, y;
	int type;
	int state;
};

void fillTheContainer(containers con, int r, int g, int b)
{
	if (con.state == 1){
		iSetColor(r, g, b);
		iFilledRectangle(con.x, con.y, 75, 16);
	}
	else if (con.state == 2){
		iSetColor(r, g, b);
		iFilledRectangle(con.x, con.y, 75, 32);
	}
	else if (con.state == 3){
		iSetColor(r, g, b);
		iFilledRectangle(con.x, con.y, 75, 48);
	}
}

void renderContainer(containers con){
	iShowBMP2(con.x, con.y, ContainerImage, 0);
	if (con.type == 0){ // color purple
		fillTheContainer(con, 128, 0, 128);
	}
	else if (con.type == 1){ // color blue
		fillTheContainer(con, 0, 0, 255);
	}
	else if (con.type == 2){
		fillTheContainer(con, 135, 206, 235);
	}
	else if (con.type == 3){
		fillTheContainer(con, 0, 128, 0);
	}
	else if (con.type == 4){
		fillTheContainer(con, 255, 255, 0);
	}
	else if (con.type == 5){
		fillTheContainer(con, 255, 165, 0);
	}
	else if (con.type == 6){
		fillTheContainer(con, 255, 0, 0);
	}
}