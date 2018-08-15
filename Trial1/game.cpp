///Compiling shortcut (Linux): g++ -o message message.cpp -lGL -lGLU -lglfw ///
#include <GLFW/glfw3.h>
#include <iostream>
#include "randomer.hpp"
using namespace std;

#include <fstream>
#include "Lists.hpp"
#include "Time.hpp"
#include <ctime>
#include "Letter.hpp"
#include "Spawner2D.hpp"
#include "SquareObj.hpp"
#include "QuadObj.hpp"
#include "TriangleObj.hpp"
#include "PatternObj.hpp"

///Global variables
GLFWwindow* gamewindow;
int linesize;
double WINDOW_HEIGHT; //tested on 1000+ pixels
double WINDOW_WIDTH; //tested on 600+ pixels
const float CURSOR_SIZE = 4;

const float sqrtTwo = sqrt(2);
const float sqrtThree = sqrt(3);

const float CURSOR_DIAG = CURSOR_SIZE*sqrtTwo;

//Game variables:
double xpos, ypos;
double newxpos, newypos;
double expos, eypos;

Time timeeffect;
Time worldtime[5];
int worldn = 0;
Time delaytime;
bool gameover = false;
bool spacepressed = false;
bool hardmode = false;
bool practicemode = false;

const float SHOT_DELAY = 0.095;

const float SHOT_DAMAGE = 1;
int bombcount;

float gameovertext[1200];
int gameovermark[1];
const string gameover1 = "GAME OVER";

float mainmenutext[3000];
int mainmenumark[6];
const string mainmenu1 = "T R I A L S";
const string mainmenu2 = "";
const string mainmenu3 = "Press Spacebar to begin trial.";
const string mainmenu4 = "Press X to begin hard mode.";
const string mainmenu5 = "Press H for help. Press Esc to quit.";

float wintext[3200];
int winmark[4];
const string wintext1 = "END OF GAME";
const string wintext2 = "Thanks for playing";
const string wintext3 = "You can press numbers 1 to 6 and certain alphabet keys in help page to practise.";

float helptext[9300];
int helpmark[7];
const string help1 = "Dodge all obstacles. Move with mouse.";
const string help2 = "Hold Spacebar to shoot enemies.";
const string help3 = "Press X to use bomb. You can carry MAXIMUM 5 bombs per trial.";
const string help4 = "It is up to you to change your mouse sensitivity.";
const string help5 = "This game may not be completable by everyone. Stay calm.";
const string help6 = "Press Spacebar to return to main menu.";

float backtext[100000];
int backmark[13];
const string back1 = "C C C C C C C C C C C C C C C C C C C C C C C C C C C";


///Title texts
float title[1500];
int titlemark;

GLfloat borders[8] = {-1.0,-1.0, -1.0,1.0, 1.0,1.0, 1.0,-1.0};
GLfloat cursorpoint[16];
int gamemode = 0;

///Objects
List<SquareObj> Sq;
List<TriangleObj> Tr;
List<QuadObj> Qu;
List<QuadObj> Shots;

List<Spawner2D> defSpw;
List<Spawner2D> subSpw;
List<Spawner2D> Spw;
List<PatternObj> Ptt;
List<PatternObj> defPtt;

QuadObj healthBar(0, 0, 0, 0, 0);

//Helper procedure
void spawnerClear(List<Spawner2D>& Li) {
	Li.setBegin();
	while (!Li.atEnd()) {
		switch (Li.getIValue().getObjType()) {
			case TYPE_SQUARE: delete (SquareObj*)Li.getIValue().getObject();
			break;
			case TYPE_QUAD: delete (QuadObj*)Li.getIValue().getObject();
			break;
			case TYPE_TRIANGLE: delete (TriangleObj*)Li.getIValue().getObject();
			break;
		}
		Li.next();
	}
	Li.removeAll();
}
void patternClear(List<PatternObj>& Li) {
	Li.setBegin();
	while (!Li.atEnd()) {
		delete[] Li.getIValue().getObjData();
		Li.next();
	}
	Li.removeAll();
}
 
///Stages
const int ID_GAMEOVER = -1;
const int ID_MAINMENU = 0;
const int ID_HELP = 998;
const int ID_WIN = 999;

const int ZONE_LIMIT = 987;
const int ID_TEST = 986;
const int ID_TEST2 = 885;
const int ID_TEST3 = 884;
const int ID_TEST4 = 883;
const int ID_TEST5 = 882;
const int ID_TEST6 = 881;
const int ID_FINAL = 880;

const int LEVEL_LIMIT = 800;

int patterner;
Point pointmark;

/* convert pixel to openGL coordinates */
void convertPointData(float *arr, int start, int end) {
	for (int i = start; i < end; i += 2) {
		arr[i] = widthConvert(arr[i]);
	}
	for (int i = start+1; i < end; i += 2) {
		arr[i] = heightConvert(arr[i]);
	}
}

///Pattern shots
const int PATTERN_DEFAULT = 0;

//Pattern helper
void PatternObj::move() {
	setX(getX() + speed*cos(convertToRadian(direction)));
	setY(getY() - speed*sin(convertToRadian(direction)));
	switch (patterntype) {
		case PATTERN_DEFAULT: {
			for (int i = 0; i < n; i++) {
				if (objData[i] != nullptr) {
					objData[i]->setX(objData[i]->getX() + speed*cos(convertToRadian(direction)));
					objData[i]->setY(objData[i]->getY() - speed*sin(convertToRadian(direction)));
				}
			}
		} break;
	}
}

///Spawn shots
const int NULL_SHOT = 0;
const int QUAD_1 = 1;
const int QUAD_2 = 2;
const int TRIANGLE_1 = 3;
const int SQUARE_1 = 4;
const int TRIANGLE_2 = 5;
const int QUAD_3 = 6;
const int SQUARE_2 = 7;
const int CIRCLE_1 = 8;
const int TRIANGLE_3 = 9;
const int EFFECT_1 = 10;
const int QUAD_4 = 11;
const int QUAD_5 = 12;
const int SQUARE_3 = 13;
const int SQUARE_4 = 14;
const int TRIANGLE_4 = 15;
const int TRIANGLE_5 = 16;
const int SQUARE_5 = 17;

void Spawner2D::spawnObject() {
	switch(spawntype) {
		case QUAD_1 : {
			for (int i = 0; i < 5; i++) {
				float ang = -spawner->angleTo(Point(xpos, ypos)) + 15*(i-2);
				Qu.add(QuadObj(spawner->getX() + 30*cos(convertToRadian(ang)), spawner->getY() - 30*sin(convertToRadian(ang)), 70, 25, 6));
				Qu[0].setSpeed(5.4);
				Qu[0].setAngle(ang);
				Qu[0].setDirection(Qu[0].getAngle());
				Qu[0].getColorData()[0] = 0.0;
				Qu[0].getColorData()[1] = 0.0;
			}
		} break;
		case QUAD_2 : {
			float ang = randomFloat(230.0, 310.0);
			Qu.add(QuadObj(spawner->getX() + WINDOW_HEIGHT/2*cos(convertToRadian(ang)), spawner->getY() - WINDOW_HEIGHT/2*sin(convertToRadian(ang)), WINDOW_WIDTH, 35, 5, 1.8));
			Qu[0].setAngle(ang);
			Qu[0].getColorData()[0] = 0.0;
			if (hardmode) Qu[0].setDim2(30);
		} break;
		case TRIANGLE_1 : {
			Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 45, 40, 5));
			Tr[0].setSpeed(!hardmode? 7 : 8);
			Tr[0].setAngle(-spawner->angleTo(Point(xpos, ypos)));
			Tr[0].setDirection(Tr[0].getAngle());
			Tr[0].getColorData()[1] = 0.8;
			Tr[0].getColorData()[1] = 0.8;
			Tr[0].getColorData()[2] = 0.0;
		} break;
		case SQUARE_1 : {
			float
				xpdel = hardmode ? 0.75 : 1.0,
				speed = hardmode ? 9.0 : 7.0;
			subSpw.add(Spawner2D(new SquareObj(spawner->getX(), spawner->getY(), 190, xpdel), TYPE_SQUARE, xpdel - 0.022, 999, TRIANGLE_2));
			subSpw[0].getObject()->setSpeed(speed);
			subSpw[0].getObject()->setDirection(-spawner->angleTo(Point(xpos, ypos)));
			subSpw[0].getObject()->setAngle(subSpw[0].getObject()->getDirection());
			subSpw[0].getObject()->getColorData()[0] = 0.3;
			subSpw[0].getObject()->getColorData()[1] = 0.9;
		} break;
		case SQUARE_3 : {
			subSpw.add(Spawner2D(new SquareObj(spawner->getX(), spawner->getY(), 120, 1.0), TYPE_SQUARE, 0.978, 999, SQUARE_4));
			subSpw[0].getObject()->setSpeed(12);
			subSpw[0].getObject()->setDirection(-spawner->angleTo(Point(xpos, ypos)));
			subSpw[0].getObject()->setAngle(subSpw[0].getObject()->getDirection());
			subSpw[0].getObject()->getColorData()[1] = 0.5;
			subSpw[0].getObject()->getColorData()[2] = 0.5;
		} break;
		case SQUARE_4 : {
			for (int i = 0; i < 12; i++) {
				subSpw.add(Spawner2D(new SquareObj(spawner->getX(), spawner->getY(), 60, 1.0), TYPE_SQUARE, 0.978, 999, TRIANGLE_4));
				subSpw[0].getObject()->setSpeed(10);
				subSpw[0].getObject()->setDirection(spawner->getAngle() + 30*i);
				subSpw[0].getObject()->setAngle(subSpw[0].getObject()->getDirection());
				subSpw[0].getObject()->getColorData()[0] = 0.8;
				subSpw[0].getObject()->getColorData()[1] = 0.3;
				subSpw[0].getObject()->getColorData()[2] = 0.3;
			}
		} break;
		case TRIANGLE_4 : {
			Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 40, 20, 5));
			Tr[0].setAngle(-Tr[0].angleTo(Point(xpos, ypos)));
			Tr[0].setDirection(Tr[0].getAngle());
			Tr[0].getColorData()[0] = 0.6;
			Tr[0].getColorData()[1] = 0.1;
			Tr[0].getColorData()[2] = 0.1;
		} break;
		case TRIANGLE_2 : {
			float
				xpdel = hardmode ? 0.75 : 1.0,
				speed = hardmode ? 6.0 : 5.0;
			for (int i = 0; i < 4; i++) {
				subSpw.add(Spawner2D(new TriangleObj(spawner->getX(), spawner->getY(), 70*sqrtThree, 140, xpdel), TYPE_TRIANGLE, xpdel - 0.022, 999, QUAD_3));
				subSpw[0].getObject()->setSpeed(speed);
				subSpw[0].getObject()->setDirection(spawner->getAngle() + 90*i + 45);
				subSpw[0].getObject()->setAngle(subSpw[0].getObject()->getDirection());
				subSpw[0].getObject()->getColorData()[0] = 0.3;
				subSpw[0].getObject()->getColorData()[1] = 0.9;
			}
		} break;
		case QUAD_3 : {
			for (int i = 0; i < 3; i++) {
				Qu.add(QuadObj(spawner->getX(), spawner->getY(), 120, 50, 16));
				Qu[0].setSpeed(hardmode?2.2:2.6);
				Qu[0].setDirection(spawner->getAngle() + 120*i);
				Qu[0].setAngle(Qu[0].getDirection());
				Qu[0].getColorData()[0] = 0.3;
				Qu[0].getColorData()[1] = 0.9;
			}
		} break;
		case SQUARE_2 : {
			for (int i = 0; i < 2; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 20, 999));
				Sq[0].setSpeed(randomFloat(1.9, 4.5));
				float d = randomFloat(0, 360);
				Sq[0].setAngle(d);
				Sq[0].setDirection(d);
			}
			if (patterner%100 == 0) {
				float ang = -spawner->angleTo(Point(xpos, ypos));
				for (int i = 0; i < 48; i++) {
					Sq.add(SquareObj(spawner->getX(), spawner->getY(), 40, 5));
					Sq[0].setSpeed(3.8);
					Sq[0].setAngle(ang+(float)i/24*180);
					Sq[0].setDirection(Sq[0].getAngle());
					Sq[0].getColorData()[1] = 0.7;
					Sq[0].getColorData()[2] = 0.1;
				}
			}
			patterner++;
		} break;
		case SQUARE_5 : {
			for (int i = 0; i < 5; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 20, 999));
				Sq[0].setSpeed(randomFloat(1.9, 4.5));
				float d = randomFloat(0, 360);
				Sq[0].setAngle(d);
				Sq[0].setDirection(d);
			}
			if (patterner%25 == 0) {
				float ang = -spawner->angleTo(Point(xpos, ypos));
				for (int i = 0; i < 48; i++) {
					Sq.add(SquareObj(spawner->getX(), spawner->getY(), 40, 5));
					Sq[0].setSpeed(3.8);
					Sq[0].setAngle(ang+(float)i/24*180);
					Sq[0].setDirection(Sq[0].getAngle());
					Sq[0].getColorData()[1] = 0.7;
					Sq[0].getColorData()[2] = 0.1;
				}
			}
			patterner++;
		} break;
		case CIRCLE_1 : {
			Ptt.add(PatternObj(spawner->getX(), spawner->getY(), 48, PATTERN_DEFAULT));
			Ptt[0].setSpeed(2.8);
			Ptt[0].setDirection(-spawner->angleTo(Point(xpos, ypos)));
			int ran = randomInt(0,1);
			for (int i = 0; i < 48; i++) {
				float ang = -spawner->angleTo(Point(xpos, ypos)) + (float)i/48*360;
				subSpw.add(
					Spawner2D(
						new SquareObj(
							spawner->getX() + 100*cos(convertToRadian(ang)),
							spawner->getY() - 100*sin(convertToRadian(ang)),
							20, 8.1
						),
						TYPE_SQUARE, 2.8, 999, TRIANGLE_3
					)
				);
				subSpw[0].getObject()->setDirection(ang);
				subSpw[0].getObject()->setAngle(subSpw[0].getObject()->getDirection() + 90 - 180*ran);
				subSpw[0].getObject()->getColorData()[0] = 0.8;
				subSpw[0].getObject()->getColorData()[1] = 0.0;
				Ptt[0].add(subSpw[0].getObject());
			}
			if (hardmode) {
				patterner++;
				if (patterner%4 == 0) {
					float ang = -spawner->angleTo(Point(xpos, ypos));
					for (int i = 0; i < 48; i++) {
						Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 27, 20, 30));
						Tr[0].setSpeed(4);
						Tr[0].setAngle(ang+(float)i/24*180);
						Tr[0].setDirection(Tr[0].getAngle());
						Tr[0].getColorData()[0] = 0.9;
						Tr[0].getColorData()[1] = 0.5;
						Tr[0].getColorData()[2] = 0.9;
					}
				}
			}
		} break;
		case TRIANGLE_3 : {
			Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 27, 20, 30));
			Tr[0].setSpeed(4);
			Tr[0].setAngle(spawner->getAngle());
			Tr[0].setDirection(Tr[0].getAngle());
			Tr[0].getColorData()[0] = 0.6;
			Tr[0].getColorData()[1] = 0.0;
			Tr[0].getColorData()[2] = 0.6;
		} break;
		case TRIANGLE_5 : {
			for(int i=0; i<2; i++)
				for(int j=0; j<2; j++)
					for(int k=0; k<4; k++) {
						Tr.add(TriangleObj(-30 + (WINDOW_WIDTH+60)*i, -30 + (WINDOW_HEIGHT+60)*j, 27, 20, 15));
						Tr[0].setSpeed(2.4);
						Tr[0].setAngle(k * 90 + 45 + randomFloat(35.0,44.0) * (randomInt(0,1)==0 ? 1 : -1));
						Tr[0].setDirection(Tr[0].getAngle());
						Tr[0].getColorData()[0] = 0.4;
						Tr[0].getColorData()[1] = 0.0;
						Tr[0].getColorData()[2] = 0.4;
					}
		} break;
		case EFFECT_1 : {
			float ang = randomFloat(0.0, 360.0);
			float factor = randomFloat(100, 450);
			Sq.add(SquareObj(spawner->getX() + factor*cos(convertToRadian(ang)), spawner->getY() - factor*sin(convertToRadian(ang)), randomFloat(20, 70), 0.6, 1.5));
			Sq[0].setSpeed(sqrt(Sq[0].distanceSquaredTo(*spawner))/50);
			Sq[0].setAngle(ang - 180);
			Sq[0].setDirection(Sq[0].getAngle());
		} break;
		case QUAD_4 : {
			Ptt.add(PatternObj(spawner->getX(), spawner->getY(), 2, PATTERN_DEFAULT));
			Ptt[0].setSpeed(defPtt[0].getSpeed());
			Ptt[0].setDirection(defPtt[0].getDirection());
			Qu.add(QuadObj(Ptt[0].getX(), Ptt[0].getY(), 70, 12, 999));
			Qu[0].setAngle(Ptt[0].getDirection());
			Qu[0].setDirection(Qu[0].getAngle());
			Qu[0].getColorData()[0] = 0.0;
			Qu[0].getColorData()[2] = 0.0;
			Tr.add(TriangleObj(Qu[0].getX() + 45*cos(convertToRadian(Qu[0].getAngle())), Qu[0].getY() - 45*sin(convertToRadian(Qu[0].getAngle())), 30, 40, 999));
			Tr[0].setAngle(Qu[0].getAngle());
			Tr[0].setDirection(Qu[0].getAngle());
			Tr[0].getColorData()[0] = 0.0;
			Tr[0].getColorData()[2] = 0.0;
			Ptt[0].add(&Qu[0]);
			Ptt[0].add(&Tr[0]);
		} break;
		case QUAD_5 : {
			defPtt.add(PatternObj(spawner->getX(), spawner->getY(), 2, PATTERN_DEFAULT));
			defPtt[0].setSpeed(9);
			defPtt[0].setDirection(-defPtt[0].angleTo(Point(xpos, ypos)));
			defSpw.add(Spawner2D(new QuadObj(defPtt[0].getX(), defPtt[0].getY(), 70, 12, 999), TYPE_QUAD, 0.8, 1, QUAD_4));
			defSpw[0].getObject()->setAngle(defPtt[0].getDirection());
			defSpw[0].getObject()->setDirection(defPtt[0].getDirection());
			defSpw[0].getObject()->getColorData()[0] = 0.3;
			defSpw[0].getObject()->getColorData()[2] = 0.3;
			defPtt[0].add(defSpw[0].getObject());
			defSpw.add(Spawner2D(new TriangleObj(defSpw[0].getObject()->getX() + 45*cos(convertToRadian(defPtt[0].getDirection())), defSpw[0].getObject()->getY() - 45*sin(convertToRadian(defPtt[0].getDirection())), 30, 40, 999), TYPE_TRIANGLE, 999, 1, NULL_SHOT));
			defSpw[0].getObject()->setAngle(defPtt[0].getDirection());
			defSpw[0].getObject()->setDirection(defPtt[0].getDirection());
			defSpw[0].getObject()->getColorData()[0] = 0.3;
			defSpw[0].getObject()->getColorData()[2] = 0.3;
			defPtt[0].add(defSpw[0].getObject());
		} break;
	}
	spawntimer.resetTime();
}

//Level init
void createLevel() {
	linesize = 2;
	titlemark = 0;
	switch (gamemode) {
		case ID_TEST : {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -240, 220, 999, 1.5), TYPE_SQUARE, 0.6, 180, QUAD_1));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.7;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			if (hardmode) {
				Spw[0].setSpawnTime(0.3);
			}
			worldn = 1;
			pointmark = Point(WINDOW_WIDTH/2, 135);
			
			convertStringToLetterData("The Trial Begins", 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_TEST2 : {
			pointmark = Point(WINDOW_WIDTH/2, 135);
			Spw.add(Spawner2D(new SquareObj(expos, eypos, 220, 999, 2.5), TYPE_SQUARE, 0.8, 420, TRIANGLE_1));
			Spw[0].getObject()->setSpeed(5);
			Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
			Spw[0].getObject()->getColorData()[0] = 0.7;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			if (!hardmode)
				for (int i = 0; i < 47; i++) {
					defSpw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/40*(i-3), -30, 1, 1, 999), TYPE_NULL, 6, 1, QUAD_2));
					defSpw[0].getSpawnTimer().setTime(10*i);
				}
			else {
				for (int i = 0; i < 67; i++) {
					defSpw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/60*(i-3), -30, 1, 1, 999), TYPE_NULL, 6, 1, QUAD_2));
					defSpw[0].getSpawnTimer().setTime(4*i);
				}
				Spw[0].setSpawnTime(0.5);
			}
			
			worldn = 1;
			
			convertStringToLetterData("C Sign: Assignment Hunt", 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_TEST3 : {
			pointmark = Point(WINDOW_WIDTH/2, 135);
			Spw.add(Spawner2D(new SquareObj(expos, eypos, 220, 999, 1.6), TYPE_SQUARE, 999, 370, SQUARE_1));
			Spw[0].getObject()->setSpeed(10);
			Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
			Spw[0].getObject()->getColorData()[0] = 0.7;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			worldn = 1;
			
			convertStringToLetterData("Visual Sign: Polygon Splash", 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_TEST4 : {
			pointmark = Point(WINDOW_WIDTH/2, 135);
			Spw.add(Spawner2D(new SquareObj(expos, eypos, 220, 999, 2), TYPE_SQUARE, 3, 320, SQUARE_3));
			Spw[0].getObject()->setSpeed(5);
			Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
			Spw[0].getObject()->getColorData()[0] = 0.7;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			worldn = 1;
			
			convertStringToLetterData("C Sign: Complex Deathlock", 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_TEST5 : {
			pointmark = Point(WINDOW_WIDTH/2, 150);
			Spw.add(Spawner2D(new SquareObj(expos, eypos, 220, 999, 2.5), TYPE_SQUARE, hardmode ? 2.0 : 2.7, 360, CIRCLE_1));
			Spw[0].getObject()->setSpeed(3);
			Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
			Spw[0].getObject()->getColorData()[0] = 0.7;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			worldn = 1;
			
			convertStringToLetterData("Visual Sign: Wish Upon Stars", 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_TEST6 : {
			pointmark = Point(WINDOW_WIDTH/2, 135);
			Spw.add(Spawner2D(new SquareObj(expos, eypos, 220, 35, 38), TYPE_SQUARE, 999, 400, QUAD_5));
			Spw[0].getObject()->setSpeed(7);
			Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
			Spw[0].getObject()->getColorData()[0] = 0.7;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			worldn = 2;
			
			convertStringToLetterData("C Sign: Death Pointers", 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_FINAL : {
			pointmark = Point(WINDOW_WIDTH/2, 135);
			Spw.add(Spawner2D(new SquareObj(pointmark.getX(), pointmark.getY(), 220, 999, 3), TYPE_SQUARE, (hardmode ? 0.018 : 0.008), (hardmode ? 750 : 500), SQUARE_2));
			Spw[0].getObject()->getColorData()[0] = 0.7;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			worldn = 1;
			defSpw.add(Spawner2D(new SquareObj(pointmark.getX(), pointmark.getY(), 1, 2.5, 1.0), TYPE_NULL, 0.008, 1, EFFECT_1));
			
			convertStringToLetterData("Final Sign: Minutes Before Deadline", 10, 10, linesize, title, titlemark, true);
		} break;
		default:
			worldn = 1;
	}
	if (gamemode > 0 && gamemode < ZONE_LIMIT)
		Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 0.05, 1));
	convertPointData(title, 0, titlemark);
	for (int i = 0; i < worldn; i++)
		worldtime[i].resetTime();
	healthBar.setDim1(-1);
}

void drawTitle() {
	glColor4f(0.7,0.7,0.7,1.0);
	glLineWidth(2);
	glVertexPointer (2, GL_FLOAT, 0, title);
	glDrawArrays(GL_LINES, 0, titlemark/2);
}

//Game over
void gameOver() {
	gameover = true;
	glColor4f(1.0,0.0,0.0,0.4);
	glVertexPointer (2, GL_FLOAT, 0, borders);
	glDrawArrays(GL_QUADS, 0, 4);
	glfwSwapBuffers(gamewindow);
	delaytime.resetTime();
}

//Fungsi clear level
void clearLevel(int gmode) {
	pointmark = Point(0,0);
	if (gmode <= 0 || gamemode <= 0 || gmode > LEVEL_LIMIT || gamemode > LEVEL_LIMIT) {
		Sq.removeAll();
		Tr.removeAll();
		Qu.removeAll();
		spawnerClear(subSpw);
		patternClear(Ptt);
		if (gmode <= 0 || gmode > ZONE_LIMIT)
			Shots.removeAll();
		spawnerClear(Spw);
	}
	patternClear(defPtt);
	spawnerClear(defSpw);
}

//Bomb effect, mirip clear level
void bomb() {
	Sq.setBegin();
	while (!Sq.atEnd()) {
		if (Sq.getIValue().isMaterialised())
			Sq.getIValue().getLifeTimer().setTime(999000);
		Sq.next();
	}
	
	Tr.setBegin();
	while (!Tr.atEnd()) {
		if (Tr.getIValue().isMaterialised())
			Tr.getIValue().getLifeTimer().setTime(999000);
		Tr.next();
	}
	
	Qu.setBegin();
	while (!Qu.atEnd()) {
		if (Qu.getIValue().isMaterialised())
			Qu.getIValue().getLifeTimer().setTime(999000);
		Qu.next();
	}
	subSpw.setBegin();
	while (!subSpw.atEnd()) {
		if (subSpw.getIValue().getObject()->isMaterialised())
			subSpw.getIValue().getObject()->getLifeTimer().setTime(999000);
		subSpw.next();
	}
	Spw.setBegin();
	while (!Spw.atEnd()) {
		if (Spw.getIValue().getObject()->isMaterialised())
			Spw.getIValue().damage(10);
		Spw.next();
	}
	Sq.add(SquareObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 2000, 0.05, 1));
	Sq[0].getColorData()[1] = 0.0;
	Sq[0].getColorData()[2] = 0.0;
}

//Switch levels
void switchLevel(int gmode) {
	if (practicemode) {
		gmode = ID_MAINMENU;
	} else if (gamemode == ID_HELP) {
		practicemode = true;
		bombcount = 0;
	}
	clearLevel(gmode);
	gamemode = gmode;
	createLevel();
	patterner = 0;
	if ((gamemode <= 0) || (gamemode > ZONE_LIMIT)) {
		practicemode = false;
		hardmode = false;
		expos = WINDOW_WIDTH/2;
		eypos = 135;
	}
	if (gamemode > ZONE_LIMIT)
		delaytime.resetTime();
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
					case GLFW_KEY_SPACE :
						spacepressed = true;
						switchLevel(ID_TEST);
						bombcount = 5;
					break;
					case GLFW_KEY_X :
						hardmode = true;
						switchLevel(ID_TEST);
						bombcount = 5;
					break;
					case GLFW_KEY_H :
						switchLevel(ID_HELP);
					break;
					case GLFW_KEY_ESCAPE :
						glfwSetWindowShouldClose(window, GLFW_TRUE);
					break;
				}
			break;
			case ID_HELP :
				switch(key) {
					case GLFW_KEY_Q : hardmode = true;
					case GLFW_KEY_1 :
						switchLevel(ID_TEST2);
					break;
					case GLFW_KEY_W : hardmode = true;
					case GLFW_KEY_2 :
						switchLevel(ID_TEST3);
					break;
					case GLFW_KEY_E : hardmode = true;
					case GLFW_KEY_3 :
						switchLevel(ID_TEST4);
					break;
					case GLFW_KEY_R : hardmode = true;
					case GLFW_KEY_4 :
						switchLevel(ID_TEST5);
					break;
					case GLFW_KEY_T : hardmode = true;
					case GLFW_KEY_5 :
						switchLevel(ID_TEST6);
					break;
					case GLFW_KEY_Y : hardmode = true;
					case GLFW_KEY_6 :
						switchLevel(ID_FINAL);
					break;
					case GLFW_KEY_SPACE :
						switchLevel(ID_MAINMENU);
					break;
				}
			break;
			case ID_GAMEOVER :
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
			case ID_WIN :
				switch (key) {
					case GLFW_KEY_ESCAPE :
						glfwSetWindowShouldClose(window, GLFW_TRUE);
					break;
					default :
						if (delaytime.getElapsed() > 3) {
							switchLevel(ID_MAINMENU);
						}
				}
			break;
			default :
				if (gamemode < ZONE_LIMIT && key == GLFW_KEY_X) {
					if (bombcount > 0) {
						bomb();
						bombcount--;
					}
				}
				if (key == GLFW_KEY_SPACE && !gameover) {
					spacepressed = true;
				}
		}
	} else if (key == GLFW_KEY_SPACE && act == GLFW_RELEASE) {
		spacepressed = false;
	}
}

void drawCursor() {
	if (!gameover)
		glColor3f(1.0,0.0,0.0);
	else 
		glColor3f(1.0 - delaytime.getElapsed(),0.0,0.0);
	cursorpoint[0] = widthConvert(xpos-CURSOR_SIZE);
	cursorpoint[1] = heightConvert(ypos-CURSOR_SIZE);
	cursorpoint[2] = widthConvert(xpos);
	cursorpoint[3] = heightConvert(ypos-CURSOR_DIAG);
	cursorpoint[4] = widthConvert(xpos+CURSOR_SIZE);
	cursorpoint[5] = heightConvert(ypos-CURSOR_SIZE);
	cursorpoint[6] = widthConvert(xpos+CURSOR_DIAG);
	cursorpoint[7] = heightConvert(ypos);
	cursorpoint[8] = widthConvert(xpos+CURSOR_SIZE);
	cursorpoint[9] = heightConvert(ypos+CURSOR_SIZE);
	cursorpoint[10] = widthConvert(xpos);
	cursorpoint[11] = heightConvert(ypos+CURSOR_DIAG);
	cursorpoint[12] = widthConvert(xpos-CURSOR_SIZE);
	cursorpoint[13] = heightConvert(ypos+CURSOR_SIZE);
	cursorpoint[14] = widthConvert(xpos-CURSOR_DIAG);
	cursorpoint[15] = heightConvert(ypos);
	
	glVertexPointer (2, GL_FLOAT, 0, cursorpoint);
	glDrawArrays(GL_POLYGON, 0, 8);
}

void checkDamaged() {
	///Check shot damage
	bool check;
	float healthdisplay = -10;
	Shots.setBegin();
	while (!Shots.atEnd()) {
		check = false;
		Spw.setBegin();
		while (!Spw.atEnd() && !check) {
			if (Spw.getIValue().getObject()->isMaterialised() && Spw.getIValue().getObject()->isIn(Shots.getIValue())) {
				check = true;
				Spw.getIValue().damage(SHOT_DAMAGE);
				healthdisplay = Spw.getIValue().getHealth()/Spw.getIValue().getMaxHealth();
			} else {
				Spw.next();
			}
		}
		if (check) {
			Shots.removeIValue();
		} else {
			Shots.next();
		}
	}
	if (healthdisplay > -10) {
		healthBar.setDim1(healthdisplay*(WINDOW_WIDTH-10));
		healthBar.setX(healthBar.getDim1()/2 + 5);
	}
}

void deleteOBObjects() { //and remove
	Qu.setBegin();
	while (!Qu.atEnd()) {
		float size = Qu.getIValue().getDim2() + Qu.getIValue().getDim1();
		if (Qu.getIValue().getX() < -size || Qu.getIValue().getX() > WINDOW_WIDTH + size || Qu.getIValue().getY() < -size || Qu.getIValue().getY() > WINDOW_HEIGHT + size) {
			Qu.getIValue().getLifeTimer().setTime(999999);
		}
		Qu.next();
	}
	
	Sq.setBegin();
	while (!Sq.atEnd()) {
		if (Sq.getIValue().getX() < -Sq.getIValue().getRadius()*2 || Sq.getIValue().getX() > WINDOW_WIDTH + Sq.getIValue().getRadius()*2 || Sq.getIValue().getY() < -Sq.getIValue().getRadius()*2 || Sq.getIValue().getY() > WINDOW_HEIGHT + Sq.getIValue().getRadius()*2)
			Sq.getIValue().getLifeTimer().setTime(999999);
		Sq.next();
	}
	
	Tr.setBegin();
	while (!Tr.atEnd()) {
		float size = Tr.getIValue().getDim1() + Tr.getIValue().getDim2();
		if (Tr.getIValue().getX() < -size || Tr.getIValue().getX() > WINDOW_WIDTH + size || Tr.getIValue().getY() < -size || Tr.getIValue().getY() > WINDOW_HEIGHT + size) {
			Tr.getIValue().getLifeTimer().setTime(999999);
		}
		Tr.next();
	}
}

void spawnObjects() { //and remove
	defSpw.setBegin();
	while (!defSpw.atEnd()) {
		if (defSpw.getIValue().getObject()->isDead()) {
			switch (defSpw.getIValue().getObjType()) {
				case TYPE_SQUARE: delete (SquareObj*)defSpw.getIValue().getObject();
				break;
				case TYPE_QUAD: delete (QuadObj*)defSpw.getIValue().getObject();
				break;
				case TYPE_TRIANGLE: delete (TriangleObj*)defSpw.getIValue().getObject();
				break;
			}
			defSpw.removeIValue();
			
		} else {
			if (defSpw.getIValue().getObject()->isMaterialised() && defSpw.getIValue().getSpawnTimer().getElapsed() > defSpw.getIValue().getSpawnTime())
				defSpw.getIValue().spawnObject();	
			defSpw.next();
		}
	}
	
	Spw.setBegin();
	while (!Spw.atEnd()) {
		if (Spw.getIValue().getObject()->isDead()) {
			expos = Spw.getIValue().getObject()->getX();
			eypos = Spw.getIValue().getObject()->getY();
			switch (Spw.getIValue().getObjType()) {
				case TYPE_SQUARE: delete (SquareObj*)Spw.getIValue().getObject();
				break;
				case TYPE_QUAD: delete (QuadObj*)Spw.getIValue().getObject();
				break;
				case TYPE_TRIANGLE: delete (TriangleObj*)Spw.getIValue().getObject();
				break;
			}
			Spw.removeIValue();
		} else if (Spw.getIValue().getHealth() <= 0) {
			expos = Spw.getIValue().getObject()->getX();
			eypos = Spw.getIValue().getObject()->getY();
			switch (Spw.getIValue().getObjType()) {
				case TYPE_SQUARE: delete (SquareObj*)Spw.getIValue().getObject();
				break;
				case TYPE_QUAD: delete (QuadObj*)Spw.getIValue().getObject();
				break;
				case TYPE_TRIANGLE: delete (TriangleObj*)Spw.getIValue().getObject();
				break;
			}
			Spw.removeIValue();
		} else {
			if (Spw.getIValue().getObject()->isMaterialised() && (Spw.getIValue().getSpawnTimer().getElapsed() > Spw.getIValue().getSpawnTime()))
				Spw.getIValue().spawnObject();
			Spw.next();
		}
	}
	
	Qu.setBegin();
	while (!Qu.atEnd()) {
		if (Qu.getIValue().isDead()) {
			Qu.removeIValue();
		} else {
			Qu.next();
		}
	}
	
	Sq.setBegin();
	while (!Sq.atEnd()) {
		if (Sq.getIValue().isDead()) {
			Sq.removeIValue();
		} else {
			Sq.next();
		}
	}
	
	Tr.setBegin();
	while (!Tr.atEnd()) {
		if (Tr.getIValue().isDead()) {
			Tr.removeIValue();
		} else {
			Tr.next();
		}
	}
	
	subSpw.setBegin();
	while (!subSpw.atEnd()) {
		if (subSpw.getIValue().getObject()->isDead()) {
			switch (subSpw.getIValue().getObjType()) {
				case TYPE_SQUARE: delete (SquareObj*)subSpw.getIValue().getObject();
				break;
				case TYPE_QUAD: delete (QuadObj*)subSpw.getIValue().getObject();
				break;
				case TYPE_TRIANGLE: delete (TriangleObj*)subSpw.getIValue().getObject();
				break;
			}
			subSpw.removeIValue();
		} else {
			if (subSpw.getIValue().getObject()->isMaterialised() && subSpw.getIValue().getSpawnTimer().getElapsed() > subSpw.getIValue().getSpawnTime())
				subSpw.getIValue().spawnObject();
			subSpw.next();
		}
	}
	
	Ptt.setBegin();
	while (!Ptt.atEnd()) {
		Ptt.getIValue().checkMemberDead();
		if (Ptt.getIValue().isDead()) {
			delete[] Ptt.getIValue().getObjData();
			Ptt.removeIValue();
		} else {
			Ptt.next();
		}
	}
	
	defPtt.setBegin();
	while (!defPtt.atEnd()) {
		defPtt.getIValue().checkMemberDead();
		if (defPtt.getIValue().isDead()) {
			delete[] defPtt.getIValue().getObjData();
			defPtt.removeIValue();
		} else {
			defPtt.next();
		}
	}
	
	Shots.setBegin();
	while (!Shots.atEnd()) {
		if (Shots.getIValue().isDead()) {
			Shots.removeIValue();
		} else {
			Shots.next();
		}
	}
}

void drawObjects() {
	defSpw.setBegin();
	while (!defSpw.atEnd()) {
		defSpw.getIValue().getObject()->redraw();
		glVertexPointer (2, GL_FLOAT, 0, defSpw.getIValue().getObject()->getPointData());
		if (defSpw.getIValue().getObject()->isMaterialised())
			glColor4f(defSpw.getIValue().getObject()->getColorData()[0],defSpw.getIValue().getObject()->getColorData()[1],defSpw.getIValue().getObject()->getColorData()[2],1.0);
		else
			glColor4f(defSpw.getIValue().getObject()->getColorData()[0],defSpw.getIValue().getObject()->getColorData()[1],defSpw.getIValue().getObject()->getColorData()[2],0.3);
		switch (defSpw.getIValue().getObjType()) {
			case TYPE_SQUARE:
			case TYPE_QUAD:
				glDrawArrays(GL_QUADS, 0, 4);
			break;
			case TYPE_TRIANGLE:
				glDrawArrays(GL_TRIANGLES, 0, 3);
			break;
		}
		defSpw.next();
	}
	
	Spw.setBegin();
	while (!Spw.atEnd()) {
		Spw.getIValue().getObject()->redraw();
		glVertexPointer (2, GL_FLOAT, 0, Spw.getIValue().getObject()->getPointData());
		if (Spw.getIValue().isDamaged())
			glColor4f(0.6,0.0,0.0,1.0);
		else if (Spw.getIValue().getObject()->isMaterialised())
			glColor4f(Spw.getIValue().getObject()->getColorData()[0],Spw.getIValue().getObject()->getColorData()[1],Spw.getIValue().getObject()->getColorData()[2],1.0);
		else
			glColor4f(Spw.getIValue().getObject()->getColorData()[0],Spw.getIValue().getObject()->getColorData()[1],Spw.getIValue().getObject()->getColorData()[2],0.3);
		switch (Spw.getIValue().getObjType()) {
			case TYPE_SQUARE:
			case TYPE_QUAD:
				glDrawArrays(GL_QUADS, 0, 4);
			break;
			case TYPE_TRIANGLE:
				glDrawArrays(GL_TRIANGLES, 0, 3);
			break;
		}
		Spw.next();
	}
	
	Qu.setBegin();
	while (!Qu.atEnd()) {
		Qu.getIValue().redraw();
		glVertexPointer (2, GL_FLOAT, 0, Qu.getIValue().getPointData());
		if (Qu.getIValue().isMaterialised())
			glColor4f(Qu.getIValue().getColorData()[0],Qu.getIValue().getColorData()[1],Qu.getIValue().getColorData()[2],1.0);
		else
			glColor4f(Qu.getIValue().getColorData()[0],Qu.getIValue().getColorData()[1],Qu.getIValue().getColorData()[2],0.3);
		glDrawArrays(GL_QUADS, 0, 4);
		Qu.next();
	}
	
	Sq.setBegin();
	while (!Sq.atEnd()) {
		Sq.getIValue().redraw();
		glVertexPointer (2, GL_FLOAT, 0, Sq.getIValue().getPointData());
		if (Sq.getIValue().isMaterialised())
			glColor4f(Sq.getIValue().getColorData()[0],Sq.getIValue().getColorData()[1],Sq.getIValue().getColorData()[2],1.0);
		else
			glColor4f(Sq.getIValue().getColorData()[0],Sq.getIValue().getColorData()[1],Sq.getIValue().getColorData()[2],0.3);
		glDrawArrays(GL_QUADS, 0, 4);
		Sq.next();
	}
	
	Tr.setBegin();
	while (!Tr.atEnd()) {
		Tr.getIValue().redraw();
		glVertexPointer (2, GL_FLOAT, 0, Tr.getIValue().getPointData());
		if (Tr.getIValue().isMaterialised())
			glColor4f(Tr.getIValue().getColorData()[0],Tr.getIValue().getColorData()[1],Tr.getIValue().getColorData()[2],1.0);
		else
			glColor4f(Tr.getIValue().getColorData()[0],Tr.getIValue().getColorData()[1],Tr.getIValue().getColorData()[2],0.3);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		Tr.next();
	}
	
	subSpw.setBegin();
	while (!subSpw.atEnd()) {
		subSpw.getIValue().getObject()->redraw();
		glVertexPointer (2, GL_FLOAT, 0, subSpw.getIValue().getObject()->getPointData());
		if (subSpw.getIValue().getObject()->isMaterialised())
			glColor4f(subSpw.getIValue().getObject()->getColorData()[0],subSpw.getIValue().getObject()->getColorData()[1],subSpw.getIValue().getObject()->getColorData()[2],1.0);
		else
			glColor4f(subSpw.getIValue().getObject()->getColorData()[0],subSpw.getIValue().getObject()->getColorData()[1],subSpw.getIValue().getObject()->getColorData()[2],0.3);
		switch (subSpw.getIValue().getObjType()) {
			case TYPE_SQUARE:
			case TYPE_QUAD:
				glDrawArrays(GL_QUADS, 0, 4);
			break;
			case TYPE_TRIANGLE:
				glDrawArrays(GL_TRIANGLES, 0, 3);
			break;
		}	
		subSpw.next();
	}
	
	Shots.setBegin();
	while (!Shots.atEnd()) {
		Shots.getIValue().redraw();
		glVertexPointer (2, GL_FLOAT, 0, Shots.getIValue().getPointData());
		glColor4f(0,1,1,0.4);
		glDrawArrays(GL_QUADS, 0, 4);
		Shots.next();
	}
	
	if (!Spw.isEmpty() && healthBar.getDim1() >= 1) {
		healthBar.redraw();
		glVertexPointer (2, GL_FLOAT, 0, healthBar.getPointData());
		glColor4f(0.0, 1.0, 0.0, 0.7);
		glDrawArrays(GL_QUADS, 0, 4);
		glLineWidth(1);
		glColor4f(1.0, 1.0, 1.0, 0.7);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}
}

void moveObjects() {
	Ptt.setBegin();
	while (!Ptt.atEnd()) {
		Ptt.getIValue().move();
		Ptt.next();
	}
	defPtt.setBegin();
	while (!defPtt.atEnd()) {
		defPtt.getIValue().move();
		defPtt.next();
	}
	Sq.setBegin();
	while (!Sq.atEnd()) {
		Sq.getIValue().move();
		Sq.next();
	}
	Tr.setBegin();
	while (!Tr.atEnd()) {
		Tr.getIValue().move();
		Tr.next();
	}
	Qu.setBegin();
	while (!Qu.atEnd()) {
		Qu.getIValue().move();
		Qu.next();
	}
	Shots.setBegin();
	while (!Shots.atEnd()) {
		Shots.getIValue().move();
		Shots.next();
	}
	defSpw.setBegin();
	while (!defSpw.atEnd()) {
		defSpw.getIValue().getObject()->move();
		defSpw.next();
	}
	subSpw.setBegin();
	while (!subSpw.atEnd()) {
		subSpw.getIValue().getObject()->move();
		subSpw.next();
	}
	Spw.setBegin();
	while (!Spw.atEnd()) {
		Spw.getIValue().getObject()->move();
		Spw.next();
	}
}

void normalDraw() {
	moveObjects();
	checkDamaged();
	spawnObjects();
	drawObjects();
}

void checkGameOver() {
	Sq.setBegin();
	while ((!Sq.atEnd()) && (!gameover)) {
		if (Sq.getIValue().isMaterialised() && Sq.getIValue().isIn(Point(xpos, ypos))) {
			gameOver();
		}
		Sq.next();
	}
	Tr.setBegin();
	while ((!Tr.atEnd()) && (!gameover)) {
		if (Tr.getIValue().isMaterialised() && Tr.getIValue().isIn(Point(xpos, ypos))) {
			gameOver();
		}
		Tr.next();
	}
	Qu.setBegin();
	while ((!Qu.atEnd()) && (!gameover)) {
		if (Qu.getIValue().isMaterialised() && Qu.getIValue().isIn(Point(xpos, ypos))) {
			gameOver();
		}
		Qu.next();
		}
	defSpw.setBegin();
	while ((!defSpw.atEnd()) && (!gameover)) {
		if (defSpw.getIValue().getObject()->isMaterialised() && defSpw.getIValue().getObject()->isIn(Point(xpos, ypos)) && defSpw.getIValue().getObjType() != TYPE_NULL) {
			gameOver();
		}
		defSpw.next();
	}
	subSpw.setBegin();
	while ((!subSpw.atEnd()) && (!gameover)) {
		if (subSpw.getIValue().getObject()->isMaterialised() && subSpw.getIValue().getObject()->isIn(Point(xpos, ypos))) {
			gameOver();
		}
		subSpw.next();
	}
		Spw.setBegin();
	while ((!Spw.atEnd()) && (!gameover)) {
		if (Spw.getIValue().getObject()->isMaterialised() && Spw.getIValue().getObject()->isIn(Point(xpos, ypos))) {
			gameOver();
		}
		Spw.next();
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
	gamewindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "A N T I (v.Beta)", glfwGetPrimaryMonitor(), NULL);
	
	if (!gamewindow) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	//Set context window yang ingin di-apakan
	glfwMakeContextCurrent(gamewindow);
	
	//Set callback untuk input keyboard
	glfwSetKeyCallback(gamewindow, keyCallback);
	
	
	//Hide cursor
	glfwSetInputMode(gamewindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	
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
	winmark[3] = winmark[2];
	convertStringToLetterData(wintext3, WINDOW_WIDTH/2 - getStringWidth(wintext3, 1)/2, WINDOW_HEIGHT*9/10, 1, wintext, winmark[3], false);
	convertPointData(wintext, 0, winmark[3]);
	
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
	convertPointData(helptext, 0, helpmark[6]);
	
	linesize = 3;
	backmark[0] = 0;
	for (int i = 0; i < 12; i++) {
		backmark[i+1] = backmark[i];
		convertStringToLetterData(back1, 14, (float)i*WINDOW_HEIGHT/11 + 15, linesize, backtext, backmark[i+1], true);
	}
	convertPointData(backtext, 0, backmark[12]);
	
	//Initialize
	xpos = WINDOW_WIDTH/2;
	ypos = WINDOW_HEIGHT/2;
	
	gamemode = ID_MAINMENU;
	
	healthBar.setY(3);
	healthBar.setDim2(4);
	
	while (!glfwWindowShouldClose(gamewindow)) {
		
		//Membersihkan buffer
		if (!gameover || gamemode == ID_GAMEOVER)
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Menghapus segala transformasi
		glLoadIdentity();
		
		//Proses
		if (gamemode > 800 && gamemode < 900) {
			glColor4f(1.0,1.0,1.0,0.1);
			glVertexPointer (2, GL_FLOAT, 0, backtext);
			glLineWidth(3);
			glDrawArrays(GL_LINES, 0, backmark[12]/2);
		}
		
		///Proses mouse
		if (!gameover) {
			glfwGetCursorPos(gamewindow, &newxpos, &newypos);
			float x = newxpos - xpos;
			float y = newypos - ypos;
			float dist = sqrt(x*x + y*y);
			if (dist > 1) {
				float val = atan2(y, x);
				xpos = xpos + dist/5*cos(val);
				ypos = ypos + dist/5*sin(val);
			} else {
				xpos = newxpos;
				ypos = newypos;
			}
		}
		
		///Shooting
		if (!gameover && gamemode > 0 && gamemode < ZONE_LIMIT && spacepressed && delaytime.getElapsed() > SHOT_DELAY) {
			for (int i = 0; i < 3; i++) {
				Shots.add(QuadObj(xpos, ypos-CURSOR_SIZE-3, 20, 7, 2));
				Shots[0].setDirection(75 + 15*i);
				Shots[0].setAngle(75 + 15*i);
				Shots[0].setSpeed(10);
			}
			Shots.add(QuadObj(xpos, ypos-CURSOR_SIZE-3, 20, 7, 2));
			Shots[0].setDirection(90);
			Shots[0].setAngle(90);
			Shots[0].setSpeed(10);
			delaytime.resetTime();
		}
		
		switch (gamemode) {
			case ID_TEST: {
				if (!gameover && Spw.isEmpty()) {
					switchLevel(ID_TEST2);
				} else if (!gameover) {
					if (Spw[0].getObject()->distanceSquaredTo(pointmark) < 10) {
						if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-400) || Spw[0].getObject()->getX() < 400)
							pointmark = Point(randomFloat(Spw[0].getObject()->getX()+100, Spw[0].getObject()->getX()+200), randomFloat(90, 180));
						else
							pointmark = Point(randomFloat(Spw[0].getObject()->getX()-100, Spw[0].getObject()->getX()-200), randomFloat(90, 180));
						Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/280);
						Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
					}
					if (Spw[0].getObject()->isMaterialised() && !hardmode) {
						glBegin(GL_LINES);
							glVertex2f(widthConvert(xpos), heightConvert(ypos));
							glVertex2f(widthConvert(Spw[0].getObject()->getX()), heightConvert(Spw[0].getObject()->getY()));
						glEnd();
					}
					normalDraw();
				}
			} break;
			case ID_TEST2: {
				if (!gameover && Spw.isEmpty()) {
					switchLevel(ID_TEST3);
				} else if (!gameover) {
					if (Spw[0].getObject()->distanceSquaredTo(pointmark) < 10) {
						if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-400) || Spw[0].getObject()->getX() < 400)
							pointmark = Point(randomFloat(Spw[0].getObject()->getX()+100, Spw[0].getObject()->getX()+200), randomFloat(90, 180));
						else
							pointmark = Point(randomFloat(Spw[0].getObject()->getX()-100, Spw[0].getObject()->getX()-200), randomFloat(90, 180));
						Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/280);
						Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
					}
					normalDraw();
				}
			} break;
			case ID_TEST3: {
				if (!gameover && Spw.isEmpty()) {
					switchLevel(ID_TEST4);
				} else if (!gameover) {
					if (Spw[0].getObject()->distanceSquaredTo(pointmark) < 50) {
						if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-550) || Spw[0].getObject()->getX() < 550)
							pointmark = Point(randomFloat(Spw[0].getObject()->getX()+190, Spw[0].getObject()->getX()+300), randomFloat(90, 180));
						else
							pointmark = Point(randomFloat(Spw[0].getObject()->getX()-190, Spw[0].getObject()->getX()-300), randomFloat(90, 180));
						worldtime[0].resetTime();
						Spw[0].getObject()->setSpeed(0);
						Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
						if (Spw[0].getObject()->isMaterialised())
							Spw[0].spawnObject();
					} else if (worldtime[0].getElapsed() > (hardmode ? 0.99 : 1.4)) {
						Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/8);
					}
					normalDraw();
				}
			} break;
			case ID_TEST4: {
				if (!gameover && Spw.isEmpty()) {
					switchLevel(ID_TEST5);
				} else if (!gameover) {
					if (Spw[0].getObject()->distanceSquaredTo(pointmark) < 10) {
						if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-500) || Spw[0].getObject()->getX() < 500)
							pointmark = Point(randomFloat(Spw[0].getObject()->getX()+90, Spw[0].getObject()->getX()+140), randomFloat(90, 180));
						else
							pointmark = Point(randomFloat(Spw[0].getObject()->getX()-90, Spw[0].getObject()->getX()-140), randomFloat(90, 180));
						Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/280);
						Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
					}
					subSpw.setBegin();
					while (!subSpw.atEnd()) {
						if (subSpw.getIValue().getObject()->getSpeed() > 0.1)
							subSpw.getIValue().getObject()->setSpeed(subSpw.getIValue().getObject()->getSpeed() - 0.18);
						subSpw.next();
					}
					Tr.setBegin();
					while (!Tr.atEnd()) {
						if (Tr.getIValue().getColorData()[0] > 0.5)
							Tr.getIValue().setSpeed(Tr.getIValue().getSpeed() + 0.12);
						Tr.next();
					}
					
					if (hardmode && Spw[0].getHealth() < 120 && defSpw.isEmpty()) {
						Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 0.05, 1));
						defSpw.add(Spawner2D(new SquareObj(-100, -100, 220, 999), TYPE_NULL, 0.3, 1, TRIANGLE_5));
					} else if (Spw[0].getHealth() < (hardmode? 240 : 130) && Spw[0].getSpawnTime() > 2) {
						Spw[0].setSpawnTime(1.0);
						Spw[0].getSpawnTimer().resetTime();
						Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 0.05, 1));
					}
					normalDraw();
				}
			} break;
			case ID_TEST5: {
				if (!gameover && Spw.isEmpty()) {
					switchLevel(ID_TEST6);
				} else if (!gameover) {
					if (Spw[0].getObject()->distanceSquaredTo(pointmark) < 10) {
						if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-480) || Spw[0].getObject()->getX() < 480)
							pointmark = Point(randomFloat(Spw[0].getObject()->getX()+90, Spw[0].getObject()->getX()+170), randomFloat(110, 180));
						else
							pointmark = Point(randomFloat(Spw[0].getObject()->getX()-90, Spw[0].getObject()->getX()-170), randomFloat(110, 180));
						Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/280);
						Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
					}
					normalDraw();
				}
			} break;
			case ID_TEST6: {
				if (!gameover && Spw.isEmpty()) {
					switchLevel(ID_FINAL);
				} else if (!gameover) {
					if (defSpw.isEmpty() && worldtime[0].getElapsed() > 2.5)
						Spw[0].spawnObject();
					if (Spw[0].getObject()->distanceSquaredTo(pointmark) < 10 && Spw[0].getObject()->getSpeed() > 1) {
						Spw[0].getObject()->setSpeed(0);
					}
					if (!defPtt.isEmpty()) {
						if (defPtt[0].getSpeed() < 0.2) {
							float ang = -defPtt[0].angleTo(Point(xpos, ypos));
							defPtt[0].rotate(ang - defPtt[0].getDirection());
							defPtt[0].setDirection(ang);
							defPtt[0].setSpeed(14);
						} else {
							defPtt[0].setSpeed(defPtt[0].getSpeed() - 0.18);
						}
					}
					if (hardmode) {
						if (worldtime[0].getElapsed() > 15) {
							if (worldtime[1].getElapsed() > 0.7) {
								for (int i = 0; i < 11; i++) {
									Qu.add(QuadObj(WINDOW_WIDTH/10.0 * i, -100, 80, 18, 5));
									Qu[0].setSpeed(7);
									Qu[0].setAngle(270);
									Qu[0].setDirection(Qu[0].getAngle());
									Qu[0].getColorData()[2] = 0.0;
									Tr.add(TriangleObj(Qu[0].getX() + 54*cos(convertToRadian(Qu[0].getAngle())), Qu[0].getY() - 54*sin(convertToRadian(Qu[0].getAngle())), 42, 30, 5));
									Tr[0].setSpeed(7);
									Tr[0].setAngle(Qu[0].getAngle());
									Tr[0].setDirection(Qu[0].getAngle());
									Tr[0].getColorData()[2] = 0.0;
								}
								worldtime[1].resetTime();
							}
						} else if (worldtime[0].getElapsed() > 12) {
							glColor4f(1.0,1.0,1.0,0.6);
							glBegin(GL_LINES);
								for (int i = 0; i < 11; i++) {
									glVertex2f(2.0/10.0*i - 1.0, -1.0);
									glVertex2f(2.0/10.0*i - 1.0, 1.0);
								}
							glEnd();
						}
					}
					Ptt.setBegin();
					while (!Ptt.atEnd()) {
						if (Ptt.getIValue().getSpeed() < 0.06) {
							float ang = -Ptt.getIValue().angleTo(Point(xpos, ypos));
							Ptt.getIValue().rotate(ang - Ptt.getIValue().getDirection());
							Ptt.getIValue().setDirection(ang);
							Ptt.getIValue().setSpeed(randomFloat(10.0, 15.0));
						} else {
							Ptt.getIValue().setSpeed(Ptt.getIValue().getSpeed() - 0.07);
						}
						Ptt.next();
					}
					normalDraw();
				}
			} break;
			case ID_FINAL: {
				if (!gameover && Spw.isEmpty()) {
					switchLevel(ID_WIN);
				} else if (!gameover) {
					if (Spw[0].getObject()->distanceSquaredTo(pointmark) < 10 && Spw[0].getObject()->getSpeed() > 1) {
						Spw[0].getObject()->setSpeed(0);
					}
					if (hardmode && Spw[0].getHealth() < 250 && Spw[0].getSpawnTime() < 0.01) {
						Sq.removeAll();
						Tr.removeAll();
						Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 999, 999));
						Spw[0].setSpawnTime(0.018);
						Spw[0].setSpawnType(SQUARE_5);
						worldtime[0].resetTime();
						patterner = 0;
					} else if (hardmode && Spw[0].getHealth() < 550 && worldtime[0].getElapsed() > 6.5) {
						Sq.removeAll();
						Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 0.05, 1));
						Spw[0].setSpawnTime(0.008);
						worldtime[0].resetTime();
						patterner = 0;
					}
					if (hardmode && Spw[0].getHealth() < 550) {
						if (worldtime[0].getElapsed() > (Spw[0].getHealth() < 250 ? 4.5 : 6)) {
							float ang = -Spw[0].getObject()->angleTo(Point(xpos, ypos));
							for (int i = 0; i < 7; i++) {
								Tr.add(TriangleObj(Spw[0].getObject()->getX(), Spw[0].getObject()->getY(), 60, 40, 6));
								Tr[0].setSpeed(8);
								Tr[0].setAngle(ang+3*(i-3));
								Tr[0].setDirection(Tr[0].getAngle());
								Tr[0].getColorData()[2] = 0.0;
							}
							worldtime[0].resetTime();
						} else if (worldtime[0].getElapsed() > (Spw[0].getHealth() < 250 ? 2.0 : 3.5)) {
							glColor4f(1.0,1.0,1.0,0.6);
							glBegin(GL_LINES);
								glVertex2f(widthConvert(xpos), heightConvert(ypos));
								glVertex2f(widthConvert(Spw[0].getObject()->getX()), heightConvert(Spw[0].getObject()->getY()));
							glEnd();
						}
					}
					normalDraw();
					deleteOBObjects();
				}
			} break;
			case ID_MAINMENU: 
				glVertexPointer (2, GL_FLOAT, 0, mainmenutext);
				glLineWidth(7);
				glDrawArrays(GL_LINES, 0, mainmenumark[1]/2);
				glLineWidth(3);
				glDrawArrays(GL_LINES, mainmenumark[1]/2, (mainmenumark[5]-mainmenumark[1])/2);
			break;
			case ID_HELP: {
				glVertexPointer (2, GL_FLOAT, 0, helptext);
				glLineWidth(2);
				glDrawArrays(GL_LINES, 0, helpmark[6]/2);
			} break;
			case ID_WIN: {
				glColor4f(0.8,0.8,0.8,1.0);
				glVertexPointer(2, GL_FLOAT, 0, borders);
				glDrawArrays(GL_POLYGON, 0, 4);
				glLineWidth(7);
				glVertexPointer (2, GL_FLOAT, 0, wintext);
				glColor4f(0.0,0.0,0.0,(delaytime.getElapsed() - 1));
				glDrawArrays(GL_LINES, 0, winmark[2]/2);
				glLineWidth(1);
				glDrawArrays(GL_LINES, winmark[2]/2, (winmark[3] - winmark[2])/2);
			} break;
			default: //ID_GAMEOVER
				if (delaytime.getElapsed() > 6) {
					switchLevel(ID_MAINMENU);
				}
				else if (delaytime.getElapsed() > 0.6) { 
					glLineWidth(7);
					glVertexPointer (2, GL_FLOAT, 0, gameovertext);
					glDrawArrays(GL_LINES, 0, gameovermark[1]/2);
				} else if (delaytime.getElapsed() < 0.03) {
					glColor4f(1.0,0.0,0.0,1.0);
					glVertexPointer (2, GL_FLOAT, 0, borders);
					glDrawArrays(GL_QUADS, 0, 4);
				}
		}
		
		///Draw cursor
		if (gamemode != ID_WIN && gamemode != ID_GAMEOVER)
			drawCursor();
		
		///Draw title
		drawTitle();
		
		///Draw borders
		glLineWidth(2);
		glColor4f(1.0,1.0,1.0,1.0);
		glVertexPointer (2, GL_FLOAT, 0, borders);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		
		//Check gameover
		checkGameOver();
		
		if (gameover) { //gameover
			if (delaytime.getElapsed() > 2) {
				switchLevel(ID_GAMEOVER);
				gameover = false;
				spacepressed = false;
				delaytime.resetTime();
			}
		}
		
		//Memindahkan buffer ke tempat yang akan digunakan
		if (!gameover)
			glfwSwapBuffers(gamewindow);		
		glfwPollEvents();
	}
	
	//Destroy window
	glfwDestroyWindow(gamewindow);
	
	//Terminasi GLFW
	glfwTerminate();

	return 0;
}
