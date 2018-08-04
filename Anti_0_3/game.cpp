///Compiling shortcut (Linux): g++ -o message message.cpp -lGL -lGLU -lglfw ///
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <iostream>
#include "randomer.hpp"
using namespace std;

#include <fstream>
#include "Lists.hpp"
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
Time worldtime[10];
int worldn = 0;
Time delaytime;
bool disabled = false;
bool gameover = false;
bool checkp = false;
int checkl = 0;
bool loaded = false;

float pausetext[1000];
int pausemark[3];
const string pause1 = "PAUSED";
const string pause2 = "Press P to resume";

float gameovertext[1200];
int gameovermark[3];
const string gameover1 = "GAME OVER";

float mainmenutext[3000];
int mainmenumark[6];
const string mainmenu1 = "A N T I";
const string mainmenu2 = "Press S to start NEW game";
const string mainmenu3 = "Press L to load checkpoint";
const string mainmenu4 = "Press A to start arcade";
const string mainmenu5 = "Press H for help. Press Esc to quit";
bool storymode = false;
int rounds = 0;

float timetext[1500];
int timemark[2];

float wintext[1000];
int winmark[3];
const string wintext1 = "END OF GAME";
const string wintext2 = "Thanks for playing";

float helptext[3000];
int helpmark[6];
const string help1 = "Dodge all obstacles.";
const string help2 = "Red cursor: Move with mouse";
const string help3 = "Press P to pause. Only works on some levels";
const string help4 = "";
const string help5 = "";

float title_LevelA[300];
int title_LevelA_mark[2];
const string title_LevelA_str = "Level A";

float title_BulletH[300];
int title_BulletH_mark[2];
const string title_BulletH_str = "Bullet Hell";

GLfloat borders[8] = {-1.0,-1.0, -1.0,1.0, 1.0,1.0, 1.0,-1.0};
GLfloat cursorpoint[16];
int gamemode = 0;

int randommode = 0;

///Objects
List<SquareObj> Sq;

/* convert pixel to openGL coordinates */
void convertPointData(float *arr, int start, int end) {
	for (int i = start; i < end; i += 2) {
		arr[i] = widthConvert(arr[i]);
	}
	for (int i = start+1; i < end; i += 2) {
		arr[i] = heightConvert(arr[i]);
	}
}

#define LEVEL_A_TIME 30
//Level init
void createLevel() {
	switch (gamemode) {
		case 1: { ///Zone
			worldn = 10;
			} break;
		case 2 : { ///Level A
			for (int i = 0; i < 10; i++) {
				if (i%2 == 0)
					Sq.add(SquareObj(-400, WINDOW_HEIGHT/9*(i), 150 - 10*(i), LEVEL_A_TIME+1));
				else
					Sq.add(SquareObj(WINDOW_WIDTH+400, WINDOW_HEIGHT/9*(i), 50 + 10*(i-1), LEVEL_A_TIME+1));
			}
			Sq.setBegin();
			for (int i = 0; i < 10; i++) {
				Sq.getIValue().setSpeed(7);
				if (i%2 == 0)
					Sq.getIValue().setDirection(0);
				else
					Sq.getIValue().setDirection(180);
				Sq.next();
			}
			float x = randomFloat(2,3.6);
			for (int i = 0; i < 10; i++) {
				Sq.add(SquareObj(WINDOW_WIDTH/9*(i), -100, 50, LEVEL_A_TIME+1));
			}
			Sq.setBeginAt(Sq.size()-10);
			for (int i = 0; i < 10; i++) {
				Sq.getIValue().setSpeed(x);
				Sq.getIValue().setDirection(90);
				Sq.next();
			}
			
			Sq.add(SquareObj(-150, -150, 150, 30));
			
			for (int i = 0; i < 9; i++) {
				Sq.add(SquareObj(WINDOW_WIDTH/9*(i+0.5), -100, 50, LEVEL_A_TIME+1, 16));
			}
			Sq.setBeginAt(Sq.size()-9);
			for (int i = 0; i < 9; i++) {
				Sq.getIValue().setSpeed(2);
				Sq.getIValue().setDirection(270);
				Sq.next();
			}
			worldn = 2;
			} break;
		case 3: { ///BulletH1
			worldn = 2;
			} break;
	}
	for (int i = 0; i < worldn; i++)
		worldtime[i].resetTime();
}

#define SQUARE_RPROJECTILE 1
#define SQUARE_RPROJECTILED 2
#define SQUARE_RPROJECTILET 3
#define SQUARE_STATICSPAWN 4
#define SQUARE_RRPROJECTILE 5
#define SQUARE_RRPROJECTILED 6
//Create random projectiles
void addObjects(int type) {
	switch (type) {
		case SQUARE_RPROJECTILE : {
			int x = randomInt(1,4);
			switch (x) {
				case 1: Sq.add(SquareObj(WINDOW_WIDTH/2, -100, 80, 10));
					break;
				case 2: Sq.add(SquareObj(WINDOW_WIDTH/2, WINDOW_HEIGHT+100, 80, 10));
					break;
				case 3: Sq.add(SquareObj(-100, WINDOW_HEIGHT/2, 80, 10));
					break;
				case 4: Sq.add(SquareObj(WINDOW_WIDTH+100, WINDOW_HEIGHT/2, 80, 10));
					break;
			}
			Sq[Sq.size()-1].setSpeed(4);
			Sq[Sq.size()-1].setAngle(-Sq[Sq.size()-1].angleTo(Point(xpos, ypos)));
			Sq[Sq.size()-1].setDirection(-Sq[Sq.size()-1].angleTo(Point(xpos, ypos)));
			Sq[Sq.size()-1].getColorData()[2] = (float)randomInt(0,20)/20;
			} break;
		case SQUARE_RPROJECTILED : {
			int x = randomInt(1,2);
			switch (x) {
				case 1: Sq.add(SquareObj(WINDOW_WIDTH/2, -100, 70, 10));
					Sq.add(SquareObj(WINDOW_WIDTH/2, WINDOW_HEIGHT+100, 70, 10));
					break;
				case 2: Sq.add(SquareObj(-100, WINDOW_HEIGHT/2, 70, 10));
					Sq.add(SquareObj(WINDOW_WIDTH+100, WINDOW_HEIGHT/2, 70, 10));
					break;
			}
			Sq.setBeginAt(Sq.size()-2);
			for (int i = 0; i < 2; i++) {
				Sq.getIValue().setSpeed(5);
				Sq.getIValue().setAngle(-Sq.getIValue().angleTo(Point(xpos, ypos)));
				Sq.getIValue().setDirection(-Sq.getIValue().angleTo(Point(xpos, ypos)));
				Sq.getIValue().getColorData()[1] = (float)randomInt(0,20)/20;
				Sq.next();
			}
			} break;
		case SQUARE_RRPROJECTILE : {
			int x = randomInt(1,4);
			double y = randomFloat(-30,30);
			switch (x) {
				case 1: Sq.add(SquareObj(WINDOW_WIDTH/2, -100, 80, 10));
					break;
				case 2: Sq.add(SquareObj(WINDOW_WIDTH/2, WINDOW_HEIGHT+100, 80, 10));
					break;
				case 3: Sq.add(SquareObj(-100, WINDOW_HEIGHT/2, 80, 10));
					break;
				case 4: Sq.add(SquareObj(WINDOW_WIDTH+100, WINDOW_HEIGHT/2, 80, 10));
					break;
			}
			Sq[Sq.size()-1].setSpeed(4.5);
			Sq[Sq.size()-1].setAngle(-Sq[Sq.size()-1].angleTo(Point(xpos, ypos))+y);
			Sq[Sq.size()-1].setDirection(-Sq[Sq.size()-1].angleTo(Point(xpos, ypos))+y);
			Sq[Sq.size()-1].getColorData()[2] = (float)randomInt(0,20)/20;
			} break;
		case SQUARE_RRPROJECTILED : {
			int x = randomInt(1,2);
			double y = randomFloat(-30,30);
			switch (x) {
				case 1: Sq.add(SquareObj(WINDOW_WIDTH/2, -100, 70, 10));
					Sq.add(SquareObj(WINDOW_WIDTH/2, WINDOW_HEIGHT+100, 70, 10));
					break;
				case 2: Sq.add(SquareObj(-100, WINDOW_HEIGHT/2, 70, 10));
					Sq.add(SquareObj(WINDOW_WIDTH+100, WINDOW_HEIGHT/2, 70, 10));
					break;
			}
			Sq.setBeginAt(Sq.size()-2);
			for (int i = 0; i < 2; i++) {
				Sq.getIValue().setSpeed(5);
				Sq.getIValue().setAngle(-Sq.getIValue().angleTo(Point(xpos, ypos))+y);
				Sq.getIValue().setDirection(-Sq.getIValue().angleTo(Point(xpos, ypos))+y);
				Sq.getIValue().getColorData()[1] = (float)randomInt(0,20)/20;
				Sq.next();
			}
			} break;
		case SQUARE_RPROJECTILET : {
			Sq.add(SquareObj(WINDOW_WIDTH/2, -100, 60, 10));
			Sq.add(SquareObj(WINDOW_WIDTH/2, WINDOW_HEIGHT+100, 60, 10));
			Sq.add(SquareObj(-100, WINDOW_HEIGHT/2, 60, 10));
			Sq.add(SquareObj(WINDOW_WIDTH+100, WINDOW_HEIGHT/2, 60, 10));
			Sq.setBeginAt(Sq.size()-4);
			for (int i = 0; i < 4; i++) {
				Sq.getIValue().setSpeed(5.5);
				Sq.getIValue().setAngle(-Sq.getIValue().angleTo(Point(xpos, ypos)));
				Sq.getIValue().setDirection(-Sq.getIValue().angleTo(Point(xpos, ypos)));
				Sq.getIValue().getColorData()[1] = (float)randomInt(0,20)/20;
				Sq.getIValue().getColorData()[2] = (float)randomInt(0,20)/20;
				Sq.next();
			}
			} break;
		case SQUARE_STATICSPAWN : {
			float x = randomFloat(0.8,1.6);
			Sq.add(SquareObj(xpos + randomDouble(-300, 300), ypos + randomDouble(-300, 300), randomInt(200, 450), x+1, x));
			} break;
	}
}

//Fungsi pause
bool paused() {
	if (disabled) { //Pause draw
		glVertexPointer (2, GL_FLOAT, 0, pausetext);
		glLineWidth(7);
		glDrawArrays(GL_LINES, 0, pausemark[2]/2);
		glLineWidth(5);
		glDrawArrays(GL_LINES, pausemark[1]/2, (pausemark[2]-pausemark[1])/2);
		return true;
	} else
		return false;
}

//Fungsi resumer
void unpause() {
	disabled = false;
	timeeffect.continueTime();
	for (int i = 0; i < worldn; i++)
		worldtime[i].continueTime();
	Sq.setBegin();
	for (int i = 0; i < Sq.size(); i++) {
		Sq.getIValue().continueTime();
		Sq.next();
	}
}

//Fungsi show timer
void drawTimer() {
	if (!storymode) {
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
}

void drawTitle() {
	glColor4f(0.7,0.7,0.7,1.0);
	glLineWidth(2);
	switch (gamemode) {
		case 2:
			glVertexPointer (2, GL_FLOAT, 0, title_LevelA);
			glDrawArrays(GL_LINES, 0, title_LevelA_mark[1]/2);
			break;
		case 3:
			glVertexPointer (2, GL_FLOAT, 0, title_BulletH);
			glDrawArrays(GL_LINES, 0, title_BulletH_mark[1]/2);
			break;
	}
}

//Game over
void gameOver() {
	if (!storymode) {
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
				case 3 :
					Record << "Bullet_Hell";
					break;
				default: //1
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
			case 3 :
				Record << "Bullet_Hell";
				break;
			default: //1
				Record << "Zone";
		}
		Record << endl;
		Record << "Survival time: " << timescore << endl << endl;
		Record.close();
		
		linesize = 4;
		gameovermark[2] = gameovermark[1];
		timeeffect.continueTime();
		string str = "Time: " + timeeffect.toString();
		convertStringToLetterData(str, WINDOW_WIDTH/2 - getStringWidth(str, linesize)/2, WINDOW_HEIGHT*3/4, linesize, gameovertext, gameovermark[2], true);
		convertPointData(gameovertext, gameovermark[1], gameovermark[2]);
	} else {
		if (!loaded) {
			ofstream saveFile;
			saveFile.open("savedata");
			saveFile << gamemode << endl;
			checkl = gamemode;
			saveFile.close();
		}
	}
	rounds = 0;
	gameover = true;
	delaytime.resetTime();
}

//Fungsi clear level
void clearLevel() {
	Sq.removeAll();
	for (int i = 0; i < worldn; i++)
		worldtime[i].resetTime();
	worldn = 0;
	randommode = 0; 
	glColor4f(1.0,1.0,1.0,1.0);
	glVertexPointer (2, GL_FLOAT, 0, borders);
	glDrawArrays(GL_QUADS, 0, 4);
}

//Switch levels
void switchLevel(int gmode) {
	if (loaded)
		loaded = false;
	clearLevel();
	gamemode = gmode;
	createLevel();
	if (gmode == 999) {
		ofstream saveFile;
		saveFile.open("savedata");
		saveFile << gamemode << endl;
		saveFile.close();
		checkl = gamemode;
		delaytime.resetTime();
	} if (gmode == 1) {
		checkp = false;
		rounds++;
	}
}


/* Subprogram berhubungan dengan penggunaan OpenGL (dan GLFW) */
void errCallback(int error, const char* desc) {
	cerr << "Error: " << desc << endl;
}

void keyCallback(GLFWwindow* window, int key, int scanc, int act, int mods) {
	if (act == GLFW_PRESS) {
		switch (gamemode) {
			case 0 :
				switch(key) {
					case GLFW_KEY_S :
						storymode = true;
						switchLevel(3);
						createLevel();
						break;
					case GLFW_KEY_L :
						storymode = true;
						switch (checkl) {
							case 999: switchLevel(2);
								break;
							default: switchLevel(3);
						}
						loaded = true;
						createLevel();
						break;
					case GLFW_KEY_A :
						storymode = false;
						switchLevel(1);
						createLevel();
						timeeffect.resetTime();
						break;
					case GLFW_KEY_H :
						switchLevel(998);
						break;
					case GLFW_KEY_ESCAPE :
						glfwSetWindowShouldClose(window, GLFW_TRUE);
						break;
				}
				break;
			case 1 :
				if (key == GLFW_KEY_P) {
					if (!disabled && !gameover) {
						timeeffect.markTime();
						for (int i = 0; i < worldn; i++)
							worldtime[i].markTime();
						Sq.setBegin();
						for (int i = 0; i < Sq.size(); i++) {
							Sq.getIValue().markTime();
							Sq.next();
						}
						disabled = true;
					} else {
						unpause();
					}
				}
				break;
			case 2:
			case 3:
				break;
			default: //case -1 or 999 or 998
				switch (key) {
					case GLFW_KEY_ESCAPE :
						glfwSetWindowShouldClose(window, GLFW_TRUE);
						break;
					default :
						if (delaytime.getElapsed() > 1) {
							switchLevel(0);
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
		Sq.setBegin();
		for (int i = 0; i < Sq.size(); i++)	{
			Sq.getIValue().markTime();
			Sq.next();
		}
	}
}

void drawCursor() {
	switch (gamemode) {
		default: glColor3f(1.0,0.0,0.0);
	}
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
	
	glVertexPointer (2, GL_FLOAT, 0, cursorpoint);
	glDrawArrays(GL_POLYGON, 0, 8);
}

void drawObjects() {
	int i = 0;
	Sq.setBegin();
	while (i < Sq.size()) {
		if (Sq.getIValue().isDead()) {
			Sq.removeAt(i);
		} else {
			Sq.getIValue().redraw();
			glVertexPointer (2, GL_FLOAT, 0, Sq.getIValue().getPointData());
			if (Sq.getIValue().isMaterialised())
				glColor4f(Sq.getIValue().getColorData()[0],Sq.getIValue().getColorData()[1],Sq.getIValue().getColorData()[2],1.0);
			else
				glColor4f(Sq.getIValue().getColorData()[0],Sq.getIValue().getColorData()[1],Sq.getIValue().getColorData()[2],0.4);
			glDrawArrays(GL_QUADS, 0, 4);
			Sq.next();
			i++;
		}
	}
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
	
	winmark[0] = 0;
	winmark[1] = winmark[0];
	convertStringToLetterData(wintext1, WINDOW_WIDTH/2 - getStringWidth(wintext1, linesize)/2, WINDOW_HEIGHT/4, linesize, wintext, winmark[1], false);
	winmark[2] = winmark[1];
	convertStringToLetterData(wintext2, WINDOW_WIDTH/2 - getStringWidth(wintext2, linesize)/2, WINDOW_HEIGHT*2/3, linesize, wintext, winmark[2], false);
	convertPointData(wintext, 0, winmark[2]);
	
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
	convertStringToLetterData(mainmenu1, WINDOW_WIDTH/2 - getStringWidth(mainmenu1, linesize)/2, WINDOW_HEIGHT/4, linesize, mainmenutext, mainmenumark[1], false);
	linesize = 3;
	mainmenumark[2] = mainmenumark[1];
	convertStringToLetterData(mainmenu2, WINDOW_WIDTH/2 - getStringWidth(mainmenu2, linesize)/2, WINDOW_HEIGHT*6/10, linesize, mainmenutext, mainmenumark[2], true);
	mainmenumark[3] = mainmenumark[2];
	convertStringToLetterData(mainmenu3, WINDOW_WIDTH/2 - getStringWidth(mainmenu3, linesize)/2, WINDOW_HEIGHT*7/10, linesize, mainmenutext, mainmenumark[3], true);
	mainmenumark[4] = mainmenumark[3];
	convertStringToLetterData(mainmenu4, WINDOW_WIDTH/2 - getStringWidth(mainmenu4, linesize)/2, WINDOW_HEIGHT*8/10, linesize, mainmenutext, mainmenumark[4], true);
	mainmenumark[5] = mainmenumark[4];
	convertStringToLetterData(mainmenu5, WINDOW_WIDTH/2 - getStringWidth(mainmenu5, linesize)/2, WINDOW_HEIGHT*9/10, linesize, mainmenutext, mainmenumark[5], true);
	convertPointData(mainmenutext, 0, mainmenumark[5]);
	
	linesize = 2;
	helpmark[0] = 0;
	helpmark[1] = helpmark[0];
	convertStringToLetterData(help1, 30, WINDOW_HEIGHT/10, linesize, helptext, helpmark[1], true);
	helpmark[2] = helpmark[1];
	convertStringToLetterData(help2, 30, WINDOW_HEIGHT*2/10, linesize, helptext, helpmark[2], true);
	helpmark[3] = helpmark[2];
	convertStringToLetterData(help3, 30, WINDOW_HEIGHT*3/10, linesize, helptext, helpmark[3], true);
	helpmark[4] = helpmark[3];
	convertStringToLetterData(help4, 30, WINDOW_HEIGHT*4/10, linesize, helptext, helpmark[4], true);
	helpmark[5] = helpmark[4];
	convertStringToLetterData(help5, 30, WINDOW_HEIGHT*5/10, linesize, helptext, helpmark[5], true);
	convertPointData(helptext, 0, helpmark[5]);
	
	linesize = 2;
	title_LevelA_mark[0] = 0;
	title_LevelA_mark[1] = title_LevelA_mark[0];
	convertStringToLetterData(title_LevelA_str, 10, 10, linesize, title_LevelA, title_LevelA_mark[1], true);
	convertPointData(title_LevelA, 0, title_LevelA_mark[1]);
	
	title_BulletH_mark[0] = 0;
	title_BulletH_mark[1] = title_BulletH_mark[0];
	convertStringToLetterData(title_BulletH_str, 10, 10, linesize, title_BulletH, title_BulletH_mark[1], true);
	convertPointData(title_BulletH, 0, title_BulletH_mark[1]);
	
	int iter;
	gamemode = 0;
	xpos = WINDOW_WIDTH/2;
	ypos = WINDOW_HEIGHT/2;
	
	ifstream loadFile;
	loadFile.open("savedata");
	loadFile >> checkl;
	loadFile.close();
	
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
		
		///Proses mouse
		glfwGetCursorPos(window, &newxpos, &newypos);
		if (abs(newypos - ypos) + abs(newxpos - xpos) < 5) {
			xpos = newxpos;
			ypos = newypos;
		}else if (abs(newypos - ypos) + abs(newxpos - xpos) < 30) {
			xpos = newxpos - (newxpos - xpos)*10/11;
			ypos = newypos - (newypos - ypos)*10/11;
		} else if (abs(newypos - ypos) + abs(newxpos - xpos) < 50) {
			xpos = newxpos - (newxpos - xpos)*2/3;
			ypos = newypos - (newypos - ypos)*2/3;
		} else if (abs(newypos - ypos) + abs(newxpos - xpos) < 120) {
			xpos = newxpos - (newxpos - xpos)*4/5;
			ypos = newypos - (newypos - ypos)*4/5;
		} else {
			xpos = xpos + 60*cos(atan2((newypos - ypos),(newxpos - xpos)));
			ypos = ypos + 60*sin(atan2((newypos - ypos),(newxpos - xpos)));
		}
		
		switch (gamemode) {
			case 0: 
				glVertexPointer (2, GL_FLOAT, 0, mainmenutext);
				glLineWidth(7);
				glDrawArrays(GL_LINES, 0, mainmenumark[1]/2);
				glLineWidth(3);
				glDrawArrays(GL_LINES, mainmenumark[1]/2, (mainmenumark[5]-mainmenumark[1])/2);
				drawCursor();
				break;
			case 1: { ///Zone
				if (!gameover && worldtime[0].getElapsed() > 20)
					switchLevel(randomInt(2,3));
				else if (!gameover) {
					if (worldtime[0].getElapsed() > 10 && !checkp) {
						randommode = randomInt(1,2);
						checkp = true;
					} else if (randommode == 0) {
						randommode = randomInt(1,2);
					}
					if (!paused()) {
						switch (randommode) {
							case 1: { ///Random 1
								if (rounds > 2) {
									if (checkp && worldtime[1].getElapsed() > 0.22) {
										addObjects(SQUARE_RRPROJECTILED);
										worldtime[1].resetTime();
									} else if (worldtime[1].getElapsed() > 0.32) {
										addObjects(SQUARE_RPROJECTILED);
										worldtime[1].resetTime();
									}
								} else {
									if (checkp && worldtime[1].getElapsed() > 0.18) {
										addObjects(SQUARE_RRPROJECTILE);
										worldtime[1].resetTime();
									} else if (worldtime[1].getElapsed() > 0.25) {
										addObjects(SQUARE_RPROJECTILE);
										worldtime[1].resetTime();
									}	
								}
								} break;
							case 2: { ///Random 2
								if (checkp && worldtime[2].getElapsed() > 0.1) {
									addObjects(SQUARE_STATICSPAWN);
									worldtime[2].resetTime();
								} else if (worldtime[2].getElapsed() > 0.2) {
									addObjects(SQUARE_STATICSPAWN);
									worldtime[2].resetTime();
								}
								Sq.setBegin();
								for (int i = 0; i < Sq.size(); i++) {
									if (!Sq.getIValue().isMaterialised())
										Sq.getIValue().setAngle(Sq.getIValue().getLifeTime().getElapsed()*100);
									Sq.next();
								}
								} break;
						}
						Sq.setBegin();
						for (int i = 0; i < Sq.size(); i++) {
							Sq.getIValue().move();
							Sq.next();
						}
						drawObjects();
					}	
				drawCursor();
				}
				} break;
			case 2: { ///Level A
				if (!gameover && worldtime[0].getElapsed() > LEVEL_A_TIME) {
					if (storymode) {
						switchLevel(999);
					} else {
						switchLevel(1);
					}
				} else if (!gameover) {
					if (!paused()) {
						Sq.setBegin();
						for (int i = 0; i < 10; i++) {
							Sq.getIValue().setAngle(worldtime[0].getElapsed()*36);
							Sq.next();
						}
						for (int i = 0; i < 10; i++) {
							Sq.getIValue().setAngle(-worldtime[0].getElapsed()*36);
							Sq.next();
						}
						Sq.getIValue().setAngle(worldtime[0].getElapsed()*108);
						Sq.next();
						for (int i = 0; i < 9; i++) {
							Sq.getIValue().setAngle(-worldtime[0].getElapsed()*72);
							Sq.next();
						}
						
						Sq.setBegin();
						for (int i = 0; i < 10; i++) {
							Sq.getIValue().move();
							if (i%2 == 0) {
								if (Sq.getIValue().getX() > WINDOW_WIDTH+Sq.getIValue().getRadius()*2)
									Sq.getIValue().setX(-Sq.getIValue().getRadius()*2);
							} else {
								if (Sq.getIValue().getX() < -Sq.getIValue().getRadius()*2)
									Sq.getIValue().setX(WINDOW_WIDTH+Sq.getIValue().getRadius()*2);
							}
							Sq.next();
						}
						for (int i = 0; i < 10; i++) {
							Sq.getIValue().move();
							if (Sq.getIValue().getY() < -Sq.getIValue().getRadius()*2)
								Sq.getIValue().setY(WINDOW_HEIGHT+Sq.getIValue().getRadius()*2);
							Sq.next();
						}
						Sq.getIValue().setSpeed(sqrt(Sq.getIValue().distanceSquaredTo(Point(xpos, ypos)))/100+2);
						Sq.getIValue().setDirection(-Sq.getIValue().angleTo(Point(xpos, ypos))); //Karena y terbalik menurut terminal
						Sq.getIValue().move();
						Sq.next();
						if (worldtime[0].getElapsed() > 16 && worldtime[1].getElapsed() > 16) {
							worldtime[1].resetTime();
							float a = randomFloat(1,5);
							for (int i = 0; i < 9; i++) {
								Sq.getIValue().setSpeed(a);
								Sq.next();
							}
						}
						Sq.setBeginAt(Sq.size()-9);
						for (int i = 0; i < 9; i++) {
							Sq.getIValue().move();
							if (Sq.getIValue().getY() > WINDOW_HEIGHT+Sq.getIValue().getRadius()*2)
								Sq.getIValue().setY(-Sq.getIValue().getRadius()*2);
							Sq.next();
						}
						drawObjects();
						if ((worldtime[0].getElapsed() > 15.98) && (worldtime[0].getElapsed() < 16.02)) {
							glColor4f(1.0,1.0,1.0,1.0);
							glVertexPointer (2, GL_FLOAT, 0, borders);
							glDrawArrays(GL_QUADS, 0, 4);
						}
					}
					drawCursor();
				}
				} break;
			case 3: {
				if (storymode && !gameover && worldtime[0].getElapsed() > 20) {
					switchLevel(2);
				} else if (!storymode && !gameover && worldtime[0].getElapsed() > 15) {
					switchLevel(1);
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() > 15 && worldtime[1].getElapsed() > 0.18) {
							addObjects(SQUARE_RPROJECTILET);
							worldtime[1].resetTime();
						} else if (worldtime[0].getElapsed() > 9 && worldtime[1].getElapsed() > 0.25) {
							addObjects(SQUARE_RPROJECTILET);
							worldtime[1].resetTime();
						} else if (worldtime[1].getElapsed() > 0.45) {
							addObjects(SQUARE_RPROJECTILET);
							worldtime[1].resetTime();
						}
						Sq.setBegin();
						for (int i = 0; i < Sq.size(); i++) {
							Sq.getIValue().move();
							Sq.next();
						}
						drawObjects();
					}	
				drawCursor();
				}
				} break;
			case 998: {
				glVertexPointer (2, GL_FLOAT, 0, helptext);
				glLineWidth(2);
				glDrawArrays(GL_LINES, 0, helpmark[5]/2);
				drawCursor();
				} break;
			case 999: {
				glLineWidth(7);
				glVertexPointer (2, GL_FLOAT, 0, wintext);
				glColor4f(1.0,1.0,1.0,delaytime.getElapsed());
				glDrawArrays(GL_LINES, 0, winmark[2]/2);
				} break;
			default: //-1
				if (delaytime.getElapsed() > 0.5) { 
					glLineWidth(7);
					glVertexPointer (2, GL_FLOAT, 0, gameovertext);
					glDrawArrays(GL_LINES, 0, gameovermark[1]/2);
					if (!storymode) {
						glLineWidth(4);
						glDrawArrays(GL_LINES, gameovermark[1]/2, (gameovermark[2]-gameovermark[1])/2);
					}
				}
		}
		
		///Draw title
		if (!disabled)
			drawTitle();
			
		///Draw timer
		if (!disabled && !gameover && (gamemode > 0) && (gamemode < 998)) {
			drawTimer();
		}
		//Check gameover
		iter = 0;
		Sq.setBegin();
		while ((!disabled) && (iter < Sq.size()) && (!gameover)) {
			if (Sq.getIValue().isMaterialised() && Sq.getIValue().isIn(Point(xpos, ypos))) {
				gameOver();
			}
			Sq.next();
			iter++;
		}
						
		if (gameover) { //gameover
			if (delaytime.getElapsed() > 2) {
				switchLevel(-1);
				gameover = false;
				delaytime.resetTime();
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
