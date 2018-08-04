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
#include "Spawner2D.hpp"
#include "SquareObj.hpp"
#include "QuadObj.hpp"

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
bool freeze = false;
bool gameover = false;
int checkl = 0;
bool loaded = false;
bool spacepressed = false;
#define SHOT_DELAY 0.1
#define SHOT_DAMAGE 4

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

float helptext[4000];
int helpmark[8];
const string help1 = "Dodge all obstacles.";
const string help2 = "Move with mouse.";
const string help3 = "Press P to pause.";
const string help4 = "Press and hold spacebar to shoot.";
const string help5 = "This game may or may not be completable.";
const string help6 = "One does not simply succeed on first try.";
const string help7 = "Do not panic. Unless you must.";

float title_LevelA[300];
int title_LevelA_mark[2];
const string title_LevelA_str = "Level A";

GLfloat borders[8] = {-1.0,-1.0, -1.0,1.0, 1.0,1.0, 1.0,-1.0};
GLfloat cursorpoint[16];
int gamemode = 0;

///Objects
List<SquareObj> Sq;
List<QuadObj> Shots;

List<Spawner2D> defSpw;
List<Spawner2D> Spw;

///Stages
#define ID_GAMEOVER -1
#define ID_MAINMENU 0
#define ID_HELP 998
#define ID_WIN 999

//Easy
#define ID_ZONE1 1
#define ID_BULLET1 3
#define ID_ZONE2 4
#define ID_ZONE3 5

//Medium
#define ID_ZONE1B 6
#define ID_LEVEL_A 2

//Hard

//Insane

List<int> changeID;
List<int> levelID;

/* convert pixel to openGL coordinates */
void convertPointData(float *arr, int start, int end) {
	for (int i = start; i < end; i += 2) {
		arr[i] = widthConvert(arr[i]);
	}
	for (int i = start+1; i < end; i += 2) {
		arr[i] = heightConvert(arr[i]);
	}
}

///spawn shots
#define NULL_SHOT 0
#define SQUARE_ANGLESHOT1 1
#define SQUARE_ANGLESHOT2 2
#define SQUARE_ANGLESHOT3 3

void Spawner2D::spawnObject() {
	if (spawntimer.getElapsed() > spawntime) {
		switch(spawntype) {
			case SQUARE_ANGLESHOT1 : {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 50, 7));
				Sq[Sq.size()-1].setDirection(spawner->getAngle());
				Sq[Sq.size()-1].setSpeed(6);
				Sq[Sq.size()-1].setAngle(spawner->getAngle());
				Sq[Sq.size()-1].getColorData()[2] = 0.0;
			} break;
			case SQUARE_ANGLESHOT2 : {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 70, 7));
				Sq[Sq.size()-1].setSpeed(4);
				Sq[Sq.size()-1].setAngle(spawner->getAngle());
				Sq[Sq.size()-1].setDirection(spawner->getAngle());
				Sq[Sq.size()-1].getColorData()[2] = (float)randomInt(0,20)/20;
			} break;
			case SQUARE_ANGLESHOT3 : {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 40, 6));
				Sq[Sq.size()-1].setSpeed(5.5);
				Sq[Sq.size()-1].setAngle(spawner->getAngle());
				Sq[Sq.size()-1].setDirection(spawner->getAngle());
				Sq[Sq.size()-1].getColorData()[1] = (float)randomInt(0,20)/20;
				Sq[Sq.size()-1].getColorData()[2] = (float)randomInt(0,20)/20;
			} break;
		}
		spawntimer.resetTime();
	}
}

#define LEVEL_A_TIME 30
//Level init
void createLevel() {
	switch (gamemode) {
		case ID_LEVEL_A : { ///Level A
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
		case ID_ZONE1: {
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -100, 1, 7), 0.26, 0, SQUARE_ANGLESHOT2));
			worldn = 2;
		} break;
		case ID_ZONE1B: {
			defSpw.add(Spawner2D(new SquareObj(-100, WINDOW_HEIGHT/2, 1, 7), 0.32, 0, SQUARE_ANGLESHOT2));
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH+100, WINDOW_HEIGHT/2, 1, 7), 0.32, 0, SQUARE_ANGLESHOT2));
			worldn = 2;
		} break;
		case ID_ZONE3: {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -100, 150, 999), 0.04, 100, SQUARE_ANGLESHOT1));
			Spw[0].getObject()->setSpeed(4);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.0;
			Spw[0].getObject()->getColorData()[2] = 0.0;
		} break;
		case ID_BULLET1: {
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -100, 1, 7), 0.6, 0, SQUARE_ANGLESHOT3));
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, WINDOW_HEIGHT+100, 1, 7), 0.6, 0, SQUARE_ANGLESHOT3));
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH+100, WINDOW_HEIGHT/2, 1, 7), 0.6, 0, SQUARE_ANGLESHOT3));
			defSpw.add(Spawner2D(new SquareObj(-100, WINDOW_HEIGHT/2, 1, 7), 0.6, 0, SQUARE_ANGLESHOT3));
			worldn = 1;
		} break;
			worldn = 1;
		default: {
			worldn = 1;
		} break;
	}
	for (int i = 0; i < worldn; i++)
		worldtime[i].resetTime();
}

//Fungsi pause
bool paused() {
	if (disabled) { //Pause draw
		if (!freeze) {
			timeeffect.markTime();
			for (int i = 0; i < worldn; i++)
				worldtime[i].markTime();
			Sq.setBegin();
			for (int i = 0; i < Sq.size(); i++) {
				Sq.getIValue().markTime();
				Sq.next();
			}
			Shots.setBegin();
			for (int i = 0; i < Shots.size(); i++) {
				Shots.getIValue().markTime();
				Shots.next();
			}
			defSpw.setBegin();
			for (int i = 0; i < defSpw.size(); i++) {
				defSpw.getIValue().getSpawnTimer().markTime();
				defSpw.getIValue().getObject()->markTime();
				defSpw.next();
			}
			Spw.setBegin();
			for (int i = 0; i < Spw.size(); i++) {
				Spw.getIValue().getSpawnTimer().markTime();
				Spw.getIValue().getObject()->markTime();
				Spw.next();
			}
			freeze = true;
		}
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
	freeze = false;
	timeeffect.continueTime();
	for (int i = 0; i < worldn; i++)
		worldtime[i].continueTime();
	Sq.setBegin();
	for (int i = 0; i < Sq.size(); i++) {
		Sq.getIValue().continueTime();
		Sq.next();
	}
	Shots.setBegin();
	for (int i = 0; i < Shots.size(); i++) {
		Shots.getIValue().continueTime();
		Shots.next();
	}
	defSpw.setBegin();
	for (int i = 0; i < defSpw.size(); i++) {
		defSpw.getIValue().getSpawnTimer().continueTime();
		defSpw.getIValue().getObject()->continueTime();
		defSpw.next();
	}
	Spw.setBegin();
	for (int i = 0; i < Spw.size(); i++) {
		Spw.getIValue().getSpawnTimer().continueTime();
		Spw.getIValue().getObject()->continueTime();
		Spw.next();
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

void drawTitle() {
	glColor4f(0.7,0.7,0.7,1.0);
	glLineWidth(2);
	switch (gamemode) {
		case ID_LEVEL_A:
			glVertexPointer (2, GL_FLOAT, 0, title_LevelA);
			glDrawArrays(GL_LINES, 0, title_LevelA_mark[1]/2);
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
				case ID_LEVEL_A :
					Record << "Level_A";
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
			case ID_LEVEL_A :
				Record << "Level_A";
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
	storymode = false;
	delaytime.resetTime();
}

//Fungsi clear level
void clearLevel() {
	if (changeID.find(gamemode) == -1) {
		Sq.removeAll();
		Shots.removeAll();
	}
	defSpw.removeAll();
	Spw.removeAll();
	for (int i = 0; i < worldn; i++)
		worldtime[i].resetTime();
	worldn = 0;
	glColor4f(1.0,1.0,1.0,1.0);
	glVertexPointer (2, GL_FLOAT, 0, borders);
	glDrawArrays(GL_QUADS, 0, 4);
}

//Switch levels
void switchLevel(int gmode) {
	if (loaded)
		loaded = false;
	gamemode = gmode;
	clearLevel();
	createLevel();
	if (gmode == ID_WIN) {
		ofstream saveFile;
		saveFile.open("savedata");
		saveFile << gamemode << endl;
		saveFile.close();
		checkl = gamemode;
		delaytime.resetTime();
	} if (changeID.find(gmode) != -1) {
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
			case ID_MAINMENU :
				switch(key) {
					case GLFW_KEY_S :
						storymode = true;
						switchLevel(ID_ZONE1);
						break;
					case GLFW_KEY_L :
						storymode = true;
						switch (checkl) {
							case ID_WIN: switchLevel(ID_LEVEL_A);
								break;
							default: switchLevel(ID_ZONE1);
						}
						loaded = true;
						break;
					case GLFW_KEY_A :
						switchLevel(changeID[randomInt(0,changeID.size()-1)]);
						timeeffect.resetTime();
						break;
					case GLFW_KEY_H :
						switchLevel(ID_HELP);
						break;
					case GLFW_KEY_ESCAPE :
						glfwSetWindowShouldClose(window, GLFW_TRUE);
						break;
				}
				break;
			case ID_GAMEOVER :
			case ID_HELP :
			case ID_WIN :
				switch (key) {
					case GLFW_KEY_ESCAPE :
						glfwSetWindowShouldClose(window, GLFW_TRUE);
						break;
					default :
						if (delaytime.getElapsed() > 1) {
							switchLevel(ID_MAINMENU);
						}
				}
				break;
			default :
				if (key == GLFW_KEY_P && !storymode) {
					if (!disabled && !gameover) {
						
						disabled = true;
					} else {
						unpause();
					}
				} else if (key == GLFW_KEY_SPACE && !gameover && !disabled) {
					spacepressed = true;
				}
		}
	} else if (key == GLFW_KEY_SPACE && act == GLFW_RELEASE)
		spacepressed = false;
}

void enterCallback(GLFWwindow* window, int entered) {
	if (!entered && !disabled && !storymode && !gameover && (gamemode > 0) && (gamemode < 998)) { //Strict limited
		disabled = true;
	}
}

void drawCursor() {
	glColor3f(1.0,0.0,0.0);
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
	///Check shot damage
	int i = 0;
	bool check;
	Shots.setBegin();
	while (i < Shots.size()) {
		check = false;
		int j = 0;
		Spw.setBegin();
		while (j < Spw.size() && !check) {
			if (Spw.getIValue().getObject()->isMaterialised() && Spw.getIValue().getObject()->isIn(Shots.getIValue())) {
				check = true;
				Spw.getIValue().damage(SHOT_DAMAGE);
			} else {
				j++;
				Spw.next();
			}
		}
		if (check) {
			Shots.removeAt(i);
		} else {
			i++;
			Shots.next();
		}
	}
	
	///Removal check then draw
	i = 0;
	defSpw.setBegin();
	while (i < defSpw.size()) {
		if (defSpw.getIValue().getObject()->isDead()) {
			defSpw.removeAt(i);
		} else {
			defSpw.getIValue().getObject()->redraw();
			glVertexPointer (2, GL_FLOAT, 0, defSpw.getIValue().getObject()->getPointData());
			if (defSpw.getIValue().getObject()->isMaterialised())
				glColor4f(defSpw.getIValue().getObject()->getColorData()[0],defSpw.getIValue().getObject()->getColorData()[1],defSpw.getIValue().getObject()->getColorData()[2],1.0);
			else
				glColor4f(defSpw.getIValue().getObject()->getColorData()[0],defSpw.getIValue().getObject()->getColorData()[1],defSpw.getIValue().getObject()->getColorData()[2],0.4);
			glDrawArrays(GL_QUADS, 0, 4);
			defSpw.getIValue().spawnObject();
			defSpw.next();
			i++;
		}
	}
	
	i = 0;
	Spw.setBegin();
	while (i < Spw.size()) {
		if (Spw.getIValue().getHealth() <= 0) {
			Spw.removeAt(i);
		} else {
			Spw.getIValue().getObject()->redraw();
			glVertexPointer (2, GL_FLOAT, 0, Spw.getIValue().getObject()->getPointData());
			if (Spw.getIValue().isDamaged())
				glColor4f(1.0,0.0,0.0,1.0);
			else if (Spw.getIValue().getObject()->isMaterialised())
				glColor4f(Spw.getIValue().getObject()->getColorData()[0],Spw.getIValue().getObject()->getColorData()[1],Spw.getIValue().getObject()->getColorData()[2],1.0);
			else
				glColor4f(Spw.getIValue().getObject()->getColorData()[0],Spw.getIValue().getObject()->getColorData()[1],Spw.getIValue().getObject()->getColorData()[2],0.4);
			glDrawArrays(GL_QUADS, 0, 4);
			Spw.getIValue().spawnObject();
			Spw.next();
			i++;
		}
	}
	
	i = 0;
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
	
	i = 0;
	Shots.setBegin();
	while (i < Shots.size()) {
		if (Shots.getIValue().isDead()) {
			Shots.removeAt(i);
		} else {
			Shots.getIValue().redraw();
			glVertexPointer (2, GL_FLOAT, 0, Shots.getIValue().getPointData());
			glColor4f(0,1,1,1);
			glDrawArrays(GL_QUADS, 0, 4);
			Shots.next();
			i++;
		}
	}
}

void moveObjects() {
	Sq.setBegin();
	for (int i = 0; i < Sq.size(); i++) {
		Sq.getIValue().move();
		Sq.next();
	}
	Shots.setBegin();
	for (int i = 0; i < Shots.size(); i++) {
		Shots.getIValue().move();
		Shots.next();
	}
	defSpw.setBegin();
	for (int i = 0; i < defSpw.size(); i++) {
		defSpw.getIValue().getObject()->move();
		defSpw.next();
	}
	Spw.setBegin();
	for (int i = 0; i < Spw.size(); i++) {
		Spw.getIValue().getObject()->move();
		Spw.next();
	}
}

void switchArcade() {
	if ((rounds+1)%6 == 0)
		switchLevel(levelID[randomInt(0,levelID.size()-1)]);
	else {
		int x;
		do
			x = randomInt(0,changeID.size()-1);
		while (changeID[x] == gamemode);
		switchLevel(changeID[x]);
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
	helpmark[6] = helpmark[5];
	convertStringToLetterData(help6, 30, WINDOW_HEIGHT*6/10, linesize, helptext, helpmark[6], true);
	helpmark[7] = helpmark[6];
	convertStringToLetterData(help7, 30, WINDOW_HEIGHT*7/10, linesize, helptext, helpmark[7], true);
	convertPointData(helptext, 0, helpmark[7]);
	
	linesize = 2;
	title_LevelA_mark[0] = 0;
	title_LevelA_mark[1] = title_LevelA_mark[0];
	convertStringToLetterData(title_LevelA_str, 10, 10, linesize, title_LevelA, title_LevelA_mark[1], true);
	convertPointData(title_LevelA, 0, title_LevelA_mark[1]);
	
	//Initialize
	int iter;
	gamemode = ID_MAINMENU;
	xpos = WINDOW_WIDTH/2;
	ypos = WINDOW_HEIGHT/2;
	
	changeID.add(ID_ZONE1);
	changeID.add(ID_ZONE2);
	changeID.add(ID_BULLET1);
	changeID.add(ID_ZONE3);
	
	changeID.add(ID_ZONE1B);
	
	levelID.add(ID_LEVEL_A);
	
	ifstream loadFile;
	loadFile.open("savedata");
	loadFile >> checkl;
	loadFile.close();
	
	while (!glfwWindowShouldClose(window)) {
		
		//Membersihkan buffer
		if (!gameover || gamemode == ID_GAMEOVER)
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
		if (!paused()) {
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
		}
		
		switch (gamemode) {
			case ID_MAINMENU: 
				glVertexPointer (2, GL_FLOAT, 0, mainmenutext);
				glLineWidth(7);
				glDrawArrays(GL_LINES, 0, mainmenumark[1]/2);
				glLineWidth(3);
				glDrawArrays(GL_LINES, mainmenumark[1]/2, (mainmenumark[5]-mainmenumark[1])/2);
				drawCursor();
				break;
			case ID_ZONE1: {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 7) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_ZONE2);
				} else if (!gameover) {
					if (!paused()) {
						double y;
						if (worldtime[1].getElapsed() > 0.19) {
							int x = randomInt(1,4);
							switch (x) {
								case 1:
									defSpw[0].getObject()->setX(WINDOW_WIDTH/2);
									defSpw[0].getObject()->setY(-100);
									break;
								case 2:
									defSpw[0].getObject()->setX(WINDOW_WIDTH/2);
									defSpw[0].getObject()->setY(WINDOW_HEIGHT+100);
									break;
								case 3:
									defSpw[0].getObject()->setX(-100);
									defSpw[0].getObject()->setY(WINDOW_HEIGHT/2);
									break;
								case 4:
									defSpw[0].getObject()->setX(WINDOW_WIDTH+100);
									defSpw[0].getObject()->setY(WINDOW_HEIGHT/2);
									break;
							}
							if (worldtime[0].getElapsed() > 4)
								y = randomFloat(-25,25);
							else
								y = 0;
							worldtime[1].resetTime();
						}
						if (worldtime[0].getElapsed() > 4) {
							defSpw[0].setSpawnTime(0.2);
						}
						defSpw[0].getObject()->setAngle(-defSpw[0].getObject()->angleTo(Point(xpos, ypos))+y);
						drawObjects();
						drawCursor();
					}
				}
			} break;
			case ID_ZONE1B: {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 7) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_LEVEL_A);
				} else if (!gameover) {
					if (!paused()) {
						double y, z;
						if (worldtime[1].getElapsed() > 0.21) {
							int x = randomInt(1,2);
							switch (x) {
								case 1:
									defSpw[0].getObject()->setX(WINDOW_WIDTH+100);
									defSpw[0].getObject()->setY(WINDOW_HEIGHT/2);
									defSpw[1].getObject()->setX(-100);
									defSpw[1].getObject()->setY(WINDOW_HEIGHT/2);
									break;
								case 2:
									defSpw[0].getObject()->setX(WINDOW_WIDTH/2);
									defSpw[0].getObject()->setY(-100);
									defSpw[1].getObject()->setX(WINDOW_WIDTH/2);
									defSpw[1].getObject()->setY(WINDOW_HEIGHT+100);
									break;
							}
							if (worldtime[0].getElapsed() > 4) {
								y = randomFloat(-40,40);
								z = randomFloat(-40,40);
							} else {
								y = 0;
								z = 0;
							}
							worldtime[1].resetTime();
						}
						if (worldtime[0].getElapsed() > 4) {
							defSpw[0].setSpawnTime(0.22);
							defSpw[1].setSpawnTime(0.22);
						}
						defSpw[0].getObject()->setAngle(-defSpw[0].getObject()->angleTo(Point(xpos, ypos))+y);
						defSpw[1].getObject()->setAngle(-defSpw[1].getObject()->angleTo(Point(xpos, ypos))+z);
						drawObjects();
						drawCursor();
					}	
				}
			} break;
			case ID_LEVEL_A: { ///Level A
				if (!paused() && !gameover && worldtime[0].getElapsed() > LEVEL_A_TIME) {
					if (storymode) {
						switchLevel(ID_WIN);
						rounds = 0;
					} else {
						switchArcade();
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
							if (Sq.getIValue().getY() < -Sq.getIValue().getRadius()*2)
								Sq.getIValue().setY(WINDOW_HEIGHT+Sq.getIValue().getRadius()*2);
							Sq.next();
						}
						Sq.getIValue().setSpeed(sqrt(Sq.getIValue().distanceSquaredTo(Point(xpos, ypos)))/100+2);
						Sq.getIValue().setDirection(-Sq.getIValue().angleTo(Point(xpos, ypos))); //Karena y terbalik menurut terminal
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
						drawCursor();
					}
				}
				} break;
			case ID_BULLET1: {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 6) {
					if (storymode)
						switchLevel(ID_ZONE3);
					else
						switchArcade();
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() > 4) {
							for (int i = 0; i < 4; i++)
								defSpw[i].setSpawnTime(0.3);
						}
						for (int i = 0; i < 4; i++)
							defSpw[i].getObject()->setAngle(-defSpw[i].getObject()->angleTo(Point(xpos, ypos)));
						drawObjects();
						drawCursor();
					}	
				}
				} break;
			case ID_ZONE2 : {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 4) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_BULLET1);
				} else if (!gameover) {
					if (!paused()) {
						if ((rounds > 3) && worldtime[1].getElapsed() > 0.1) {
							float x = randomFloat(0.8,1.6);
							Sq.add(SquareObj(xpos + randomDouble(-300, 300), ypos + randomDouble(-300, 300), randomInt(200, 450), x+0.5, x));
							worldtime[1].resetTime();
						} else if (worldtime[1].getElapsed() > 0.18) {
							float x = randomFloat(0.8,1.6);
							Sq.add(SquareObj(xpos + randomDouble(-300, 300), ypos + randomDouble(-300, 300), randomInt(200, 450), x+0.5, x));
							worldtime[1].resetTime();
						}
						Sq.setBegin();
						for (int i = 0; i < Sq.size(); i++) {
							if (!Sq.getIValue().isMaterialised())
								Sq.getIValue().setAngle(Sq.getIValue().getLifeTime().getElapsed()*100);
							Sq.next();
						}
						drawObjects();
						drawCursor();
					}	
				}
				} break;
			case ID_ZONE3: {
				if (!paused() && !gameover && (Spw.isEmpty() || worldtime[0].getElapsed() > 11)) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_ZONE1B);
				} else if (!gameover) {
					if (!paused()) {
						Spw[0].getObject()->setAngle(worldtime[0].getElapsed()*830);
						if (worldtime[0].getElapsed() < 4 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/3) {
							Spw[0].getObject()->setSpeed(0);
							Spw[0].getObject()->setY(WINDOW_HEIGHT/3-0.01);
						} else if (worldtime[0].getElapsed() > 8) {
							Spw[0].getObject()->setSpeed(5);
						}
						drawObjects();
						drawCursor();
					}	
				}
				} break;
			case ID_HELP: {
				glVertexPointer (2, GL_FLOAT, 0, helptext);
				glLineWidth(2);
				glDrawArrays(GL_LINES, 0, helpmark[7]/2);
				drawCursor();
				} break;
			case ID_WIN: {
				glLineWidth(7);
				glVertexPointer (2, GL_FLOAT, 0, wintext);
				glColor4f(1.0,1.0,1.0,delaytime.getElapsed());
				glDrawArrays(GL_LINES, 0, winmark[2]/2);
				} break;
			default: //ID_GAMEOVER
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
		if (!disabled) {
			drawTitle();
			moveObjects();
		}
			
		///Draw timer
		if (!storymode && !disabled && !gameover && (gamemode > 0) && (gamemode < 998)) { //strict limiter
			drawTimer();
		}
		
		///Shooting
		if (!gameover && spacepressed && delaytime.getElapsed() > SHOT_DELAY) {
			QuadObj shot(xpos, ypos-5, 8, 20, 3);
			shot.setDirection(90);
			shot.setSpeed(10);
			Shots.add(shot);
			delaytime.resetTime();
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
		iter = 0;
		defSpw.setBegin();
		while ((!disabled) && (iter < defSpw.size()) && (!gameover)) {
			if (defSpw.getIValue().getObject()->isMaterialised() && defSpw.getIValue().getObject()->isIn(Point(xpos, ypos))) {
				gameOver();
			}
			defSpw.next();
			iter++;
		}
		iter = 0;
		Spw.setBegin();
		while ((!disabled) && (iter < Spw.size()) && (!gameover)) {
			if (Spw.getIValue().getObject()->isMaterialised() && Spw.getIValue().getObject()->isIn(Point(xpos, ypos))) {
				gameOver();
			}
			Spw.next();
			iter++;
		}
						
		if (gameover) { //gameover
			if (delaytime.getElapsed() > 2) {
				switchLevel(ID_GAMEOVER);
				gameover = false;
				spacepressed = false;
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
