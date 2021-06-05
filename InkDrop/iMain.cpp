#define _CRT_SECURE_NO_WARNINGS
#include "iGraphics.h"
#include <iostream>
#include <fstream> 
#include "inkfunction.h"
//#include "containerfunction.h"
#include "containerfunctionimage.h"

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

int HORIZONTAL = 500, VERTICAL = 600;
int ContainerSpeed = 10;
int HeightFromGround = 25;
int InkSpeed = 1;
int Distance = 200;
int containerWidth = 75;
int points = 0;
int life = 5;
int gameState = 0;
int level = 4;
//int r = 0, g = 0, b = 0;
bool hasStarted = 0;

containers con[7];
inkDrop ink[7];
char scorechar[15];
char lifechar[15];
char highscorechar[15];



void convertPoint(int n);
void convertLife(int n);
void setAll(){

	int sum = 25;
	// set the container
	for (int i = 0; i < 7; i++){
		con[i].x = sum;
		con[i].y = HeightFromGround;
		con[i].type = -1; // no color
		con[i].state = 0; // number of color 0
		sum += 125;
	}


	// set the ink
	ink[0].x = rand() % 500;
	ink[0].y = VERTICAL + (rand() % 100);
	ink[0].type = 0;

	for (int i = 1; i < 7; i++){
		ink[i].x = rand() % 500;
		ink[i].y = ink[i - 1].y + Distance;
		ink[i].type = i;
	}

	// set score & life
	convertPoint(points);
	convertLife(life);
}

void resetAll(){
	points = 0;
	life = 5;
	int sum = 25;
	// set the container
	for (int i = 0; i < 7; i++){
		con[i].x = sum;
		con[i].y = HeightFromGround;
		con[i].type = -1; // no color
		con[i].state = 0; // number of color 0
		sum += 125;
	}


	// set the ink
	ink[0].x = rand() % 500;
	ink[0].y = VERTICAL + (rand() % 100);
	ink[0].type = 0;

	for (int i = 1; i < 7; i++){
		ink[i].x = rand() % 500;
		ink[i].y = ink[i - 1].y + Distance;
		ink[i].type = i;
	}

	// set score & life
	convertPoint(points);
	convertLife(life);
	hasStarted = 0;
}

void convertPoint(int n)
{
	int ind = 0;
	while (n){
		int temp = n % 10;
		char c = temp + 48;
		scorechar[ind] = c;
		ind++;
		n /= 10;
	}
	scorechar[ind] = '\0';
	_strrev(scorechar);
}

void convertLife(int n)
{
	int ind = 0;
	while (n){
		int temp = n % 10;
		char c = temp + 48;
		lifechar[ind] = c;
		ind++;
		n /= 10;
	}
	lifechar[ind] = '\0';
	_strrev(lifechar);
}
void convertHighsScore(int n)
{
	int ind = 0;
	while (n){
		int temp = n % 10;
		char c = temp + 48;
		highscorechar[ind] = c;
		ind++;
		n /= 10;
	}
	highscorechar[ind] = '\0';
	_strrev(highscorechar);
}


void showHighScore(){
	iShowBMP(0, 0, "pictures\\highscore.bmp");
	FILE* fpo;
	fpo = fopen("highscore.txt", "a");
	fclose(fpo);
	FILE* fp;
	fp = fopen("highscore.txt", "r"); 
	int s = 0;
	while (!feof(fp)){
		fscanf(fp, "%d", &s);
	}
	fclose(fp);
	convertHighsScore(s);
	iSetColor(0, 0, 0);
	iText((HORIZONTAL / 2)-5, (VERTICAL / 2)+15, highscorechar, GLUT_BITMAP_TIMES_ROMAN_24);
}

void saveScore(int score)
{
	FILE* fp;
	fp = fopen("highscore.txt", "a+" ); 
	int highestTillNow;
	fscanf(fp, "%d", &highestTillNow);
	fclose(fp);
	if (score > highestTillNow){
		FILE * fpw;
		fpw = fopen("highscore.txt", "w");
		fprintf(fpw, "%d", score);
		fclose(fpw);
	}
}

void showMenu(){
	iShowBMP(0, 0, "pictures\\inkbg.dib");
	iShowBMP2(25, VERTICAL - 200, "pictures\\inkdrop.dib", 0);
	iShowBMP2(5, VERTICAL - 230, "pictures\\play.dib", 0);
	iShowBMP2(5, VERTICAL - 305, "pictures\\highscore.dib", 0);
	iShowBMP2(5, VERTICAL - 380, "pictures\\instruction.dib", 0);
	iShowBMP2(5, VERTICAL - 455, "pictures\\about.dib", 0);
	iShowBMP2(5, VERTICAL - 530, "pictures\\exit.dib", 0);
}

void iDraw()
{
	iClear();

	if (gameState == 0){
		showMenu();
	}
	else if (gameState == 1){ // play
		//set background
		iShowBMP(0, 0, "pictures\\playbg.dib");

		// score & life
		//iSetColor(128, 0, 128);
		iText(5, VERTICAL - 30, "SCORE: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(90, VERTICAL - 30, scorechar, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(5, VERTICAL - 60, "LIFE: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(70, VERTICAL - 60, lifechar, GLUT_BITMAP_TIMES_ROMAN_24);

		if (hasStarted){
			// render rectangle
			for (int i = 0; i < 7; i++){
				renderContainer(con[i]);
			}
			// render ink
			for (int i = 0; i < 7; i++){
				iShowBMP2(ink[i].x, ink[i].y, inkName[ink[i].type], 0);
			}
		}
		else{
			iSetColor(255, 0, 0);
			iText(HORIZONTAL / 2 - 100, VERTICAL / 2 - 100, "Press p to play/pause", GLUT_BITMAP_HELVETICA_18);
			for (int i = 0; i < 7; i++){
				renderContainer(con[i]);
			}
			// render ink
			for (int i = 0; i < 7; i++){
				iShowBMP2(ink[i].x, ink[i].y, inkName[ink[i].type], 0);
			}
		}
	}
	else if (gameState == 2){ // highscore
		showHighScore();
	}
	else if (gameState == 3){ // instruction
		iShowBMP(0, 0, "pictures\\inkdrop_instruction.bmp");
	}
	else if (gameState == 4){ // about
		iShowBMP(0, 0, "pictures\\about.bmp");
	}
	else if (gameState == 5){ // afterplay
		iShowBMP(0, 0, "pictures\\sorrybg.dib");
		iShowBMP2(25, VERTICAL - (142 + 30), "pictures\\sorry.dib", 0);
		iSetColor(0, 0, 0);
		iText((HORIZONTAL / 2) - 40+20, VERTICAL - (172 + 50), scorechar, GLUT_BITMAP_TIMES_ROMAN_24);		
		iSetColor(255, 255, 255);
		iText(HORIZONTAL / 2 - 40, VERTICAL - (172 + 200+200), "press enter to continue", GLUT_BITMAP_HELVETICA_18);
	}
	else if (gameState == 6){ // exit
		exit(0);
	}


}

bool checkLanding(int prev_x, containers con){
	return (prev_x >= con.x && prev_x <= con.x + containerWidth);
}

void change(){
	//if (points >= 10 && points <= 20){
	//	level--;
	//}
	//if (points >= 20 && points <= 50){
	//	level--;
	//}
	if (hasStarted){
		for (int i = 0; i < 7; i++){
			ink[i].y -= InkSpeed;
			if (ink[i].y <= 65){ // when ink touches container
				int prev_x = ink[i].x;
				ink[i].y = VERTICAL + Distance * level;
				ink[i].x = rand() % 500;

				int requiredType = ink[i].type;
				bool landedCorrectly = 0;
				for (int j = 0; j < 7; j++){
					if (checkLanding(prev_x, con[j])){
						landedCorrectly = 1;
						if (con[j].state){
							if (con[j].type == requiredType){
								con[j].state++;
								if (con[j].state == 3){
									con[j].state = 0;
									con[j].type = -1;
									points += 5;
								}
								points++;
								convertPoint(points);
								saveScore(points);
							}
							else{
								life--;
								if (life == 0){
									hasStarted = 0;
									gameState = 5;
								}
								convertLife(life);
							}
						}
						else{
							con[j].type = ink[i].type;
							con[j].state++;
							points++;
							convertPoint(points);
							saveScore(points);
						}
					}
				}
				if (!landedCorrectly){
					life--;
					if (life == 0){
						hasStarted = 0;
						gameState = 5;
					}
					convertLife(life);
				}
			}
		}
	}
}





/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{

}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//5, VERTICAL - 230 play
		if (gameState == 0){
			if (mx >= 5 && mx <= 5 + 108 && my >= VERTICAL - 230 && my <= (VERTICAL - 230) + 50){
				gameState = 1;
			}

			//5, VERTICAL - 305
			else if (mx >= 5 && mx <= 5 + 225 && my >= VERTICAL - 305 && my <= (VERTICAL - 305) + 50){
				gameState = 2;
			}
			// 5, VERTICAL - 380,
			else if (mx >= 5 && mx <= 5 + 273 && my >= VERTICAL - 380 && my <= (VERTICAL - 380) + 50){
				gameState = 3;
			}
			// 5, VERTICAL - 455,
			else if (mx >= 5 && mx <= 5 + 178 && my >= VERTICAL - 455 && my <= (VERTICAL - 455) + 50){
				gameState = 4;
			}
			// 5, VERTICAL - 530, exit
			else if (mx >= 5 && mx <= 5 + 131 && my >= VERTICAL - 530 && my <= (VERTICAL - 530) + 50){
				gameState = 6;
			}
		}
	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (key == 'w')
	{
		ContainerSpeed += 2;
	}
	else if (key == 's'){
		ContainerSpeed -= 2;
	}
	else if (key == '\b'){
		gameState = 0;
		hasStarted = 0;
		resetAll();
	}
	else if (key == 'p'){
		if (hasStarted) hasStarted = 0;
		else hasStarted = 1;
	}
	else if (key == '\r'){ // enter
		resetAll();
		gameState = 0;
	}

}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{


	if (key == GLUT_KEY_RIGHT)
	{
		for (int i = 0; i < 7; i++){
			con[i].x += ContainerSpeed;
			if (con[i].x >= 775){
				con[i].x = -100.9;
			}
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		for (int i = 0; i < 7; i++){
			con[i].x -= ContainerSpeed;
			if (con[i].x <= -101){
				con[i].x = 774.9;
			}
		}
	}

	if (key == GLUT_KEY_HOME)
	{

	}

}


int main()
{
	srand((unsigned)time(NULL));
	setAll();
	iSetTimer(5, change);
	iInitialize(HORIZONTAL, VERTICAL, "Ink");
	///updated see the documentations
	iStart();
	return 0;
}