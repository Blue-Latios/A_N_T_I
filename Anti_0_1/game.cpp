///Compiling shortcut (Linux): g++ -o message message.cpp -lGL -lGLU -lglfw ///
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <iostream>
#include "randomer.hpp"
using namespace std;

#include <fstream>
#include "Time.hpp"
#include "Letter.hpp"
#include "SquareObj.hpp"

///Global variables
int linesize;
double WINDOW_HEIGHT;
double WINDOW_WIDTH;
#define CURSOR_HEIGHT 4
#define CURSOR_WIDTH 4

float sqrtTwo = sqrt(2);

double xpos, ypos;
double newxpos, newypos;
GLfloat pixColor[4];

Time timeeffect;
Time worldtime[20];
int worldn = 0;
Time delaytime;
bool disabled = false;
bool gameover = false;
bool initgame = false;

float pausetext[1000];
int pausemark[3];
const string pause1 = "PAUSED";
const string pause2 = "Press P to resume";

float gameovertext[1200];
int gameovermark[3];
const string gameover1 = "GAME OVER";

float mainmenutext[1500];
int mainmenumark[4];
const string mainmenu1 = "A N T I";
const string mainmenu2 = "Press S to start game";
const string mainmenu3 = "Press Esc to quit";

float timetext[1000];
int timemark[2];

GLfloat borders[8] = {-1.0,-1.0, -1.0,1.0, 1.0,1.0, 1.0,-1.0};
GLfloat cursorpoint[16];
int gamemode = 1;

///Objects
SquareObj* *Sq;
int SqNum = 0;

/* convert pixel to openGL coordinates */
void convertPointData(float *arr, int start, int end) {
	for (int i = start; i < end; i += 2) {
		arr[i] = widthConvert(arr[i]);
	}
	for (int i = start+1; i < end; i += 2) {
		arr[i] = heightConvert(arr[i]);
	}
}

//Level init
void createLevel() {
	switch (gamemode) {
		case 2 : ///Level A
			Sq = new SquareObj*[30];
			Sq[20] = new SquareObj(0, 0, 150, 30);
			
			for (int i = 0; i < 10; i++) {
				if (i%2 == 0)
					Sq[i] = new SquareObj(-400, WINDOW_HEIGHT/9*(i), 150 - 10*(i), 30);
				else
					Sq[i] = new SquareObj(WINDOW_WIDTH+400, WINDOW_HEIGHT/9*(i), 50 + 10*(i-1), 30);
				Sq[i]->setSpeed(5);
				if (i%2 == 0)
					Sq[i]->setDirection(0);
				else
					Sq[i]->setDirection(180);
				Sq[i+10] = new SquareObj(WINDOW_WIDTH/9*(i), -100, 50, 30);
				Sq[i+10]->setSpeed(3);
				Sq[i+10]->setDirection(90);
			}
			int x = randomDouble(1.5, 2.7);
			for (int i = 0; i < 9; i++) {
				Sq[i+21] = new SquareObj(WINDOW_WIDTH/9*(i+0.5), -100, 50, 30, 16);
				Sq[i+21]->setSpeed(x);
				Sq[i+21]->setDirection(270);
			}
			SqNum = 30;
			break;
	}
	worldn = 1;
	worldtime[0].resetTime();
}

//Fungsi resumer
void unpause() {
	disabled = false;
	timeeffect.continueTime();
	for (int i = 0; i < worldn; i++)
		worldtime[i].continueTime();
	switch (gamemode) {
		case 2:
			for (int i = 0; i < SqNum; i++)
				Sq[i]->setTime(worldtime[0]);
			break;
	}
}

//Fungsi show timer
void drawTimer() {
	glColor4f(0.7,0.7,0.7,1.0);
	linesize = 2;
	timemark[0] = 0;
	timemark[1] = timemark[0];
	convertStringToLetterData(timeeffect.toString(), WINDOW_WIDTH - getStringWidth(timeeffect.toString(), linesize), 10, linesize, timetext, timemark[1], false);
	convertPointData(timetext, 0, timemark[1]);
	glLineWidth(linesize);
	glVertexPointer (2, GL_FLOAT, 0, timetext);
	glDrawArrays(GL_LINES, 0, timemark[1]/2);
}

//Game over
void gameOver() {
	string dummy;
	timeeffect.markTime();
	double timescore = timeeffect.getElapsed();
	double data;
	ifstream RecordData;
	ofstream Record;
	RecordData.open("highscore.txt");
	RecordData >> dummy >> dummy >> dummy >> dummy;
	RecordData >> data;
	if (timescore > data) {
		RecordData.close();
		Record.open("highscore.txt");
		Record << "World: ";
		switch (gamemode) {
			case 2 :
				Record << "Level_A";
				break;
			default:
				Record << "Zone";
		}
		Record << endl;
		Record << "Survival time: " << timescore << endl;
		Record.close();
	}
	Record.open("record.txt", ios::out | ios::app);
	Record << "World: ";
	switch (gamemode) {
		case 2 :
			Record << "Level_A";
			break;
		default:
			Record << "Zone";
	}
	Record << endl;
	Record << "Survival time: " << timescore << endl << endl;
	Record.close();
	gameover = true;
	
	linesize = 4;
	gameovermark[2] = gameovermark[1];
	timeeffect.continueTime();
	string str = "Time: " + timeeffect.toString();
	convertStringToLetterData(str, WINDOW_WIDTH/2 - getStringWidth(str, linesize)/2, WINDOW_HEIGHT*3/4, linesize, gameovertext, gameovermark[2], true);
	convertPointData(gameovertext, gameovermark[1], gameovermark[2]);
	delaytime.resetTime();
}

//Fungsi clear level
void clearLevel() {
	for (int i = 0; i < SqNum; i++)
		delete Sq[i];
	delete Sq;
	glColor4f(1.0,1.0,1.0,1.0);
	glVertexPointer (2, GL_FLOAT, 0, borders);
	glDrawArrays(GL_QUADS, 0, 4);
}

//Switch levels
void switchLevel(int gmode) {
	clearLevel();
	gamemode = gmode;
	createLevel();
}


/* Subprogram berhubungan dengan penggunaan OpenGL (dan GLFW) */
void errCallback(int error, const char* desc) {
	cerr << "Error: " << desc << endl;
}

void keyCallback(GLFWwindow* window, int key, int scanc, int act, int mods) {
	if (act == GLFW_PRESS) {
		switch (gamemode) {
			case 1 :
				switch(key) {
					case GLFW_KEY_S :
						gamemode = 2;
						createLevel();
						timeeffect.resetTime();
						break;
					case GLFW_KEY_ESCAPE :
						glfwSetWindowShouldClose(window, GLFW_TRUE);
						break;
				}
				break;
			case 2 :
				if (key == GLFW_KEY_P) {
					if (!disabled && !gameover) {
						timeeffect.markTime();
						for (int i = 0; i < worldn; i++)
							worldtime[i].markTime();
						disabled = true;
					} else {
						unpause();
					}
				}
				break;
			default: //case -1
				switch (key) {
					case GLFW_KEY_ESCAPE :
						glfwSetWindowShouldClose(window, GLFW_TRUE);
						break;
					default :
						if (delaytime.getElapsed() > 1) {
							gamemode = 1;
						}
				}
		}
	}
}

void enterCallback(GLFWwindow* window, int entered) {
	if (!entered && !disabled) {
		disabled = true;
		timeeffect.markTime();
		for (int i = 0; i < worldn; i++)
			worldtime[i].markTime();
	}
}

void drawCursor() {
	///Draw cursor
	cursorpoint[0] = widthConvert(xpos-CURSOR_WIDTH);
	cursorpoint[1] = heightConvert(ypos-CURSOR_HEIGHT);
	cursorpoint[2] = widthConvert(xpos);
	cursorpoint[3] = heightConvert(ypos-CURSOR_HEIGHT*sqrtTwo);
	cursorpoint[4] = widthConvert(xpos+CURSOR_WIDTH);
	cursorpoint[5] = heightConvert(ypos-CURSOR_HEIGHT);
	cursorpoint[6] = widthConvert(xpos+CURSOR_WIDTH*sqrtTwo);
	cursorpoint[7] = heightConvert(ypos);
	cursorpoint[8] = widthConvert(xpos+CURSOR_WIDTH);
	cursorpoint[9] = heightConvert(ypos+CURSOR_HEIGHT);
	cursorpoint[10] = widthConvert(xpos);
	cursorpoint[11] = heightConvert(ypos+CURSOR_HEIGHT*sqrtTwo);
	cursorpoint[12] = widthConvert(xpos-CURSOR_WIDTH);
	cursorpoint[13] = heightConvert(ypos+CURSOR_HEIGHT);
	cursorpoint[14] = widthConvert(xpos-CURSOR_WIDTH*sqrtTwo);
	cursorpoint[15] = heightConvert(ypos);
	glColor3f(1.0,0.0,0.0);
	glVertexPointer (2, GL_FLOAT, 0, cursorpoint);
	glDrawArrays(GL_POLYGON, 0, 8);
}

int main() {
	
	//Inisialisasi GLFW
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	
	//Enable Switch Task
	glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	
	//Get Monitor
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	
	//Set parameters
	WINDOW_HEIGHT = mode->height;
	WINDOW_WIDTH = mode->width;
	Dimensions(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	//Create window
	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TestDriver", glfwGetPrimaryMonitor(), NULL);
	
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	//Set context window yang ingin di-apakan
	glfwMakeContextCurrent(window);
	
	//Set callback untuk input keyboard
	glfwSetKeyCallback(window, keyCallback);
	
	//Set enter/leave callback
	glfwSetCursorEnterCallback(window, enterCallback);
	
	//Hide cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	
	//interval per swap buffer
	glfwSwapInterval(1);
	
	//Enable stuff
	glEnableClientState (GL_VERTEX_ARRAY);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Text initialize
	linesize = 7;
	gameovermark[0] = 0;
	gameovermark[1] = gameovermark[0];
	convertStringToLetterData(gameover1, WINDOW_WIDTH/2 - getStringWidth(gameover1, linesize)/2, WINDOW_HEIGHT/2-8, linesize, gameovertext, gameovermark[1], false);
	convertPointData(gameovertext, 0, gameovermark[1]);
	
	pausemark[0] = 0;
	pausemark[1] = pausemark[0];
	convertStringToLetterData(pause1, WINDOW_WIDTH/2 - getStringWidth(pause1, linesize)/2, WINDOW_HEIGHT/3, linesize, pausetext, pausemark[1], false);
	linesize = 5;
	pausemark[2] = pausemark[1];
	convertStringToLetterData(pause2, WINDOW_WIDTH/2 - getStringWidth(pause2, linesize)/2, WINDOW_HEIGHT*2/3, linesize, pausetext, pausemark[2], true);
	convertPointData(pausetext, 0, pausemark[2]);
	
	linesize = 7;
	mainmenumark[0] = 0;
	mainmenumark[1] = mainmenumark[0];
	convertStringToLetterData(mainmenu1, WINDOW_WIDTH/2 - getStringWidth(mainmenu1, linesize)/2, WINDOW_HEIGHT/3, linesize, mainmenutext, mainmenumark[1], false);
	linesize = 3;
	mainmenumark[2] = mainmenumark[1];
	convertStringToLetterData(mainmenu2, WINDOW_WIDTH/2 - getStringWidth(mainmenu2, linesize)/2, WINDOW_HEIGHT*2/3, linesize, mainmenutext, mainmenumark[2], true);
	mainmenumark[3] = mainmenumark[2];
	convertStringToLetterData(mainmenu3, WINDOW_WIDTH/2 - getStringWidth(mainmenu3, linesize)/2, WINDOW_HEIGHT*3/4, linesize, mainmenutext, mainmenumark[3], true);
	convertPointData(mainmenutext, 0, mainmenumark[3]);
	
	int iter;
	gamemode = 1;
	xpos = WINDOW_WIDTH/2;
	ypos = WINDOW_HEIGHT/2;
	
	while (!glfwWindowShouldClose(window)) {
		
		//Membersihkan buffer
		if (!gameover || gamemode == -1)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Menghapus segala transformasi
		glLoadIdentity();
		
		//Proses
		///Draw borders
		glLineWidth(2);
		glColor4f(1.0,1.0,1.0,1.0);
		glVertexPointer (2, GL_FLOAT, 0, borders);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		
		glfwGetCursorPos(window, &newxpos, &newypos);
		if ((newypos - ypos) + (newxpos - xpos) < 30) {
			xpos = newxpos;
			ypos = newypos;
		} else {
			xpos = newxpos - (newxpos - xpos)/2;
			ypos = newypos - (newypos - ypos)/2;
		}
		
		switch (gamemode) {
			case 1: 
				glVertexPointer (2, GL_FLOAT, 0, mainmenutext);
				glLineWidth(7);
				glDrawArrays(GL_LINES, 0, mainmenumark[1]/2);
				glLineWidth(3);
				glDrawArrays(GL_LINES, mainmenumark[1]/2, (mainmenumark[3]-mainmenumark[1])/2);
				drawCursor();
				break;
			case 2: ///Level A
				if (!gameover && worldtime[0].getElapsed() > 30) {
					switchLevel(2);
				} else if (!gameover) {
					if (disabled) { //Pause draw
						glVertexPointer (2, GL_FLOAT, 0, pausetext);
						glLineWidth(7);
						glDrawArrays(GL_LINES, 0, pausemark[2]/2);
						glLineWidth(5);
						glDrawArrays(GL_LINES, pausemark[1]/2, (pausemark[2]-pausemark[1])/2);
					} else {
						for (int i = 0; i < 10; i++) {
							Sq[i]->setAngle(worldtime[0].getElapsed()*36);
							Sq[i+10]->setAngle(-worldtime[0].getElapsed()*36);
						}
						for (int i = 0; i < 9; i++) {
							Sq[i+21]->setAngle(-worldtime[0].getElapsed()*72);
						}
						Sq[20]->setAngle(worldtime[0].getElapsed()*108);
						
						for (int i = 0; i < 10; i++) {
							Sq[i]->move();
							if (i%2 == 0) {
								if (Sq[i]->getX() > WINDOW_WIDTH+Sq[i]->getRadius()*2)
									Sq[i]->setX(-Sq[i]->getRadius()*2);
							} else {
								if (Sq[i]->getX() < -Sq[i]->getRadius()*2)
									Sq[i]->setX(WINDOW_WIDTH+Sq[i]->getRadius()*2);
							}
							Sq[i+10]->move();
							if (Sq[i+10]->getY() < -Sq[i+10]->getRadius()*2)
								Sq[i+10]->setY(WINDOW_HEIGHT+Sq[i+10]->getRadius()*2);
						}
						for (int i = 0; i < 9; i++) {
							Sq[i+21]->move();
							if (Sq[i+21]->getY() > WINDOW_HEIGHT+Sq[i+21]->getRadius()*2)
								Sq[i+21]->setY(-Sq[i+21]->getRadius()*2);
						}
						Sq[20]->setSpeed(sqrt(Sq[20]->distanceSquaredTo(Point(xpos, ypos)))/100+2);
						Sq[20]->setDirection(-Sq[20]->angleTo(Point(xpos, ypos))); //Karena y terbalik menurut terminal
						Sq[20]->move();
						for (int i = 0; i < SqNum; i++) {
							Sq[i]->redraw();
							glVertexPointer (2, GL_FLOAT, 0, Sq[i]->getPointData());
							if (Sq[i]->isMaterialised())
								glColor4f(1.0,1.0,1.0,1.0);
							else
								glColor4f(1.0,1.0,1.0,0.4);
							glDrawArrays(GL_QUADS, 0, 4);
						}
						if ((worldtime[0].getElapsed() > 15.95) && (worldtime[0].getElapsed() < 16.0)) {
							glColor4f(1.0,1.0,1.0,1.0);
							glVertexPointer (2, GL_FLOAT, 0, borders);
							glDrawArrays(GL_QUADS, 0, 4);
						}
					}
					drawCursor();
					if (!disabled) {
						drawTimer();
						
						iter = 0; 
						while ((iter < SqNum) && (!gameover)) {
							if (Sq[iter]->isMaterialised() && Sq[iter]->isIn(Point(xpos, ypos))) {
								gameOver();
							}
							iter++;
						}
					}
				}
				break;
			default: //-1
				if (delaytime.getElapsed() > 0.5) { 
					glLineWidth(7);
					glVertexPointer (2, GL_FLOAT, 0, gameovertext);
					glDrawArrays(GL_LINES, 0, gameovermark[1]/2);
					glLineWidth(4);
					glDrawArrays(GL_LINES, gameovermark[1]/2, (gameovermark[2]-gameovermark[1])/2);
				}
		}
		
		//Check gameover
		 if (gameover) { //gameover
			if (delaytime.getElapsed() > 2) {
				gamemode = -1;
				delaytime.resetTime();
				clearLevel();
				gameover = false;
			}
		}
		
		//Memindahkan buffer ke tempat yang akan digunakan
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	//Destroy window
	glfwDestroyWindow(window);
	
	//Terminasi GLFW
	glfwTerminate();

	return 0;
}
