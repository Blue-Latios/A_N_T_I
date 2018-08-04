///Compiling shortcut (Linux): g++ -o message message.cpp -lGL -lGLU -lglfw ///
#include <cstdlib>
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
int linesize;
double WINDOW_HEIGHT; //tested on 1000+ pixels
double WINDOW_WIDTH; //tested on 600+ pixels
#define CURSOR_HEIGHT 4
#define CURSOR_WIDTH 4

float sqrtTwo = sqrt(2);

//Game variables:
double xpos, ypos;
double newxpos, newypos;

Time timeeffect;
Time worldtime[5];
int worldn = 0;
Time delaytime;
bool disabled = false;
bool freeze = false;
bool gameover = false;
int checkl = 0;
bool spacepressed = false;
#define SHOT_DELAY 0.1
#define SHOT_DAMAGE 3
int bombcount;

bool storymode = false;
bool autoshoot = false;
int rounds = -1;

//Texts but user too lazy to make a typedef instead lol
float pausetext[1000];
int pausemark[3];
const string pause1 = "PAUSED";
const string pause2 = "Press P to resume";

float gameovertext[1200];
int gameovermark[4];
const string gameover1 = "GAME OVER";

float mainmenutext[3000];
int mainmenumark[6];
const string mainmenu1 = "A N T I";
const string mainmenu2 = "Press S to start NEW game.";
const string mainmenu3 = "Press L to load checkpoint.";
const string mainmenu4 = "Press A to start arcade Beta.";
const string mainmenu5 = "Press H for help. Press Esc to quit.";

float timetext[1500];
int timemark[2];

float wintext[1000];
int winmark[3];
const string wintext1 = "END OF GAME";
const string wintext2 = "Thanks for playing";

float helptext[9600];
int helpmark[10];
const string help1 = "Dodge all obstacles. Move with mouse.";
const string help2 = "Hold spacebar to shoot enemies. Press T to toggle autoshoot.";
const string help3 = "Press X to use bomb. You can carry MAXIMUM 2 bombs at a time.";
const string help4 = "This game may not be completable by you. No need to be frustrated.";
const string help5 = "It is up to you to change your mouse sensitivity.";
const string help6 = "Do not stay too near to the edge. Especially for normal levels.";
const string help7 = "In story mode: Bomb count will replenish after cutscenes.";
const string help8 = "In arcade mode: Press P to pause. One bomb added every 10 rounds.";
const string help9 = "Press anything on the keyboard to return to main menu.";


///Title texts
float title[500];
int titlemark;

const string title_LevelA_str = "Level A";
const string title_Level1_str = "Rapid Shooter";
const string title_Danmaku1_str = "Danmaku Spiral";
const string title_DeathHearts_str = "Deadly Hearts";
const string title_RingShooter_str = "Ring Shooter";
const string title_Drone_str = "Droned Fighter";
const string title_Chaser_str = "Chaser";
const string title_Rippler_str = "Ripples";
const string title_Rain_str = "Bullet Rain";
const string title_LaserBloom_str = "Laser Bloom";
const string title_Radiance_str = "Radiance";
const string title_SpikeCage_str = "Spike Cage";
const string title_IceGod_str = "Ice God";
const string title_EarthGod_str = "Earth God";

///Story texts
#define STORY_LINESIZE 6
float story1text[1000];
int story1mark[3];
const string story1_str1 = "They are after me.";
const string story1_str2 = "I must run or fight.";

float story2text[500];
int story2mark[2];
const string story2_str1 = "They keep coming...";

float story3text[500];
int story3mark[2];
const string story3_str1 = "I am their target.";

float story4text[500];
int story4mark[2];
const string story4_str1 = "I will survive.";

float story5text[500];
int story5mark[2];
const string story5_str1 = "Their attacks get harder...";

float story6text[1000];
int story6mark[3];
const string story6_str1 = "Noone can stop me.";
const string story6_str2 = "I will destroy all.";

float story7text[500];
int story7mark[2];
const string story7_str1 = "When will this end...";

float story8text[500];
int story8mark[2];
const string story8_str1 = "Find the source.";

float story9text[500];
int story9mark[2];
const string story9_str1 = "This must be it...";

float story10text[100];
int story10mark[2];
const string story10_str1 = ". . .";

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

/** Making levels:
 * add into changeID/levelID
 * createLevel()
 * make level in main()
 * 
 * specific levels:
 * drawTitle
 * save zone
 * **/
 
///Stages
#define ID_GAMEOVER -1
#define ID_MAINMENU 0
#define ID_HELP 998
#define ID_WIN 999

//Story
#define ID_STORY1 997
#define ID_STORY2 996
#define ID_STORY3 995
#define ID_STORY4 994
#define ID_STORY5 993
#define ID_STORY6 992
#define ID_STORY7 991
#define ID_STORY8 990
#define ID_STORY9 989
#define ID_STORY10 988

#define ZONE_LIMIT 987
#define ZONE_TEST 986

//Easy
#define ID_ZONE1 1
#define ID_ZONE2 2
#define ID_ZONE3 3
#define ID_SHOOTER1 6
#define ID_ZONE4 8
#define ID_ZONE5 9
#define ID_ZONE6 10
#define ID_ZONE6B 11
#define ID_SHOOTER2 12
#define ID_ZONE7 13
#define ID_SHOOTER3 14
#define ID_SHOOTER5 16

#define ID_RAPIDSHOOTER 801
#define ID_DRONEDFIGHTER 806
#define ID_CHASER 807
#define ID_RIPPLES 808

//Medium
#define ID_ZONE1B 4
#define ID_BULLET1 5
#define ID_SHOOTER4 15
#define ID_ZONE2B 17

#define ID_LEVEL_A 802
#define ID_RINGSHOOTER 804
#define ID_DEADLYHEARTS 805
#define ID_LASERBLOOM 810
#define ID_SPIKECAGE 812

//Hard
#define ID_BULLET2 7
#define ID_SHOOTER6 18

#define ID_DANMAKU1 803
#define ID_RADIANCE 811

//Touhou


#define ID_RAIN 809
#define ID_ICEGOD 813
#define ID_EARTHGOD 814

List<int> changeID;
List<int> levelID;
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
#define PATTERN_DEFAULT 0
#define PATTERN_TWINWAVE1 1
#define PATTERN_ROTATEC 2
#define PATTERN_ROTATEAC 3
#define PATTERN_TWINWAVE2 4

//Pattern helper
void PatternObj::move() {
	setX(getX() + speed*cos(convertToRadian(direction)));
	setY(getY() - speed*sin(convertToRadian(direction)));
	switch (patterntype) {
		case PATTERN_DEFAULT: {
			for (int i = 0; i < n; i++) {
				if (objData[i] != NULL) {
					objData[i]->setX(objData[i]->getX() + speed*cos(convertToRadian(direction)));
					objData[i]->setY(objData[i]->getY() - speed*sin(convertToRadian(direction)));
				}
			}
		} break;
		case PATTERN_TWINWAVE1: {
			for (int i = 0; i < n; i++) {
				if (objData[i] != NULL) {
					objData[i]->setX(objData[i]->getX() + speed*cos(convertToRadian(direction)));
					objData[i]->setY(objData[i]->getY() - speed*sin(convertToRadian(direction)));
					objData[i]->setSpeed(8*(sin(objData[i]->getTimeElapsed() + convertToRadian((float)i*360/n))));
					objData[i]->setAngle(360*objData[i]->getTimeElapsed());
				}
			}
		} break;
		case PATTERN_TWINWAVE2: {
			for (int i = 0; i < n; i++) {
				if (objData[i] != NULL) {
					objData[i]->setX(objData[i]->getX() + speed*cos(convertToRadian(direction)));
					objData[i]->setY(objData[i]->getY() - speed*sin(convertToRadian(direction)));
					objData[i]->setSpeed(8*(cos(7*objData[i]->getTimeElapsed())));
				}
			}
		} break;
		case PATTERN_ROTATEC: {
			rotate(1);
			for (int i = 0; i < n; i++) {
				if (objData[i] != NULL) {
					objData[i]->setX(objData[i]->getX() + speed*cos(convertToRadian(direction)));
					objData[i]->setY(objData[i]->getY() - speed*sin(convertToRadian(direction)));
					objData[i]->setAngle(objData[i]->getDirection());
				}
			}
		} break;
		case PATTERN_ROTATEAC: {
			rotate(-1);
			for (int i = 0; i < n; i++) {
				if (objData[i] != NULL) {
					objData[i]->setX(objData[i]->getX() + speed*cos(convertToRadian(direction)));
					objData[i]->setY(objData[i]->getY() - speed*sin(convertToRadian(direction)));
					objData[i]->setAngle(objData[i]->getDirection());
				}
			}
		} break;
	}
}

///Spawn shots
#define NULL_SHOT 0
#define SQUARE_ANGLESHOT1 1
#define SQUARE_ANGLESHOT2 2
#define SQUARE_ANGLESHOT3 3
#define QUAD_ANGLESHOT1 4
#define SQUARE_RAPIDSHOT1 5 //RapidShooter
#define SQUARE_AIMSHOT1 6
#define SQUARE_AIMSHOT2 7
#define SQUARE_SPECIAL1 8 //Danmaku1
#define SQUARE_RANDOMSHOT1 9 //Danmaku1
#define SQUARE_SPECIAL2 10 //RingShooter
#define SQUARE_SPECIAL3 11 //DeadlyHearts
#define SQUARE_ANGLESHOT4 12
#define QUAD_ANGLESHOT2 13
#define SQUARE_SPECIAL4 14 //DronedFighter
#define SQUARE_RAPIDSHOT2 15 //Chaser
#define SQUARE_ROTATEC 16
#define SQUARE_ROTATEAC 17
#define SQUARE_AIMSHOT3 18
#define QUAD_SPECIAL1 19 //Rain
#define TRIANGLE_SPECIAL1 20 //Rain
#define QUAD_SPECIAL2 21 //LaserBlaze
#define SQUARE_SPECIAL5 22 //Radiance
#define TRIANGLE_SPECIAL2 23 //SpikeCage
#define TRIANGLE_SPECIAL3 24 //IceGod
#define SQUARE_SPECIAL6 25 //IceGod
#define TRIANGLE_RANDOMSHOT1 26 //EarthGod
#define SQUARE_AIMSHOT4 27
#define SQUARE_RANDOMSHOT2 28

#define LBOUND_EXPLOSION 80
#define SQUARE_EXPLODE1 81

void Spawner2D::spawnObject() {
	switch(spawntype) {
		case SQUARE_ANGLESHOT1 : {
			Sq.add(SquareObj(spawner->getX(), spawner->getY(), 40, 7));
			Sq[0].setDirection(spawner->getAngle());
			Sq[0].setSpeed(6);
			Sq[0].setAngle(spawner->getAngle());
			Sq[0].getColorData()[2] = 0.0;
		} break;
		case SQUARE_ANGLESHOT2 : {
			Sq.add(SquareObj(spawner->getX(), spawner->getY(), 60, 7));
			Sq[0].setSpeed(4);
			Sq[0].setAngle(spawner->getAngle());
			Sq[0].setDirection(spawner->getAngle());
			Sq[0].getColorData()[2] = randomFloat(0, 1);
		} break;
		case SQUARE_ANGLESHOT3 : {
			Sq.add(SquareObj(spawner->getX(), spawner->getY(), 50, 6));
			Sq[0].setSpeed(6);
			Sq[0].setAngle(spawner->getAngle());
			Sq[0].setDirection(spawner->getAngle());
			Sq[0].getColorData()[1] = randomFloat(0, 1);
			Sq[0].getColorData()[2] = randomFloat(0, 1);
		} break;
		case SQUARE_SPECIAL2 : {
			for (int i = 0; i < 24; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 20, 13));
				Sq[0].setSpeed(3 + 1.5*cos(convertToRadian((float)i/24 * 360)));
				Sq[0].setAngle((float)i/24*360);
				Sq[0].setDirection(spawner->getAngle() + 40*sin(convertToRadian((float)i/24*360)));
				Sq[0].getColorData()[1] = 0.0;
			}
		} break;
		case SQUARE_ANGLESHOT4 : {
			Ptt.add(PatternObj(spawner->getX(), spawner->getY(), 36, PATTERN_DEFAULT));
			Ptt[0].setSpeed(2);
			Ptt[0].setDirection(spawner->getAngle());
			for (int i = 0; i < 36; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 20, randomFloat(3.0,4.5) - randomFloat(0.0, 2.5)));
				Sq[0].setSpeed(1.5);
				Sq[0].setAngle((float)i*10);
				Sq[0].setDirection((float)i*10);
				Sq[0].getColorData()[0] = 0.5;
				Sq[0].getColorData()[1] = 0.5;
				Ptt[0].add(&Sq[0]);
			}
		} break;
		case SQUARE_SPECIAL5 : {
			for (int i = 0; i < 24; i++) {
				Ptt.add(PatternObj(spawner->getX(), spawner->getY(), 2, PATTERN_TWINWAVE2));
				Ptt[0].setSpeed(6);
				Ptt[0].setDirection((float)i/24 * 360);
				for (int j = 0; j < 2; j++) {
					Sq.add(SquareObj(spawner->getX(), spawner->getY(), 32, 3.5));
					Sq[0].setDirection(Ptt[0].getDirection() - 90 + (float)j*180);
					Sq[0].setAngle(Ptt[0].getDirection());
					Sq[0].getColorData()[0] = 0.8;
					Sq[0].getColorData()[1] = 0.7;
					Sq[0].getColorData()[2] = 0.2;
					Ptt[0].add(&Sq[0]);
				}
			}
		} break;
		case SQUARE_SPECIAL4 : {
			int num = randomInt(17, 18);
			Ptt.add(PatternObj(spawner->getX(), spawner->getY(), num, PATTERN_TWINWAVE1));
			Ptt[0].setSpeed(2);
			Ptt[0].setDirection(spawner->getAngle());
			for (int i = 0; i < num; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 40, 9));
				Sq[0].setDirection(spawner->getAngle() + 90);
				if (i < num/2) {
					Sq[0].getColorData()[0] = 0.4;
				} else {
					Sq[0].getColorData()[2] = 0.4;
				}
				Sq[0].getColorData()[1] = 0.2;
				Ptt[0].add(&Sq[0]);
			}
		} break;
		case SQUARE_SPECIAL1 : {
			for (int i = 0; i < 4; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 30, 6));
				Sq[0].setSpeed(4);
				Sq[0].setAngle(patterner+90*i);
				Sq[0].setDirection(patterner+90*i);
				Sq[0].getColorData()[0] = sin(timeeffect.getElapsed());
				Sq[0].getColorData()[1] = sin(timeeffect.getElapsed()+convertToRadian(120));
				Sq[0].getColorData()[2] = sin(timeeffect.getElapsed()+convertToRadian(240));
			}
		} break;
		case SQUARE_AIMSHOT1 : {
			Sq.add(SquareObj(spawner->getX(), spawner->getY(), 30, 10));
			Sq[0].setSpeed(4);
			Sq[0].setAngle(-spawner->angleTo(Point(xpos, ypos)));
			Sq[0].setDirection(-spawner->angleTo(Point(xpos, ypos)));
			Sq[0].getColorData()[0] = 0.5;
			Sq[0].getColorData()[1] = 0.0;
			Sq[0].getColorData()[2] = 0.5;
		} break;
		case SQUARE_AIMSHOT2 : {
			for (int i = 0; i < 3; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 20, 10));
				Sq[0].setSpeed(4.5);
				Sq[0].setAngle(-spawner->angleTo(Point(xpos, ypos)) + 25*(i - 1));
				Sq[0].setDirection(-spawner->angleTo(Point(xpos, ypos)) + 25*(i - 1));
				Sq[0].getColorData()[0] = 0.5;
				Sq[0].getColorData()[1] = 0.0;
				Sq[0].getColorData()[2] = 0.5;
			}
		} break;
		case SQUARE_AIMSHOT3 : {
			for (int i = 0; i < 5; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 30, 15));
				Sq[0].setSpeed(6-(float)i/2);
				Sq[0].setAngle(-spawner->angleTo(Point(xpos, ypos)));
				Sq[0].setDirection(-spawner->angleTo(Point(xpos, ypos)));
				Sq[0].getColorData()[2] = 0.4;
			}
		} break;
		case SQUARE_AIMSHOT4 : {
			subSpw.add(Spawner2D(new SquareObj(spawner->getX(), spawner->getY(), 90, 8), TYPE_SQUARE, 0.04, 1, SQUARE_RANDOMSHOT2));
			subSpw[0].getObject()->setSpeed(7);
			subSpw[0].getObject()->setAngle(-spawner->angleTo(Point(xpos, ypos)));
			subSpw[0].getObject()->setDirection(-spawner->angleTo(Point(xpos, ypos)));
			subSpw[0].getObject()->getColorData()[1] = 0.0;
		} break;
		case SQUARE_SPECIAL3 : {
			float r = randomFloat(0.6,1);
			float t = randomFloat(0.0,0.5);
			for (int i = 0; i < 30; i++) {
				Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 25, 15, 13));
				float ang = convertToRadian((float)i/30 * 360);
				Tr[0].setSpeed(3 + cos(ang) - abs(sin(ang)));
				Tr[0].setAngle(-spawner->angleTo(Point(xpos, ypos)));
				Tr[0].setDirection(-spawner->angleTo(Point(xpos, ypos)) + 40*sin(convertToRadian((float)i/30*360)));
				Tr[0].getColorData()[0] = r;
				Tr[0].getColorData()[1] = t;
				Tr[0].getColorData()[2] = t;
			}
		} break;
		case SQUARE_RANDOMSHOT1 : {
			Sq.add(SquareObj(spawner->getX(), spawner->getY(), 20, 15));
			Sq[0].setSpeed(2);
			float ang = randomFloat(0, 360);
			Sq[0].setAngle(ang);
			Sq[0].setDirection(ang);
		} break;
		case SQUARE_RANDOMSHOT2 : {
			Sq.add(SquareObj(spawner->getX() + randomFloat(-25, 25), spawner->getY() + randomFloat(-25, 25), 28, 18));
			Sq[0].setSpeed(randomFloat(1.5, 5.0));
			Sq[0].setAngle(spawner->getAngle());
			Sq[0].setDirection(spawner->getAngle());
			Sq[0].getColorData()[0] = 0.8;
			Sq[0].getColorData()[1] = 0.0;
			Sq[0].getColorData()[2] = 0.8;
		} break;
		case TRIANGLE_RANDOMSHOT1 : {
			Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 32, 30, 12));
			Tr[0].setSpeed(randomFloat(3.0, 5.5));
			float ang = randomFloat(0, 360);
			Tr[0].setAngle(ang);
			Tr[0].setDirection(ang);
			Tr[0].getColorData()[1] = 0.4;
			Tr[0].getColorData()[1] = 0.3;
			Tr[0].getColorData()[2] = 0.0;
		} break;
		case QUAD_ANGLESHOT1 : {
			Qu.add(QuadObj(spawner->getX(), spawner->getY(), 100, 20, 6, 0.3));
			Qu[0].setSpeed(4);
			Qu[0].setAngle(spawner->getAngle());
			Qu[0].setDirection(spawner->getAngle());
			Qu[0].getColorData()[0] = 0.0;
			Qu[0].getColorData()[1] = 0.0;
		} break;
		case QUAD_ANGLESHOT2 : {
			Qu.add(QuadObj(spawner->getX(), spawner->getY(), 80, 15, 6, 0.2));
			Qu[0].setSpeed(5);
			Qu[0].setAngle(spawner->getAngle());
			Qu[0].setDirection(spawner->getAngle());
			Qu[0].getColorData()[0] = 0.1;
			Qu[0].getColorData()[1] = 0.7;
		} break;
		case SQUARE_RAPIDSHOT1 : {
			Sq.add(SquareObj(spawner->getX(), spawner->getY(), 30, 6));
			float a = randomFloat(-45,45);
			Sq[0].setSpeed(7);
			Sq[0].setAngle(spawner->getAngle()+a);
			Sq[0].setDirection(spawner->getAngle()+a);
		} break;
		case SQUARE_RAPIDSHOT2 : {
			Sq.add(SquareObj(spawner->getX(), spawner->getY(), 20, 30));
			float a = randomFloat(-15,15);
			Sq[0].setSpeed(-randomFloat(0.8,spawner->getSpeed()));
			Sq[0].setAngle(spawner->getAngle()+a);
			Sq[0].setDirection(spawner->getAngle()+a);
		} break;
		case SQUARE_ROTATEC : {
			Ptt.add(PatternObj(spawner->getX(), spawner->getY(), 24, PATTERN_ROTATEC));
			Ptt[0].setDirection(270);
			float ex = randomFloat(0.0, 360/24);
			for (int i = 0; i < 24; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 40, 9));
				Sq[0].setDirection((float)i/24 * 360 + ex);
				Sq[0].setAngle(Sq[0].getDirection());
				Sq[0].setSpeed(2);
				Sq[0].getColorData()[0] = 0.4;
				Sq[0].getColorData()[2] = 0.2;
				Ptt[0].add(&Sq[0]);
			}
		} break;
		case SQUARE_ROTATEAC : {
			Ptt.add(PatternObj(spawner->getX(), spawner->getY(), 24, PATTERN_ROTATEAC));
			Ptt[0].setDirection(270);
			float ex = randomFloat(0.0, 360/24);
			for (int i = 0; i < 24; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 40, 9));
				Sq[0].setDirection((float)i/24 * 360 + ex);
				Sq[0].setAngle(Sq[0].getDirection());
				Sq[0].setSpeed(2);
				Sq[0].getColorData()[0] = 0.2;
				Sq[0].getColorData()[1] = 0.4;
				Ptt[0].add(&Sq[0]);
			}
		} break;
		case QUAD_SPECIAL1 : {
			float ang = randomFloat(-80.0, -30.0);
			Qu.add(QuadObj(spawner->getX() + randomFloat(0.0, WINDOW_WIDTH/10), spawner->getY(), 25, 7, 12));
			Qu[0].setSpeed(4);
			Qu[0].setAngle(ang);
			Qu[0].setDirection(ang);
			Qu[0].getColorData()[0] = 0.2;
			Qu[0].getColorData()[1] = 0.2;
		} break;
		case QUAD_SPECIAL2 : {
			Ptt.add(PatternObj(spawner->getX(), spawner->getY(), 48, PATTERN_DEFAULT));
			float ex = randomFloat(0.0, 360/42);
			for (int i = 0; i < 42; i++) {
				Qu.add(QuadObj(spawner->getX(), spawner->getY(), 120, 20, 5));
				Qu[0].setDirection((float)i/42 * 360 + ex);
				Qu[0].setAngle(Qu[0].getDirection());
				Qu[0].getColorData()[0] = 0.4;
				Qu[0].getColorData()[2] = 0.6;
				Ptt[0].add(&Qu[0]);
			}
		} break;
		case TRIANGLE_SPECIAL1 : {
			for (int i = 0; i < 13; i++) {
				Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 50, 35, 5));
				Tr[0].setSpeed(7);
				Tr[0].setAngle(270 + 14*(i-6));
				Tr[0].setDirection(270 + 14*(i-6));
				Tr[0].getColorData()[1] = 0.8;
				Tr[0].getColorData()[2] = 0.0;
			}
			for (int i = 0; i < 20; i++) {
				Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 40, 20, 8));
				Tr[0].setSpeed(5.5);
				Tr[0].setAngle(265.5 + 9*(i-9));
				Tr[0].setDirection(265.5 + 9*(i-9));
				Tr[0].getColorData()[1] = 0.8;
				Tr[0].getColorData()[2] = 0.0;
			}
			for (int i = 0; i < 33; i++) {
				Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 30, 14, 12));
				Tr[0].setSpeed(4.25);
				Tr[0].setAngle(270 + 5.5*(i-16));
				Tr[0].setDirection(270 + 5.5*(i-16));
				Tr[0].getColorData()[1] = 0.8;
				Tr[0].getColorData()[2] = 0.0;
			}
			for (int i = 0; i < 46; i++) {
				Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 20, 9, 16));
				Tr[0].setSpeed(3);
				Tr[0].setAngle(268 + 4*(i-22));
				Tr[0].setDirection(268 + 4*(i-22));
				Tr[0].getColorData()[1] = 0.8;
				Tr[0].getColorData()[2] = 0.0;
			}
		} break;
		case TRIANGLE_SPECIAL2 : {
			Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 15, 15, 999));
			float ang = randomFloat(0.0, 360.0);
			Tr[0].setDirection(ang);
			Tr[0].setAngle(ang);
			Tr[0].setSpeed(3);
			Tr[0].getColorData()[0] = 0.7;
			Tr[0].getColorData()[1] = 0.4;
			Tr[0].getColorData()[2] = 0.5;
		} break;
		case TRIANGLE_SPECIAL3 : {
			float spd = randomFloat(1.5, 4.0);
			float ang = randomFloat(0.0, 360/3);
			for(int i = 0; i < 3; i++) { 
				Tr.add(TriangleObj(spawner->getX(), spawner->getY(), 30, 30, 15));
				Tr[0].setDirection(120*i + ang);
				Tr[0].setAngle(120*i + ang);
				Tr[0].setSpeed(spd);
				Tr[0].getColorData()[0] = 0.5;
				Tr[0].getColorData()[1] = 0.4;
				Tr[0].getColorData()[2] = 0.8;
			}
		} break;
		case SQUARE_SPECIAL6 : {
			defSpw.add(Spawner2D(new SquareObj(spawner->getX(), spawner->getY(), 10, 999), TYPE_SQUARE, 0.04, 1, TRIANGLE_SPECIAL3));
			float ang = randomFloat(40, 80);
			if (randomInt(0,1) == 0)
				ang = -ang;
			defSpw[0].getObject()->setAngle(270 + ang);
			defSpw[0].getObject()->setDirection(270 + ang);
			defSpw[0].getObject()->setSpeed(8);
		} break;
		case SQUARE_EXPLODE1 : {
			for (int i = 0; i < 12; i++) {
				Sq.add(SquareObj(spawner->getX(), spawner->getY(), 20, 10));
				Sq[0].setSpeed(4.2);
				Sq[0].setAngle(spawner->getAngle()+(float)i/12*360);
				Sq[0].setDirection(spawner->getAngle()+(float)i/12*360);
			}
		} break;
	}
	spawntimer.resetTime();

}

//Level init
void createLevel() {
	linesize = 2;
	titlemark = 0;
	switch (gamemode) {
		case ID_LEVEL_A : {
			for (int i = 0; i < 10; i++) {
				if (i%2 == 0)
					defSpw.add(Spawner2D(new SquareObj(-400, WINDOW_HEIGHT/9*(i), 150 - 10*(i), 999), TYPE_SQUARE, 999, 1, NULL_SHOT));
				else
					defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH+400, WINDOW_HEIGHT/9*(i), 50 + 10*(i-1), 999), TYPE_SQUARE, 999, 1, NULL_SHOT));
			}
			defSpw.setBegin();
			for (int i = 0; i < 10; i++) {
				defSpw.getIValue().getObject()->setSpeed(5);
				if (i%2 == 0)
					defSpw.getIValue().getObject()->setDirection(0);
				else
					defSpw.getIValue().getObject()->setDirection(180);
				defSpw.next();
			}
			float x = randomFloat(1,3.2);
			for (int i = 0; i < 10; i++) {
				defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/9*(i), -100, 50, 999, 300), TYPE_SQUARE, 999, 1, NULL_SHOT));
			}
			defSpw.setBegin();
			for (int i = 0; i < 10; i++) {
				defSpw.getIValue().getObject()->setSpeed(x);
				defSpw.getIValue().getObject()->setDirection(90);
				defSpw.next();
			}
			
			Spw.add(Spawner2D(new SquareObj(-150, -150, 180, 999), TYPE_SQUARE, 999, 280 + 13*SHOT_DAMAGE, NULL_SHOT));
			Spw[0].getObject()->getColorData()[0] = 0.0;
			Spw[0].getObject()->getColorData()[1] = 0.1;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			
			for (int i = 0; i < 9; i++) {
				defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/9*(i+0.5), -100, 50, 999, 300), TYPE_SQUARE, 999, 1, NULL_SHOT));
			}
			
			float y = randomFloat(1,3.2);
			defSpw.setBegin();
			for (int i = 0; i < 9; i++) {
				defSpw.getIValue().getObject()->setSpeed(y);
				defSpw.getIValue().getObject()->setDirection(270);
				defSpw.next();
			}
			worldn = 1;

			convertStringToLetterData(title_LevelA_str, 10, 10, linesize, title, titlemark, true);	
		} break;
		case ID_ZONE1: {
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -100, 1, 7), TYPE_SQUARE, 0.32, 0, SQUARE_ANGLESHOT2));
			worldn = 2;
		} break;
		case ID_ZONE1B: {
			defSpw.add(Spawner2D(new SquareObj(-100, WINDOW_HEIGHT/2, 1, 7), TYPE_SQUARE, 0.32, 0, SQUARE_ANGLESHOT2));
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH+100, WINDOW_HEIGHT/2, 1, 7), TYPE_SQUARE, 0.32, 0, SQUARE_ANGLESHOT2));
			worldn = 2;
		} break;
		case ID_SHOOTER1: {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -100, 150, 999), TYPE_SQUARE, 0.04, 100, SQUARE_ANGLESHOT1));
			Spw[0].getObject()->setSpeed(4);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.0;
			Spw[0].getObject()->getColorData()[2] = 0.0;
			worldn = 1;
		} break;
		case ID_BULLET1: {
			defSpw.add(Spawner2D(new SquareObj(-100, WINDOW_HEIGHT+100, 1, 5), TYPE_SQUARE, 0.6, 0, SQUARE_ANGLESHOT3));
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH+100, WINDOW_HEIGHT+100, 1, 5), TYPE_SQUARE, 0.6, 0, SQUARE_ANGLESHOT3));
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH+100, -100, 1, 5), TYPE_SQUARE, 0.6, 0, SQUARE_ANGLESHOT3));
			defSpw.add(Spawner2D(new SquareObj(-100, -100, 1, 5), TYPE_SQUARE, 0.6, 0, SQUARE_ANGLESHOT3));
			worldn = 1;
		} break;
		case ID_BULLET2: {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -180, 75, 15, 1), TYPE_SQUARE, 0.01, 180, QUAD_ANGLESHOT1));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.0;
			Spw[0].getObject()->getColorData()[2] = 0.0;
			worldn = 2;
		} break;
		case ID_SHOOTER2: {
			for (int i = 0; i < 3; i++) {
				Spw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/4*(i+1), -180, 150, 130, 10, 1), TYPE_TRIANGLE, 1, 36, QUAD_ANGLESHOT1));
				Spw[0].getObject()->setSpeed(6);
				Spw[0].getObject()->setDirection(270);
				Spw[0].getObject()->getColorData()[0] = 0.0;
				Spw[0].getObject()->getColorData()[2] = 0.4;
			}
			worldn = 1;
		} break;
		case ID_SHOOTER3: {
			float b;
			for (int i = 0; i < 5; i++) {
				b = randomFloat(-250, 0);
				Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/6*(i+1) + randomFloat(-60, 60), -180 + b, 130, 9-(b + 250)/100, 1), TYPE_SQUARE, 2, 8, SQUARE_AIMSHOT2));
				Spw[0].getObject()->setSpeed(7);
				Spw[0].getObject()->setDirection(270);
				Spw[0].getObject()->getColorData()[0] = 0.4;
				Spw[0].getObject()->getColorData()[2] = 0.0;
			}
			worldn = 1;
		} break;
		case ID_SHOOTER4: {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -180, 150, 22.5, 1), TYPE_SQUARE, 0.2, 150, SQUARE_ANGLESHOT4));
			Spw[0].getObject()->setSpeed(5);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.0;
			Spw[0].getObject()->getColorData()[2] = 0.3;
			worldn = 2;
		} break;
		case ID_SHOOTER5: {
			for (int i = 0; i < 3; i++) {
				Spw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/4*(i+1), -180 + 30*abs(1-i), 140, 100, 14, 1), TYPE_TRIANGLE, 1.5, 30, SQUARE_AIMSHOT3));
				Spw[0].getObject()->setSpeed(6);
				Spw[0].getObject()->setDirection(270);
				Spw[0].getObject()->setAngle(270);
				Spw[0].getObject()->getColorData()[0] = 0.2;
				Spw[0].getObject()->getColorData()[2] = 0.2;
			}
			worldn = 2;
		} break;
		case ID_RIPPLES : {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -120, 100, 25, 2), TYPE_SQUARE, 2, 320, SQUARE_ROTATEC));
			Spw[0].getObject()->setSpeed(3);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -120, 1, 25, 2), TYPE_SQUARE, 2, 1, SQUARE_ROTATEAC));
			defSpw[0].getObject()->setSpeed(3);
			defSpw[0].getObject()->setDirection(270);
			defSpw[0].getObject()->getColorData()[0] = 0.0;
			defSpw[0].getObject()->getColorData()[1] = 0.0;
			defSpw[0].getObject()->getColorData()[2] = 0.0;
			worldn = 1;
			
			convertStringToLetterData(title_Rippler_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_RAPIDSHOOTER : {
			Spw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/2, -180, 200, 180, 999, 1), TYPE_TRIANGLE, 1, 300, SQUARE_RAPIDSHOT1));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.0;
			worldn = 1;
			
			convertStringToLetterData(title_Level1_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_DRONEDFIGHTER : {
			Spw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/2, -180, 120, 160, 999, 2), TYPE_TRIANGLE, 2.5, 270, SQUARE_SPECIAL4));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setAngle(270);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.0;
			Spw[0].getObject()->getColorData()[2] = 0.5;
			worldn = 1;
			for (int i = 0; i < 2; i++) {
				defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -180, 70, 999, 2), TYPE_SQUARE, 0.9, 1, QUAD_ANGLESHOT2));
				defSpw[0].getObject()->setSpeed(6);
				defSpw[0].getObject()->setDirection(270);
			}
			convertStringToLetterData(title_Drone_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_RINGSHOOTER : {
			Spw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/2, -180, 160, 150, 999, 1), TYPE_TRIANGLE, 0.5, 360, SQUARE_SPECIAL2));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.0;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			worldn = 1;
			
			convertStringToLetterData(title_RingShooter_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_DEADLYHEARTS : {
			for (int i = 0; i < 2; i++) {
				Spw.add(Spawner2D(new SquareObj(150+(WINDOW_WIDTH-300)*i, -180, 280, 999, 1.5), TYPE_SQUARE, 1.2, 280, SQUARE_SPECIAL3));
				Spw[0].getObject()->setSpeed(4);
				Spw[0].getObject()->setDirection(270);
				Spw[0].getObject()->getColorData()[0] = 0.8;
				Spw[0].getObject()->getColorData()[1] = 0.4;
				Spw[0].getObject()->getColorData()[2] = 0.4;
			}
			worldn = 1;
			
			convertStringToLetterData(title_DeathHearts_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_CHASER : {
			Spw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/2, -200, 200, 150, 999), TYPE_TRIANGLE, 0.05, 250, SQUARE_RAPIDSHOT2));
			Spw[0].getObject()->setSpeed(4);
			Spw[0].getObject()->setDirection(-90);
			Spw[0].getObject()->getColorData()[0] = 0.2;
			Spw[0].getObject()->getColorData()[1] = 0.6;
			Spw[0].getObject()->getColorData()[2] = 0.3;
			worldn = 1;

			convertStringToLetterData(title_Chaser_str, 10, 10, linesize, title, titlemark, true);	
		} break;
		case ID_DANMAKU1 : {
			defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -180, 50, 999, 1), TYPE_SQUARE, 0.02, 1, SQUARE_RANDOMSHOT1));
			defSpw[0].getObject()->setSpeed(6);
			defSpw[0].getObject()->setDirection(270);
			defSpw[0].getObject()->getColorData()[0] = 0.1;
			defSpw[0].getObject()->getColorData()[1] = 0.6;
			defSpw[0].getObject()->getColorData()[2] = 0.5;
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -180, 150, 999, 1), TYPE_SQUARE, 0.02, 480, SQUARE_SPECIAL1));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.1;
			Spw[0].getObject()->getColorData()[1] = 0.6;
			Spw[0].getObject()->getColorData()[2] = 0.5;
			worldn = 1;
			
			convertStringToLetterData(title_Danmaku1_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_RAIN : {
			for (int i = 0; i < 15; i++) {
				defSpw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/10*((float)i-5), -100, 2, 2, 999), TYPE_TRIANGLE, 0.3, 1, QUAD_SPECIAL1));
				defSpw[0].getSpawnTimer().setTime(randomFloat(0.0, 250.0));
			}
			Spw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/2, -180, 200, 180, 999, 1), TYPE_TRIANGLE, 15, 540, TRIANGLE_SPECIAL1));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->setAngle(270);
			Spw[0].getObject()->getColorData()[0] = 0.1;
			Spw[0].getObject()->getColorData()[1] = 0.0;
			Spw[0].getObject()->getColorData()[2] = 0.6;
			worldn = 1;
			
			Sq.add(SquareObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 2000, 0.5, 2));
			Sq[0].getColorData()[0] = 0.0;
			Sq[0].getColorData()[1] = 0.0;
			
			convertStringToLetterData(title_Rain_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_LASERBLOOM : {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -240, 240, 999, 1.5), TYPE_SQUARE, 0.5, 420, QUAD_SPECIAL2));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->setAngle(270);
			Spw[0].getObject()->getColorData()[0] = 0.1;
			Spw[0].getObject()->getColorData()[1] = 0.5;
			Spw[0].getObject()->getColorData()[2] = 0.4;
			worldn = 1;
			
			convertStringToLetterData(title_LaserBloom_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_RADIANCE : {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -240, 200, 999, 1.5), TYPE_SQUARE, 10, 350, SQUARE_SPECIAL5));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.1;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.1;
			worldn = 2;
			
			convertStringToLetterData(title_Radiance_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_SPIKECAGE : {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -240, 120, 999, 1.5), TYPE_SQUARE, 60, 480, TRIANGLE_SPECIAL2));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->setAngle(45);
			Spw[0].getObject()->getColorData()[0] = 1.0;
			Spw[0].getObject()->getColorData()[1] = 0.6;
			Spw[0].getObject()->getColorData()[2] = 0.3;
			Qu.add(QuadObj(0, WINDOW_HEIGHT/2, 20, WINDOW_HEIGHT, 998, 999));
			Qu.add(QuadObj(WINDOW_WIDTH, WINDOW_HEIGHT/2, 20, WINDOW_HEIGHT, 998, 999));
			Qu.add(QuadObj(WINDOW_WIDTH/2, 0, WINDOW_WIDTH, 20, 998, 999));
			Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT, WINDOW_WIDTH, 20, 998, 999));
			Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 0.5, 1));
			Qu.setBegin();
			for (int i = 0; i < Qu.size(); i++) {
				Qu.getIValue().getColorData()[0] = 0.5;
				Qu.getIValue().getColorData()[1] = 0.0;
				Qu.getIValue().getColorData()[2] = 0.0;
				Qu.next();
			}
			worldn = 1;
			
			convertStringToLetterData(title_SpikeCage_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_ICEGOD : {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -240, 160, 999, 1.0), TYPE_SQUARE, 999, 540 + 13*SHOT_DAMAGE, SQUARE_SPECIAL6));
			Spw[0].getObject()->setAngle(45);
			Spw[0].getObject()->getColorData()[0] = 0.2;
			Spw[0].getObject()->getColorData()[1] = 0.4;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			
			Ptt.add(PatternObj(WINDOW_WIDTH/2, -240, 5, PATTERN_DEFAULT));
			Ptt[0].setSpeed(6);
			Ptt[0].setDirection(270);
			Ptt[0].add(Spw[0].getObject());
			for (int i = 0; i < 4; i++) {
				defSpw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2 + 70*cos(convertToRadian(90*i)), -240 - 70*sin(convertToRadian(90*i)), 45, 999, 1.0), TYPE_SQUARE, 999, 1, NULL_SHOT));
				defSpw[0].getObject()->setAngle(45);
				defSpw[0].getObject()->getColorData()[0] = 0.0;
				Ptt[0].add(defSpw[0].getObject());
			}
			
			Spw[0].getSpawnTimer().setTime(999000);
			
			worldn = 2;
			
			convertStringToLetterData(title_IceGod_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_EARTHGOD : {
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -240, 160, 999, 1.0), TYPE_SQUARE, 999, 560 + 13*SHOT_DAMAGE, SQUARE_SPECIAL6));
			Spw[0].getObject()->setAngle(45);
			Spw[0].getObject()->getColorData()[0] = 0.3;
			Spw[0].getObject()->getColorData()[1] = 0.2;
			Spw[0].getObject()->getColorData()[2] = 0.1;
			
			Ptt.add(PatternObj(WINDOW_WIDTH/2, -240, 5, PATTERN_DEFAULT));
			Ptt[0].setSpeed(6);
			Ptt[0].setDirection(270);
			Ptt[0].add(Spw[0].getObject());
			for (int i = 0; i < 4; i++) {
				defSpw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/2 + 60*cos(convertToRadian(90*i + 45)), -240 - 60*sin(convertToRadian(90*i + 45)), 65, 60, 999, 1.0), TYPE_TRIANGLE, 0.03, 1, TRIANGLE_RANDOMSHOT1));
				defSpw[0].getObject()->setAngle(90*i + 45);
				defSpw[0].getObject()->getColorData()[0] = 0.4;
				defSpw[0].getObject()->getColorData()[1] = 0.3;
				Ptt[0].add(defSpw[0].getObject());
			}
			worldn = 1;
			
			convertStringToLetterData(title_EarthGod_str, 10, 10, linesize, title, titlemark, true);
		} break;
		case ID_SHOOTER6 : { ///Edit pre-available enemies here
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/3, -240, 180, 21, 0.9), TYPE_SQUARE, 1, 70, SQUARE_AIMSHOT4));
			Spw[0].getObject()->setDirection(270);
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH*2/3, -240, 180, 21, 0.9), TYPE_SQUARE, 1, 70, SQUARE_AIMSHOT4));
			Spw[0].getObject()->setDirection(270);
			Spw.add(Spawner2D(new SquareObj(-240, 180, 180, 21, 0.9), TYPE_SQUARE, 1, 70, SQUARE_AIMSHOT4));
			Spw[0].getObject()->setDirection(0);
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH + 240, 180, 180, 21, 0.9), TYPE_SQUARE, 1, 70, SQUARE_AIMSHOT4));
			Spw[0].getObject()->setDirection(180);
			Spw.setBegin();
			for (int i = 0; i < Spw.size(); i++) {
				Spw.getIValue().getObject()->setSpeed(6);
				Spw.getIValue().getObject()->getColorData()[0] = 0.1;
				Spw.getIValue().getObject()->getColorData()[2] = 0.0;
				Spw.next();
			}
			worldn = 2;
		} break;
		case ZONE_TEST : { ///Edit pre-available enemies here
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -240, 200, 999, 1.5), TYPE_SQUARE, 1, 360, SQUARE_AIMSHOT4));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.7;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			worldn = 1;
			
			convertStringToLetterData("Zone Test", 10, 10, linesize, title, titlemark, true);
		} break;
		/**case ZONE_TEST : { ///Edit pre-available enemies here
			Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH/2, -240, 200, 999, 1.5), TYPE_SQUARE, 1, 360, SQUARE_AIMSHOT4));
			Spw[0].getObject()->setSpeed(6);
			Spw[0].getObject()->setDirection(270);
			Spw[0].getObject()->getColorData()[0] = 0.7;
			Spw[0].getObject()->getColorData()[1] = 0.7;
			Spw[0].getObject()->getColorData()[2] = 0.7;
			worldn = 1;
			
			convertStringToLetterData("Zone Test", 10, 10, linesize, title, titlemark, true);
		} break; **/
		default:
			worldn = 1;
	}
	convertPointData(title, 0, titlemark);
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
			Tr.setBegin();
			for (int i = 0; i < Tr.size(); i++) {
				Tr.getIValue().markTime();
				Tr.next();
			}
			Qu.setBegin();
			for (int i = 0; i < Qu.size(); i++) {
				Qu.getIValue().markTime();
				Qu.next();
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
			subSpw.setBegin();
			for (int i = 0; i < subSpw.size(); i++) {
				subSpw.getIValue().getSpawnTimer().markTime();
				subSpw.getIValue().getObject()->markTime();
				subSpw.next();
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
	Tr.setBegin();
	for (int i = 0; i < Tr.size(); i++) {
		Tr.getIValue().continueTime();
		Tr.next();
	}
	Qu.setBegin();
	for (int i = 0; i < Qu.size(); i++) {
		Qu.getIValue().continueTime();
		Qu.next();
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
	subSpw.setBegin();
	for (int i = 0; i < subSpw.size(); i++) {
		subSpw.getIValue().getSpawnTimer().continueTime();
		subSpw.getIValue().getObject()->continueTime();
		subSpw.next();
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
	glVertexPointer (2, GL_FLOAT, 0, title);
	glDrawArrays(GL_LINES, 0, titlemark/2);
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
		if (rounds > data) {
			RecordData.close();
			Record.open("highscore.txt");
			Record << "World: ";
			switch (gamemode) {
				case ID_LEVEL_A :
					Record << "Level_A";
				break;
				case ID_RAPIDSHOOTER :
					Record << "Rapid_Shooter";
				break;
				case ID_DANMAKU1 :
					Record << "Danmaku_Spiral";
				break;
				case ID_RINGSHOOTER :
					Record << "Ring_Shooter";
				break;
				case ID_DEADLYHEARTS :
					Record << "Death_Hearts";
				break;
				case ID_DRONEDFIGHTER :
					Record << "Droned_Fighter";
				break;
				case ID_CHASER :
					Record << "Chaser";
				break;
				case ID_RIPPLES :
					Record << "Ripples";
				break;
				case ID_RAIN :
					Record << "Bullet_Rain";
				break;
				case ID_LASERBLOOM :
					Record << "Laser_Bloom";
				break;
				case ID_RADIANCE :
					Record << "Radiance";
				break;
				case ID_SPIKECAGE :
					Record << "Spike_Cage";
				break;
				case ID_ICEGOD :
					Record << "Ice_God";
				break;
				case ID_EARTHGOD :
					Record << "Earth_God";
				break;
				default:
					Record << "Zone";
			}
			Record << endl;
			Record << "Rounds completed: " << rounds << endl;
			Record << "Date: " << getNowTime() << endl;
			Record.close();
		}
		Record.open("record.txt", ios::out | ios::app);
		Record << "World: ";
		switch (gamemode) {
			case ID_LEVEL_A :
				Record << title_LevelA_str;
			break;
			case ID_RAPIDSHOOTER :
				Record << title_Level1_str;
			break;
			case ID_DANMAKU1 :
				Record << title_Danmaku1_str;
			break;
			case ID_RINGSHOOTER :
				Record << title_RingShooter_str;
			break;
			case ID_DEADLYHEARTS :
				Record << title_DeathHearts_str;
			break;
			case ID_DRONEDFIGHTER :
				Record << title_Drone_str;
			break;
			case ID_CHASER :
				Record << title_Chaser_str;
			break;
			case ID_RIPPLES :
				Record << title_Rippler_str;
			break;
			case ID_RAIN :
				Record << title_Rain_str;
			break;
			case ID_LASERBLOOM :
				Record << title_LaserBloom_str;
			break;
			case ID_RADIANCE :
				Record << title_Radiance_str;
			break;
			case ID_SPIKECAGE :
				Record << title_SpikeCage_str;
			break;
			case ID_ICEGOD :
				Record << title_IceGod_str;
			break;
			case ID_EARTHGOD :
				Record << title_EarthGod_str;
			break;
			default:
				Record << "Zone";
		}
		Record << endl;
		Record << "Rounds completed: " << rounds << endl;
		Record << "Survival time: " << timescore << endl;
		Record << "Bombs remaining: " << bombcount << endl;
		Record << "Date: " << getNowTime() << endl << endl;
		Record.close();
		
		linesize = 4;
		gameovermark[2] = gameovermark[1];
		timeeffect.continueTime();
		string str = "Time: " + timeeffect.toString();
		convertStringToLetterData(str, WINDOW_WIDTH/2 - getStringWidth(str, linesize)/2, WINDOW_HEIGHT*5/7, linesize, gameovertext, gameovermark[2], true);
		string str2 = "Rounds completed: " + to_string(rounds);
		gameovermark[3] = gameovermark[2];
		convertStringToLetterData(str2, WINDOW_WIDTH/2 - getStringWidth(str2, linesize)/2, WINDOW_HEIGHT*6/7, linesize, gameovertext, gameovermark[3], true);
		convertPointData(gameovertext, gameovermark[1], gameovermark[3]);
	}
	rounds = -1;
	gameover = true;
	delaytime.resetTime();
}

//Fungsi clear level
void clearLevel(int gmode) {
	pointmark = Point(0,0);
	if (changeID.find(gmode) == -1 || changeID.find(gamemode) == -1) {
		Sq.removeAll();
		Tr.removeAll();
		Qu.removeAll();
		subSpw.removeAll();
		Ptt.removeAll();
		if (gmode <= 0 || gmode > ZONE_LIMIT)
			Shots.removeAll();
	}
	defSpw.removeAll();
	Spw.removeAll();
	worldn = 0;
	glColor4f(1.0,1.0,1.0,1.0);
	glVertexPointer (2, GL_FLOAT, 0, borders);
	glDrawArrays(GL_QUADS, 0, 4);
}

//Bomb effect, mirip clear level
void bomb() {
	Sq.setBegin();
	for (int i = 0; i < Sq.size(); i++) {
		if (Sq.getIValue().isMaterialised())
			Sq.getIValue().getLifeTimer().setTime(999000);
		Sq.next();
	}
	
	Tr.setBegin();
	for (int i = 0; i < Tr.size(); i++) {
		if (Tr.getIValue().isMaterialised())
			Tr.getIValue().getLifeTimer().setTime(999000);
		Tr.next();
	}
	
	Qu.setBegin();
	for (int i = 0; i < Qu.size(); i++) {
		if (Qu.getIValue().isMaterialised())
			Qu.getIValue().getLifeTimer().setTime(999000);
		Qu.next();
	}
	subSpw.setBegin();
	for (int i = 0; i < subSpw.size(); i++) {
		if (subSpw.getIValue().getObject()->isMaterialised())
			subSpw.getIValue().getObject()->getLifeTimer().setTime(999000);
		subSpw.next();
	}
	Spw.setBegin();
	for (int i = 0; i < Spw.size(); i++) {
		if (Spw.getIValue().getObject()->isMaterialised())
			Spw.getIValue().damage(SHOT_DAMAGE);
		Spw.next();
	}
	Sq.add(SquareObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 2000, 0.05, 1));
	Sq[0].getColorData()[1] = 0.0;
	Sq[0].getColorData()[2] = 0.0;
}

//Switch levels
void switchLevel(int gmode) {
	clearLevel(gmode);
	gamemode = gmode;
	createLevel();
	patterner = 0;
	if ((gamemode <= 0) || (gamemode > ZONE_LIMIT)) {
		autoshoot = false;
		bombcount = 2;
	}
	if (gmode > ZONE_LIMIT)
		delaytime.resetTime();
	if (storymode) {
		bool hitcheck = true;
		switch(gamemode) {
			case ID_STORY2:
			case ID_STORY3:
			case ID_STORY4:
			case ID_STORY5:
			case ID_STORY6:
			case ID_STORY7:
			case ID_STORY8:
			case ID_STORY9:
			case ID_STORY10:
				checkl = gamemode;
			break;
			default:
				hitcheck = false;
		}
		if (hitcheck) {
			ofstream saveFile;
			saveFile.open("savedata");
			saveFile << checkl << endl;
			saveFile.close();
		}
	} else if (changeID.find(gmode) != -1 || levelID.find(gmode) != -1) {
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
					case GLFW_KEY_S : {
						storymode = true;
						switchLevel(ID_STORY1);
						ofstream saveFile;
						saveFile.open("savedata");
						checkl = ID_STORY1;
						saveFile << checkl << endl;
						saveFile.close();
					} break;
					case GLFW_KEY_L :
						storymode = true;
						switchLevel(checkl);
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
			case ID_HELP :
				switchLevel(ID_MAINMENU);
			break;
			case ID_GAMEOVER :
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
				if (key == GLFW_KEY_T) {
					autoshoot = !autoshoot;
				} else if (gamemode < ZONE_LIMIT && key == GLFW_KEY_X) {
					if (bombcount > 0) {
						bomb();
						bombcount--;
					}
				}
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
	if (!entered && !disabled && !storymode && !gameover && (gamemode > 0) && (gamemode <= ZONE_LIMIT)) { //Strict limited
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

void checkDamaged() {
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
}

void drawObjects() {
	///Removal check then draw
	int i = 0;
	defSpw.setBegin();
	while (i < defSpw.size()) {
		if (defSpw.getIValue().getObject()->isDead()) {
			if (defSpw.getIValue().getSpawnType() > LBOUND_EXPLOSION)
				defSpw.getIValue().spawnObject();
			defSpw.removeAt(i);
		} else {
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
			if (defSpw.getIValue().getObject()->isMaterialised() && defSpw.getIValue().getSpawnTimer().getElapsed() > defSpw.getIValue().getSpawnTime())
				defSpw.getIValue().spawnObject();	
			defSpw.next();
			i++;
		}
	}
	
	i = 0;
	Spw.setBegin();
	while (i < Spw.size()) {
		if (Spw.getIValue().getObject()->isDead()) {
			Spw.removeAt(i);
		} else if (Spw.getIValue().getHealth() <= 0) {
			if (Spw.getIValue().getSpawnType() > LBOUND_EXPLOSION)
				Spw.getIValue().spawnObject();
			Spw.removeAt(i);
		} else {
			Spw.getIValue().getObject()->redraw();
			glVertexPointer (2, GL_FLOAT, 0, Spw.getIValue().getObject()->getPointData());
			if (Spw.getIValue().isDamaged()) {
				glColor4f(0.6,0.0,0.0,1.0);
			}
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
			if (Spw.getIValue().getObject()->isMaterialised() && (Spw.getIValue().getSpawnTimer().getElapsed() > Spw.getIValue().getSpawnTime()))
				Spw.getIValue().spawnObject();
			Spw.next();
			i++;
		}
	}
	
	i = 0;
	Qu.setBegin();
	while (i < Qu.size()) {
		if (Qu.getIValue().isDead()) {
			Qu.removeAt(i);
		} else {
			Qu.getIValue().redraw();
			glVertexPointer (2, GL_FLOAT, 0, Qu.getIValue().getPointData());
			if (Qu.getIValue().isMaterialised())
				glColor4f(Qu.getIValue().getColorData()[0],Qu.getIValue().getColorData()[1],Qu.getIValue().getColorData()[2],1.0);
			else
				glColor4f(Qu.getIValue().getColorData()[0],Qu.getIValue().getColorData()[1],Qu.getIValue().getColorData()[2],0.3);
			glDrawArrays(GL_QUADS, 0, 4);
			Qu.next();
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
				glColor4f(Sq.getIValue().getColorData()[0],Sq.getIValue().getColorData()[1],Sq.getIValue().getColorData()[2],0.3);
			glDrawArrays(GL_QUADS, 0, 4);
			Sq.next();
			i++;
		}
	}
	
	i = 0;
	Tr.setBegin();
	while (i < Tr.size()) {
		if (Tr.getIValue().isDead()) {
			Tr.removeAt(i);
		} else {
			Tr.getIValue().redraw();
			glVertexPointer (2, GL_FLOAT, 0, Tr.getIValue().getPointData());
			if (Tr.getIValue().isMaterialised())
				glColor4f(Tr.getIValue().getColorData()[0],Tr.getIValue().getColorData()[1],Tr.getIValue().getColorData()[2],1.0);
			else
				glColor4f(Tr.getIValue().getColorData()[0],Tr.getIValue().getColorData()[1],Tr.getIValue().getColorData()[2],0.3);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			Tr.next();
			i++;
		}
	}
	
	subSpw.setBegin();
	while (i < subSpw.size()) {
		if (subSpw.getIValue().getObject()->isDead()) {
			if (subSpw.getIValue().getSpawnType() > LBOUND_EXPLOSION)
				subSpw.getIValue().spawnObject();
			subSpw.removeAt(i);
		} else {
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
			if (subSpw.getIValue().getObject()->isMaterialised() && subSpw.getIValue().getSpawnTimer().getElapsed() > subSpw.getIValue().getSpawnTime())
				subSpw.getIValue().spawnObject();	
			subSpw.next();
			i++;
		}
	}
	
	i = 0;
	Ptt.setBegin();
	while (i < Ptt.size()) {
		Ptt.getIValue().checkMemberDead();
		if (Ptt.getIValue().isDead())
			Ptt.removeAt(i);
		else {
			Ptt.next();
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
	Ptt.setBegin();
	for (int i = 0; i < Ptt.size(); i++) {
		Ptt.getIValue().move();
		Ptt.next();
	}
	Sq.setBegin();
	for (int i = 0; i < Sq.size(); i++) {
		Sq.getIValue().move();
		Sq.next();
	}
	Tr.setBegin();
	for (int i = 0; i < Tr.size(); i++) {
		Tr.getIValue().move();
		Tr.next();
	}
	Qu.setBegin();
	for (int i = 0; i < Qu.size(); i++) {
		Qu.getIValue().move();
		Qu.next();
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
	subSpw.setBegin();
	for (int i = 0; i < subSpw.size(); i++) {
		subSpw.getIValue().getObject()->move();
		subSpw.next();
	}
	Spw.setBegin();
	for (int i = 0; i < Spw.size(); i++) {
		Spw.getIValue().getObject()->move();
		Spw.next();
	}
}

void switchArcade() {
	if (rounds%10 == 8) {
		int x;
		if (rounds < 9) //switcher for later use
			x = randomInt(0,levelID.size()-1);
		else
			x = randomInt(0,levelID.size()-1);
		switchLevel(levelID[x]);
	} else {
		int x;
		do {
			if (rounds < 9) //switcher for later use
				x = randomInt(0,changeID.size()-1);
			else
				x = randomInt(0,changeID.size()-1);
		} while (changeID[x] == gamemode);
		if (rounds%10 == 9 && bombcount < 2)
			bombcount++;
		switchLevel(changeID[x]);
	}
}

void normalDraw() {
	checkDamaged();
	drawObjects();
	drawCursor();
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
	helpmark[8] = helpmark[7];
	convertStringToLetterData(help8, 30, WINDOW_HEIGHT*8/10, linesize, helptext, helpmark[8], true);
	helpmark[9] = helpmark[8];
	convertStringToLetterData(help9, 30, WINDOW_HEIGHT*9/10, linesize, helptext, helpmark[9], true);
	convertPointData(helptext, 0, helpmark[9]);
	
	//Story texts
	linesize = STORY_LINESIZE;
	
	story1mark[0] = 0;
	story1mark[1] = story1mark[0];
	convertStringToLetterData(story1_str1, WINDOW_WIDTH/2 - getStringWidth(story1_str1, linesize)/2, WINDOW_HEIGHT*2/5, linesize, story1text, story1mark[1], true);
	story1mark[2] = story1mark[1];
	convertStringToLetterData(story1_str2, WINDOW_WIDTH/2 - getStringWidth(story1_str2, linesize)/2, WINDOW_HEIGHT*3/5, linesize, story1text, story1mark[2], true);
	convertPointData(story1text, 0, story1mark[2]);
	
	story2mark[0] = 0;
	story2mark[1] = story2mark[0];
	convertStringToLetterData(story2_str1, WINDOW_WIDTH/2 - getStringWidth(story2_str1, linesize)/2, WINDOW_HEIGHT/2, linesize, story2text, story2mark[1], true);
	convertPointData(story2text, 0, story2mark[1]);
	
	story3mark[0] = 0;
	story3mark[1] = story3mark[0];
	convertStringToLetterData(story3_str1, WINDOW_WIDTH/2 - getStringWidth(story3_str1, linesize)/2, WINDOW_HEIGHT/2, linesize, story3text, story3mark[1], true);
	convertPointData(story3text, 0, story3mark[1]);
	
	story4mark[0] = 0;
	story4mark[1] = story4mark[0];
	convertStringToLetterData(story4_str1, WINDOW_WIDTH/2 - getStringWidth(story4_str1, linesize)/2, WINDOW_HEIGHT/2, linesize, story4text, story4mark[1], true);
	convertPointData(story4text, 0, story4mark[1]);
	
	story5mark[0] = 0;
	story5mark[1] = story5mark[0];
	convertStringToLetterData(story5_str1, WINDOW_WIDTH/2 - getStringWidth(story5_str1, linesize)/2, WINDOW_HEIGHT/2, linesize, story5text, story5mark[1], true);
	convertPointData(story5text, 0, story5mark[1]);
	
	story6mark[0] = 0;
	story6mark[1] = story6mark[0];
	convertStringToLetterData(story6_str1, WINDOW_WIDTH/2 - getStringWidth(story6_str1, linesize)/2, WINDOW_HEIGHT*2/5, linesize, story6text, story6mark[1], true);
	story6mark[2] = story6mark[1];
	convertStringToLetterData(story6_str2, WINDOW_WIDTH/2 - getStringWidth(story6_str2, linesize)/2, WINDOW_HEIGHT*3/5, linesize, story6text, story6mark[2], true);
	convertPointData(story6text, 0, story6mark[2]);
	
	story7mark[0] = 0;
	story7mark[1] = story7mark[0];
	convertStringToLetterData(story7_str1, WINDOW_WIDTH/2 - getStringWidth(story7_str1, linesize)/2, WINDOW_HEIGHT/2, linesize, story7text, story7mark[1], true);
	convertPointData(story7text, 0, story7mark[1]);
	
	story8mark[0] = 0;
	story8mark[1] = story8mark[0];
	convertStringToLetterData(story8_str1, WINDOW_WIDTH/2 - getStringWidth(story8_str1, linesize)/2, WINDOW_HEIGHT/2, linesize, story8text, story8mark[1], true);
	convertPointData(story8text, 0, story8mark[1]);
	
	story9mark[0] = 0;
	story9mark[1] = story9mark[0];
	convertStringToLetterData(story9_str1, WINDOW_WIDTH/2 - getStringWidth(story9_str1, linesize)/2, WINDOW_HEIGHT/2, linesize, story9text, story9mark[1], true);
	convertPointData(story9text, 0, story9mark[1]);
	
	story10mark[0] = 0;
	story10mark[1] = story10mark[0];
	convertStringToLetterData(story10_str1, WINDOW_WIDTH/2 - getStringWidth(story10_str1, linesize)/2, WINDOW_HEIGHT/2, linesize, story10text, story10mark[1], true);
	convertPointData(story10text, 0, story10mark[1]);
	
	//Initialize
	int iter;
	xpos = WINDOW_WIDTH/2;
	ypos = WINDOW_HEIGHT/2;
	
	int zeasy = 0, znormal = 0, zhard = 0, ztouhou = 0;
	int leasy = 0, lnormal = 0, lhard = 0, ltouhou = 0;
	
	changeID.add(ID_ZONE1); zeasy++;
	changeID.add(ID_ZONE2); zeasy++;
	changeID.add(ID_SHOOTER1); zeasy++;
	changeID.add(ID_ZONE3); zeasy++;
	changeID.add(ID_ZONE4); zeasy++;
	changeID.add(ID_ZONE5); zeasy++;
	//changeID.add(ID_ZONE6); story only
	changeID.add(ID_ZONE6B); zeasy++;
	changeID.add(ID_SHOOTER2); zeasy++;
	changeID.add(ID_ZONE7); zeasy++;
	changeID.add(ID_SHOOTER3); zeasy++;
	changeID.add(ID_SHOOTER5); zeasy++;
	
	levelID.add(ID_RAPIDSHOOTER); leasy++;
	levelID.add(ID_DRONEDFIGHTER); leasy++;
	levelID.add(ID_CHASER); leasy++;
	
	changeID.add(ID_BULLET1); znormal++;
	changeID.add(ID_ZONE1B); znormal++;
	changeID.add(ID_ZONE2B); znormal++;
	changeID.add(ID_SHOOTER4); znormal++;
	
	levelID.add(ID_LEVEL_A); lnormal++;
	levelID.add(ID_RINGSHOOTER); lnormal++;
	levelID.add(ID_DEADLYHEARTS); lnormal++;
	levelID.add(ID_RIPPLES); lnormal++;
	levelID.add(ID_LASERBLOOM); lnormal++;
	levelID.add(ID_SPIKECAGE); lnormal++;
	
	changeID.add(ID_BULLET2); zhard++;
	
	levelID.add(ID_DANMAKU1); lhard++;
	levelID.add(ID_RADIANCE); lhard++;
	
	levelID.add(ID_RAIN); ltouhou++;
	levelID.add(ID_ICEGOD); ltouhou++;
	levelID.add(ID_EARTHGOD); ltouhou++;
	
	//ignore this
	ltouhou = ltouhou + ztouhou + zhard + znormal + zeasy + lhard + lnormal + leasy;
	
	ifstream loadFile;
	loadFile.open("savedata");
	loadFile >> checkl;
	loadFile.close();
	
	if (checkl == 0)
		gamemode = ID_HELP;
	else
		gamemode = ID_MAINMENU;
	
	bombcount = 2;
	
	while (!glfwWindowShouldClose(window)) {
		
		//Membersihkan buffer
		if (!gameover || gamemode == ID_GAMEOVER)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Menghapus segala transformasi
		glLoadIdentity();
		
		//Proses
		
		///Proses mouse
		if (!paused()) {
			glfwGetCursorPos(window, &newxpos, &newypos);
			float dist = abs(newypos - ypos) + abs(newxpos - xpos);
			if (dist < 10) {
				xpos = newxpos;
				ypos = newypos;
			} else if (dist < 30) {
				xpos = newxpos - (newxpos - xpos)*10/11;
				ypos = newypos - (newypos - ypos)*10/11;
			} else if (dist < 50) {
				xpos = newxpos - (newxpos - xpos)*2/3;
				ypos = newypos - (newypos - ypos)*2/3;
			} else if (dist < 120) {
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
						switchLevel(ID_ZONE3);
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
							defSpw[0].setSpawnTime(0.22);
						}
						defSpw[0].getObject()->setAngle(-defSpw[0].getObject()->angleTo(Point(xpos, ypos))+y);
						normalDraw();
					}
				}
			} break;
			case ID_ZONE1B: {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 8) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_BULLET1);
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() < 7) {
							if (worldtime[1].getElapsed() >= defSpw[0].getSpawnTime()) {
								if (worldtime[0].getElapsed() > 0.8) {
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
								}
								double y[2];
								if (worldtime[0].getElapsed() > 4) {
									y[0] = randomFloat(-40,40);
									y[1] = randomFloat(-40,40);
								} else {
									y[0] = 0;
									y[1] = 0;
								}
								defSpw.setBegin();
								for (int i = 0; i < defSpw.size(); i++) {
									defSpw.getIValue().getObject()->setAngle(-defSpw.getIValue().getObject()->angleTo(Point(xpos, ypos))+y[i]);
									if (worldtime[0].getElapsed() > 4 && worldtime[0].getElapsed() < 4.1) {
										defSpw.getIValue().setSpawnTime(0.24);
									}
									defSpw.next();
								}
								worldtime[1].resetTime();
							}
						}
						normalDraw();
					}	
				}
			} break;
			case ID_LEVEL_A: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					if (storymode) {
						switchLevel(ID_STORY3);
					} else {
						switchArcade();
					}
				} else if (!gameover) {
					if (!paused()) {
						defSpw.setBegin();
						for (int i = 0; i < 9; i++) {
							defSpw.getIValue().getObject()->setAngle(-worldtime[0].getElapsed()*72);
							defSpw.next();
						}
						Spw[0].getObject()->setAngle(worldtime[0].getElapsed()*108);
						for (int i = 0; i < 10; i++) {
							defSpw.getIValue().getObject()->setAngle(-worldtime[0].getElapsed()*36);
							defSpw.next();
						}
						for (int i = 0; i < 10; i++) {
							defSpw.getIValue().getObject()->setAngle(worldtime[0].getElapsed()*36);
							defSpw.next();
						}						
						
						defSpw.setBegin();
						for (int i = 0; i < 9; i++) {
							if (defSpw.getIValue().getObject()->getY() > WINDOW_HEIGHT+50*2)
								defSpw.getIValue().getObject()->setY(-50*2);
							defSpw.next();
						}
						Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(Point(xpos, ypos)))/100+1.5);
						Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(Point(xpos, ypos))); //Karena y terbalik menurut terminal

						for (int i = 0; i < 10; i++) {
							if (defSpw.getIValue().getObject()->getY() < -50*2)
								defSpw.getIValue().getObject()->setY(WINDOW_HEIGHT+50*2);
							defSpw.next();
						}
						for (int i = 0; i < 10; i++) {
							if (i%2 == 0) {
								if (defSpw.getIValue().getObject()->getX() > WINDOW_WIDTH+(150 - 10*i)*2)
									defSpw.getIValue().getObject()->setX(-(150 - 10*i)*2);
							} else {
								if (defSpw.getIValue().getObject()->getX() < -(50 + 10*(i-1))*2)
									defSpw.getIValue().getObject()->setX(WINDOW_WIDTH+(50 + 10*(i-1))*2);
							}
							defSpw.next();
						}
						
						if (Spw[0].getHealth() <= 120 && Spw[0].getHealth() > 120 + 13*SHOT_DAMAGE) {
							Spw[0].damage(13*SHOT_DAMAGE);
							defSpw.setBegin();
							for (int i = 0; i < 19; i++) {
								defSpw.getIValue().getObject()->setTime(301000);
								defSpw.next();
							}
							glColor4f(1.0,1.0,1.0,1.0);
							glVertexPointer (2, GL_FLOAT, 0, borders);
							glDrawArrays(GL_QUADS, 0, 4);
						}
						normalDraw();
					}
				}
			} break;
			case ID_CHASER: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					if (!storymode) {
						switchArcade();
					} else {
						switchLevel(0);
					}
				} else if (!gameover) {
					if (!paused()) {
						float a = (xpos - Spw[0].getObject()->getX())*(-sin(convertToRadian(Spw[0].getObject()->getDirection()))) - (ypos - Spw[0].getObject()->getY())*(cos(convertToRadian(Spw[0].getObject()->getDirection())));
						if (abs(a) > 90) {
							Spw[0].getObject()->setSpeed(Spw[0].getObject()->getSpeed()*199/200);
						} else {
							Spw[0].getObject()->setSpeed(Spw[0].getObject()->getSpeed()*201/200 + 0.05);
						}
						if (a > 20)
							Spw[0].getObject()->setDirection(Spw[0].getObject()->getDirection() + 2);
						else if (a < -20)
							Spw[0].getObject()->setDirection(Spw[0].getObject()->getDirection() - 2);
						else if (a > 10)
							Spw[0].getObject()->setDirection(Spw[0].getObject()->getDirection() + 0.1);
						else if (a < -10)
							Spw[0].getObject()->setDirection(Spw[0].getObject()->getDirection() - 0.1);
						Spw[0].getObject()->setAngle(Spw[0].getObject()->getDirection());
						normalDraw();
					}
				}
			} break;
			case ID_BULLET1: {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 6) {
					if (storymode)
						switchLevel(ID_BULLET2);
					else
						switchArcade();
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() < 4.99) {
							if (worldtime[0].getElapsed() > 3 && worldtime[0].getElapsed() < 3.1) {
								defSpw.setBegin();
								for (int i = 0; i < defSpw.size(); i++) {
									defSpw.getIValue().setSpawnTime(0.3);
									defSpw.next();
								}
							}
							defSpw.setBegin();
							for (int i = 0; i < defSpw.size(); i++) {
								defSpw.getIValue().getObject()->setAngle(-defSpw[i].getObject()->angleTo(Point(xpos, ypos)));
								defSpw.next();
							}
						}
						normalDraw();
					}	
				}
			} break;
			case ID_ZONE2B : {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 4) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_ZONE4);
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[1].getElapsed() > 0.1) {
							float x = randomFloat(0.8,1.5);
							Sq.add(SquareObj(xpos + randomDouble(-200, 200), ypos + randomDouble(-250, 250), randomInt(150, 300), x+0.5, x));
							worldtime[1].resetTime();
						}
						Sq.setBegin();
						for (int i = 0; i < Sq.size(); i++) {
							if (!Sq.getIValue().isMaterialised())
								Sq.getIValue().setAngle(Sq.getIValue().getTimeElapsed()*100);
							Sq.next();
						}
						normalDraw();
					}	
				}
			} break;
			case ID_ZONE2 : {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 4) {
					switchArcade();
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[1].getElapsed() > 0.25) {
							float x = randomFloat(1.4,2);
							Sq.add(SquareObj(xpos + randomDouble(-200, 200), ypos + randomDouble(-200, 200), randomInt(150, 300), x+0.5, x));
							worldtime[1].resetTime();
						}
						Sq.setBegin();
						for (int i = 0; i < Sq.size(); i++) {
							if (!Sq.getIValue().isMaterialised())
								Sq.getIValue().setAngle(Sq.getIValue().getTimeElapsed()*100);
							Sq.next();
						}
						normalDraw();
					}	
				}
			} break;
			case ID_SHOOTER1: {
				if (!paused() && !gameover && (Spw.isEmpty() || worldtime[0].getElapsed() > 11)) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_ZONE6);
				} else if (!gameover) {
					if (!paused()) {
						Spw[0].getObject()->setAngle(worldtime[0].getElapsed()*830);
						if (worldtime[0].getElapsed() < 4 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/3) {
							Spw[0].getObject()->setSpeed(0);
							Spw[0].getObject()->setY(WINDOW_HEIGHT/3-0.01);
						} else if (worldtime[0].getElapsed() > 8) {
							Spw[0].getObject()->setSpeed(5);
						}
						normalDraw();
					}	
				}
			} break;
			case ID_ZONE3 : {
				if (!paused() && !gameover && (worldtime[0].getElapsed() > 8 || (worldtime[0].getElapsed() > 4 && Spw.isEmpty()))) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_ZONE2);
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() < 5 && worldtime[1].getElapsed() > 0.1) {
							float x = randomFloat(-250, WINDOW_WIDTH+250);
							Spw.add(Spawner2D(new TriangleObj(x, -100, 100, 50, 7), TYPE_TRIANGLE, 999, 1, NULL_SHOT));
							float ang = -Spw[0].getObject()->angleTo(Point(xpos, ypos));
							Spw[0].getObject()->setSpeed(7+worldtime[0].getElapsed()/2);
							Spw[0].getObject()->setAngle(ang);
							Spw[0].getObject()->setDirection(ang);
							Spw[0].getObject()->getColorData()[0] = 0.0;
							Spw[0].getObject()->getColorData()[2] = 0.0;
							worldtime[1].resetTime();
						}
						for (int i = 0; i < Spw.size(); i++) {
							if (Spw[i].getObject()->getY() < 100 && Spw[i].getObject()->getY() < ypos) {
								float ang = Spw[i].getObject()->getAngle() + (-Spw[i].getObject()->angleTo(Point(xpos, ypos)) - Spw[i].getObject()->getAngle())/5;
								Spw[i].getObject()->setDirection(ang);
								Spw[i].getObject()->setAngle(ang);
							}
						}
						normalDraw();
					}	
				}
			} break;
			case ID_ZONE4 : {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 7) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_ZONE5);
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() < 3.5 && worldtime[1].getElapsed() > 0.5) {
							Spw.add(Spawner2D(new SquareObj(100, -150, 120, 1.7), TYPE_SQUARE, 0.6, 1, SQUARE_AIMSHOT1));
							Spw.add(Spawner2D(new SquareObj(WINDOW_WIDTH-100, -150, 120, 1.7), TYPE_SQUARE, 0.6, 1, SQUARE_AIMSHOT1));
							Spw.setBegin();
							for (int i = 0; i < 2; i++) {
								Spw.getIValue().getObject()->setSpeed(10);
								Spw.getIValue().getObject()->setAngle(270);
								Spw.getIValue().getObject()->setDirection(270);
								Spw.getIValue().getObject()->getColorData()[0] = 0.0;
								Spw.getIValue().getObject()->getColorData()[2] = 0.4;
								Spw.next();
							}
							worldtime[1].resetTime();
						}
						normalDraw();
					}	
				}
			} break;
			case ID_ZONE5 : {
				if (!paused() && !gameover && (worldtime[0].getElapsed() > 4.5 && Spw.isEmpty())) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_SHOOTER1);
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() < 4 && worldtime[1].getElapsed() > 0.2) {
							Spw.add(Spawner2D(new TriangleObj(WINDOW_WIDTH/2, -120, 120, 100, 8, 0.5), TYPE_TRIANGLE, randomFloat(3, 5), 8, SQUARE_AIMSHOT1));
							Spw[0].getObject()->getColorData()[0] = 0.4;
							Spw[0].getObject()->getColorData()[2] = 0.0;
							worldtime[1].resetTime();
						}
						Spw.setBegin();
						for (int i = 0; i < Spw.size(); i++) {
							Spw.getIValue().getObject()->setSpeed(7 + 7*cos(Spw.getIValue().getObject()->getTimeElapsed()*2));
							float a = 270 + 85*cos(Spw.getIValue().getObject()->getTimeElapsed());
							Spw.getIValue().getObject()->setAngle(a);
							Spw.getIValue().getObject()->setDirection(a);
							Spw.next();
						}
						normalDraw();
					}	
				}
			} break;
			case ID_ZONE6 : {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 5) {
					switchLevel(ID_RAPIDSHOOTER);
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() < 0.5 && Qu.isEmpty()) {
							Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 550, WINDOW_HEIGHT+20, 1.5, 3));
							Qu.add(QuadObj(WINDOW_WIDTH/2, 0, 550, 50, 1.5, 3));
							Qu[0].getColorData()[1] = 0.0;
							Qu[0].getColorData()[2] = 0.0;
							Sq.add(SquareObj(WINDOW_WIDTH/2, -650, 500, 2));
							Sq[0].setSpeed(15);
							Sq[0].setDirection(270);
							Sq[0].setAngle(45);
						} else if (worldtime[0].getElapsed() < 1.6 && Qu.isEmpty()) {
							Qu.add(QuadObj(WINDOW_WIDTH/6, WINDOW_HEIGHT/2, 550, WINDOW_HEIGHT+20, 1.5, 3));
							Qu.add(QuadObj(WINDOW_WIDTH/6, 0, 550, 50, 1.5, 3));
							Qu[0].getColorData()[1] = 0.0;
							Qu[0].getColorData()[2] = 0.0;
							Qu.add(QuadObj(WINDOW_WIDTH*5/6, WINDOW_HEIGHT/2, 550, WINDOW_HEIGHT+20, 1.5, 3));
							Qu.add(QuadObj(WINDOW_WIDTH*5/6, 0, 550, 50, 1.5, 3));
							Qu[0].getColorData()[1] = 0.0;
							Qu[0].getColorData()[2] = 0.0;
							Sq.add(SquareObj(WINDOW_WIDTH/6, -650, 500, 2));
							Sq.add(SquareObj(WINDOW_WIDTH*5/6, -650, 500, 2));
							Sq.setBegin();
							for (int i = 0; i < 2; i++) {
								Sq.getIValue().setSpeed(15);
								Sq.getIValue().setDirection(270);
								Sq.getIValue().setAngle(45);
								Sq.next();
							}
						}
						normalDraw();
					}	
				}
			} break;
			case ID_ZONE6B : {
				if (!paused() && !gameover && worldtime[0].getElapsed() > 5.3) {
					switchArcade();
				} else if (!gameover) {
					if (!paused()) {
						bool rev;
						if (worldtime[0].getElapsed() < 2.6)
							rev = false;
						else
							rev = true;
						if (worldtime[0].getElapsed() > 0.5) {
							if (worldtime[0].getElapsed() < 1.2+2.1*rev && Qu.isEmpty()) {
								Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 400, WINDOW_HEIGHT+20, 0.71, 3));
								Qu.add(QuadObj(WINDOW_WIDTH/2, rev*WINDOW_HEIGHT, 400, 50, 0.71, 3));
								Qu[0].getColorData()[1] = 0.0;
								Qu[0].getColorData()[2] = 0.0;
								Sq.add(SquareObj(WINDOW_WIDTH/2, rev*(WINDOW_HEIGHT+1000)-500, 350, 2));
								Sq[0].setSpeed(15);
								if (rev)
									Sq[0].setDirection(90);
								else
									Sq[0].setDirection(270);
								Sq[0].setAngle(45);
							} else if (worldtime[0].getElapsed() < 1.9+2.1*rev && Qu.isEmpty()) {
								Qu.add(QuadObj(WINDOW_WIDTH*3/10, WINDOW_HEIGHT/2, 400, WINDOW_HEIGHT+20, 0.71, 3));
								Qu.add(QuadObj(WINDOW_WIDTH*3/10, rev*WINDOW_HEIGHT, 400, 50, 0.71, 3));
								Qu[0].getColorData()[1] = 0.0;
								Qu[0].getColorData()[2] = 0.0;
								Qu.add(QuadObj(WINDOW_WIDTH*7/10, WINDOW_HEIGHT/2, 400, WINDOW_HEIGHT+20, 0.71, 3));
								Qu.add(QuadObj(WINDOW_WIDTH*7/10, rev*WINDOW_HEIGHT, 400, 50, 0.71, 3));
								Qu[0].getColorData()[1] = 0.0;
								Qu[0].getColorData()[2] = 0.0;
								Sq.add(SquareObj(WINDOW_WIDTH*3/10, rev*(WINDOW_HEIGHT+1000)-500, 350, 2));
								Sq.add(SquareObj(WINDOW_WIDTH*7/10, rev*(WINDOW_HEIGHT+1000)-500, 350, 2));
								Sq.setBegin();
								for (int i = 0; i < 2; i++) {
									Sq.getIValue().setSpeed(15);
									if (rev)
										Sq.getIValue().setDirection(90);
									else
										Sq.getIValue().setDirection(270);
									Sq.getIValue().setAngle(45);
									Sq.next();
								}
							} else if (worldtime[0].getElapsed() < 2.6+2.1*rev && Qu.isEmpty()) {
								Qu.add(QuadObj(WINDOW_WIDTH/10, WINDOW_HEIGHT/2, 400, WINDOW_HEIGHT+20, 0.71, 3));
								Qu.add(QuadObj(WINDOW_WIDTH/10, rev*WINDOW_HEIGHT, 400, 50, 0.71, 3));
								Qu[0].getColorData()[1] = 0.0;
								Qu[0].getColorData()[2] = 0.0;
								Qu.add(QuadObj(WINDOW_WIDTH*9/10, WINDOW_HEIGHT/2, 400, WINDOW_HEIGHT+20, 0.71, 3));
								Qu.add(QuadObj(WINDOW_WIDTH*9/10, rev*WINDOW_HEIGHT, 400, 50, 0.71, 3));
								Qu[0].getColorData()[1] = 0.0;
								Qu[0].getColorData()[2] = 0.0;
								Sq.add(SquareObj(WINDOW_WIDTH/10, rev*(WINDOW_HEIGHT+1000)-500, 350, 2));
								Sq.add(SquareObj(WINDOW_WIDTH*9/10, rev*(WINDOW_HEIGHT+1000)-500, 350, 2));
								Sq.setBegin();
								for (int i = 0; i < 2; i++) {
									Sq.getIValue().setSpeed(15);
									if (rev)
										Sq.getIValue().setDirection(90);
									else
										Sq.getIValue().setDirection(270);
									Sq.getIValue().setAngle(45);
									Sq.next();
								}
							}
						}
						normalDraw();
					}	
				}
			} break;
			case ID_BULLET2: {
				if (!paused() && !gameover && Spw.isEmpty() && worldtime[1].getElapsed() > 1.5) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_LEVEL_A);
				} else if (!gameover) {
					if (!paused()) {
						if (!Spw.isEmpty()) {
							if (Spw[0].getObject()->getAngle() > 90) {
								Spw[0].getObject()->setAngle(Spw[0].getObject()->getAngle()+5);
								if (Spw[0].getObject()->getAngle() > 450)
									Spw[0].getObject()->setAngle(89);
							} else {
								Spw[0].getObject()->setAngle(Spw[0].getObject()->getAngle()-5);
								if (Spw[0].getObject()->getAngle() < -270)
									Spw[0].getObject()->setAngle(91);
							}
							if (worldtime[0].getElapsed() > 15) {
								Spw[0].getObject()->setSpeed(5);
							} else if (Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5) {
								Spw[0].getObject()->setSpeed(0);
								Spw[0].getObject()->setY(WINDOW_HEIGHT/5-0.01);
							}
						}
						checkDamaged();
						drawObjects();
						if (Spw.isEmpty() && worldtime[1].getElapsed() > 2)
							worldtime[1].resetTime();
						drawCursor();
					}	
				}
			} break;
			case ID_SHOOTER2: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					switchArcade();
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() > 7 && worldtime[0].getElapsed() < 7.1) {
							Spw.setBegin();
							for (int i = 0; i < Spw.size(); i++) {
								Spw.getIValue().getObject()->setSpeed(4);
								Spw.next();
							}
						} else if (worldtime[0].getElapsed() < 1 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5) {
							Spw.setBegin();
							for (int i = 0; i < Spw.size(); i++) {
								Spw.getIValue().getObject()->setSpeed(0);
								Spw.getIValue().getObject()->setY(WINDOW_HEIGHT/5-0.01);
								Spw.next();
							}
						}
						Spw.setBegin();
						for (int i = 0; i < Spw.size(); i++) {
							Spw.getIValue().getObject()->setAngle(-Spw.getIValue().getObject()->angleTo(Point(xpos, ypos)));
							Spw.next();
						}
						normalDraw();
					}	
				}
			} break;
			case ID_SHOOTER3: {
				if (!paused() && !gameover && (Spw.isEmpty() && worldtime[0].getElapsed() > 4)) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() > 0.9 && worldtime[0].getElapsed() < 1) {
							Spw.setBegin();
							for (int i = 0; i < Spw.size(); i++) {
								Spw.getIValue().getObject()->setSpeed(2);
								Spw.next();
							}
						}
						Spw.setBegin();
						for (int i = 0; i < Spw.size(); i++) {
							Spw.getIValue().getObject()->setAngle(worldtime[0].getElapsed()*360);
							Spw.next();
						}
						normalDraw();
					}	
				}
			} break;
			case ID_SHOOTER4: {
				if (!paused() && !gameover && Spw.isEmpty() && worldtime[1].getElapsed() > 2) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_SHOOTER1);
				} else if (!gameover) {
					if (!paused()) {
						if (!Spw.isEmpty()) {
							Spw[0].getObject()->setAngle(-Spw[0].getObject()->angleTo(Point(xpos, ypos)));
							if (worldtime[0].getElapsed() < 18.1) {
								if (worldtime[0].getElapsed() > 18) {
									Spw[0].getObject()->setSpeed(3.0);
									Spw[0].getObject()->setDirection(270);
								} else if ((Spw[0].getObject()->distanceSquaredTo(pointmark) < 1) || (Spw[0].getObject()->getSpeed() > 1.3 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/8)) {
									pointmark = Point(randomFloat(300, WINDOW_WIDTH-300), randomFloat(50, 100));
									Spw[0].getObject()->setSpeed(1.0);
									Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
								} 
							}
						}
						checkDamaged();
						drawObjects();
						if (Spw.isEmpty() && worldtime[1].getElapsed() > 3)
							worldtime[1].resetTime();
						drawCursor();
					}
				}
			} break;
			case ID_SHOOTER5: {
				if (!paused() && !gameover && (Spw.isEmpty() && worldtime[1].getElapsed() > 1)) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						if (!Spw.isEmpty()) {
							if (Spw[0].getObject()->getSpeed() > 3 && Spw[0].getObject()->getY() > WINDOW_HEIGHT/10) {
								Spw.setBegin();
								for (int i = 0; i < Spw.size(); i++) {
									Spw.getIValue().getObject()->setSpeed(1);
									Spw.getIValue().getSpawnTimer().setTime(randomFloat(0.0, 1500.0));
									Spw.next();
								}
							}
						}
						checkDamaged();
						drawObjects();
						if (Spw.isEmpty() && worldtime[1].getElapsed() > 2)
							worldtime[1].resetTime();
						drawCursor();
					}
				}
			} break;
			case ID_RAPIDSHOOTER: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(ID_STORY2);
				} else if (!gameover) {
					if (!paused()) {
						Spw[0].getObject()->setAngle(-Spw[0].getObject()->angleTo(Point(xpos, ypos)));
						if (worldtime[0].getElapsed() < 1 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5) {
							Spw[0].getObject()->setSpeed(0);
							Spw[0].getObject()->setY(WINDOW_HEIGHT/5-0.01);
						}
						Spw[0].setSpawnTime(0.12-worldtime[0].getElapsed()/200);
						normalDraw();
					}	
				}
			} break;
			case ID_RINGSHOOTER: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						Spw[0].getObject()->setAngle(-Spw[0].getObject()->angleTo(Point(xpos, ypos)));
						if ((Spw[0].getObject()->distanceSquaredTo(pointmark) < 4) || (Spw[0].getObject()->getSpeed() > 1 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5)) {
							pointmark = Point(randomFloat(400, WINDOW_WIDTH-400), randomFloat(50, 200));
							Spw[0].getObject()->setSpeed(1.0);
							Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
						}
						normalDraw();
					}	
				}
			} break;
			case ID_DEADLYHEARTS: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						if (Spw[0].getObject()->getY() > 150) {
							Spw.setBegin();
							for (int i = 0; i < 2; i++) {
								Spw.getIValue().getObject()->setSpeed(0);
								Spw.getIValue().getObject()->setY(150);
								Spw.next();
							}
							Spw[0].getSpawnTimer().setTime(600);
						}
						normalDraw();
					}	
				}
			} break;
			case ID_DRONEDFIGHTER: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						defSpw.setBegin();
						for (int i = 0; i < defSpw.size(); i++) {
							defSpw.getIValue().getObject()->setAngle(-defSpw.getIValue().getObject()->angleTo(Point(xpos, ypos)));
							defSpw.next();
						}
						if (Spw[0].getObject()->getY() <= 150 && defSpw[0].getObject()->getX() > WINDOW_WIDTH/2+250) {
							defSpw.setBegin();
							for (int i = 0; i < defSpw.size(); i++) {
								defSpw.getIValue().getObject()->setSpeed(0);
								defSpw.getIValue().getObject()->setX(WINDOW_WIDTH/2+250 - i*500);
								defSpw.next();
							}
							defSpw[0].getSpawnTimer().setTime(450);
						} else if (Spw[0].getObject()->getY() > 150) {
							Spw[0].getObject()->setSpeed(0);
							Spw[0].getObject()->setY(150);
							defSpw.setBegin();
							defSpw.getIValue().getObject()->setDirection(0);
							defSpw.getIValue().getObject()->setSpeed(4);
							defSpw.next();
							defSpw.getIValue().getObject()->setDirection(180);
							defSpw.getIValue().getObject()->setSpeed(4);
						}
						normalDraw();
					}	
				}
			} break;
			case ID_ZONE7 : {
				if (!paused() && !gameover && (worldtime[0].getElapsed() > 9 || (worldtime[0].getElapsed() > 9 && Spw.isEmpty()))) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						if (worldtime[0].getElapsed() < 5 && worldtime[1].getElapsed() > 0.25) {
							float x = randomFloat(50, WINDOW_WIDTH-50);
							Spw.add(Spawner2D(new SquareObj(x, -100, 100, 6), TYPE_SQUARE, 999, 1, SQUARE_EXPLODE1));
							Spw[0].getObject()->setSpeed(4);
							Spw[0].getObject()->setAngle(90);
							Spw[0].getObject()->setDirection(270);
							Spw[0].getObject()->getColorData()[1] = 0.6;
							Spw[0].getObject()->getColorData()[2] = 0.4;
							worldtime[1].resetTime();
						}
						normalDraw();
					}	
				}
			} break;
			case ID_RIPPLES : {
				if (!paused() && !gameover && Spw.isEmpty()) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						if (Spw[0].getObject()->getSpeed() > 1 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5) {
							Spw[0].getObject()->setSpeed(0);
							Spw[0].getObject()->setY(WINDOW_HEIGHT/5-0.01);
							defSpw[0].getObject()->setSpeed(0);
							defSpw[0].getObject()->setY(WINDOW_HEIGHT/5-0.01);
							defSpw[0].getSpawnTimer().setTime(600);
						}
						normalDraw();
					}	
				}
			} break;
			case ID_DANMAKU1: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						Spw[0].getObject()->setAngle(worldtime[0].getElapsed()*360);
						if (Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5) {
							Spw[0].getObject()->setSpeed(0);
							Spw[0].getObject()->setY(WINDOW_HEIGHT/5-0.01);
							defSpw[0].getObject()->setSpeed(0);
							defSpw[0].getObject()->setY(WINDOW_HEIGHT/5-0.01);
						}
						patterner += 13;
						normalDraw();
					}	
				}
			} break;
			case ID_RAIN: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					if (!storymode)
						switchArcade();
					else
						switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						if ((Spw[0].getObject()->distanceSquaredTo(pointmark) < 4) || (Spw[0].getObject()->getSpeed() > 2 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5)) {
							if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-500) || Spw[0].getObject()->getX() < 500)
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()+100, Spw[0].getObject()->getX()+200), randomFloat(100, 200));
							else
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()-100, Spw[0].getObject()->getX()-200), randomFloat(100, 200));
							Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/300);
							Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
							Spw[0].getSpawnTimer().setTime(15000);
						}
						normalDraw();
					}	
				}
			} break;
			case ID_LASERBLOOM: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						if ((Spw[0].getObject()->distanceSquaredTo(pointmark) < 4) || (Spw[0].getObject()->getSpeed() > 2 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5)) {
							if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-400) || Spw[0].getObject()->getX() < 400)
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()+100, Spw[0].getObject()->getX()+200), randomFloat(90, 180));
							else
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()-100, Spw[0].getObject()->getX()-200), randomFloat(90, 180));
							Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/300);
							Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
						}
						
						Ptt.setBegin();
						Qu.setBegin();
						for(int i = 0; i < Ptt.size(); i++) {
							float ang = 7.0 - 3*Qu.getIValue().getTimeElapsed();
							if (ang > 0)
								Ptt.getIValue().rotate(ang);
							for(int j = 0; j < Ptt.getIValue().getObjNum(); j++) {
								Qu.getIValue().setSpeed(Qu.getIValue().getTimeElapsed()*Qu.getIValue().getTimeElapsed());
								Qu.getIValue().setAngle(Qu.getIValue().getDirection());
								Qu.next();
							}
							Ptt.next();
						}
						normalDraw();
					}	
				}
			} break;
			case ID_RADIANCE: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						if ((Spw[0].getObject()->distanceSquaredTo(pointmark) < 100) || (worldtime[1].getElapsed() < 2 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5)) {
							if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-700) || Spw[0].getObject()->getX() < 700)
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()+250, Spw[0].getObject()->getX()+500), randomFloat(90, 200));
							else
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()-250, Spw[0].getObject()->getX()-500), randomFloat(90, 200));
							worldtime[0].resetTime();
							Spw[0].getObject()->setSpeed(0);
							Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
							Spw[0].setSpawnTime(0.04);
						} else if (worldtime[0].getElapsed() > 2.0 && worldtime[0].getElapsed() < 2.5) {
							Spw[0].setSpawnTime(10);
						} else if (worldtime[0].getElapsed() > 2.5) {
							Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/10);
						}
						
						normalDraw();
					}
				}
			} break;
			case ID_SPIKECAGE: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					switchLevel(0);
				} else if (!gameover) {
					if (!paused()) {
						if ((Spw[0].getObject()->distanceSquaredTo(pointmark) < 4) || (Spw[0].getObject()->getSpeed() > 5 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5)) {
							if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-400) || Spw[0].getObject()->getX() < 400)
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()+100, Spw[0].getObject()->getX()+200), randomFloat(90, 180));
							else
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()-100, Spw[0].getObject()->getX()-200), randomFloat(90, 180));
							Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/300);
							Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
						}
							
						Tr.setBegin();
						for (int i = 0; i < Tr.size(); i++) {
							if (Tr.getIValue().getX() < 0 || Tr.getIValue().getX() > WINDOW_WIDTH) {
								Tr.getIValue().setDirection(180-Tr.getIValue().getDirection());
								Tr.getIValue().setAngle(Tr.getIValue().getDirection());
							}
							if (Tr.getIValue().getY() < 0 || Tr.getIValue().getY() > WINDOW_HEIGHT) {
								Tr.getIValue().setDirection(-Tr.getIValue().getDirection());
								Tr.getIValue().setAngle(Tr.getIValue().getDirection());
							}
							Tr.next();
						}
						checkDamaged();
						if (Spw[0].getObject()->isMaterialised() && Spw[0].isDamaged())
							Spw[0].getSpawnTimer().setTime(Spw[0].getSpawnTimer().getElapsed()*1000 + 9000);
						drawObjects();
						drawCursor();
					}	
				}
			} break;
			case ID_ICEGOD: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					switchLevel(ID_MAINMENU);
				} else if (!gameover) {
					if (!paused()) {
						if ((Ptt[0].distanceSquaredTo(pointmark) < 4) || (Ptt[0].getSpeed() > 3 && Ptt[0].getY() >= WINDOW_HEIGHT/5)) {
							if ((randomInt(0,1) == 0 && Ptt[0].getX() < WINDOW_WIDTH-400) || Ptt[0].getX() < 400)
								pointmark = Point(randomFloat(Ptt[0].getX()+100, Ptt[0].getX()+200), randomFloat(80, 200));
							else
								pointmark = Point(randomFloat(Ptt[0].getX()-100, Ptt[0].getX()-200), randomFloat(80, 200));
							Ptt[0].setSpeed(sqrt(Ptt[0].distanceSquaredTo(pointmark))/300);
							Ptt[0].setDirection(-Ptt[0].angleTo(pointmark));
						}
						
						if (Spw[0].getHealth() > 340) {
							
							defSpw.setBegin();
							if (defSpw.size() > 4) {
								defSpw[0].getObject()->setSpeed(defSpw[0].getObject()->getSpeed()-0.06);
								if (worldtime[0].getElapsed() > 1.7) {
									defSpw.getIValue().getObject()->setAngle(-defSpw.getIValue().getObject()->angleTo(Point(xpos, ypos)));
									defSpw.getIValue().getObject()->setDirection(-defSpw.getIValue().getObject()->angleTo(Point(xpos, ypos)));
									defSpw.getIValue().getObject()->setSpeed(8);
									worldtime[0].resetTime();
								}
								defSpw.next();
							} else
								worldtime[0].resetTime();
							
							for (int i = 0; i < 4; i++) {
								defSpw.getIValue().getObject()->getColorData()[1] = 1.0 - (540 + 13*SHOT_DAMAGE - Spw[0].getHealth())/200;
								defSpw.next();
							}
						} else {
							defSpw.setBegin();
							defSpw.getIValue().getObject()->setSpeed(defSpw.getIValue().getObject()->getSpeed()-0.09);
							if (worldtime[1].getElapsed() > 0.91) {
								defSpw.getIValue().getObject()->setAngle(-defSpw.getIValue().getObject()->angleTo(Point(xpos, ypos)));
								defSpw.getIValue().getObject()->setDirection(-defSpw.getIValue().getObject()->angleTo(Point(xpos, ypos)));
								defSpw.getIValue().getObject()->setSpeed(8);
								worldtime[1].resetTime();
							}
							defSpw.next();
							defSpw.getIValue().getObject()->setSpeed(defSpw.getIValue().getObject()->getSpeed()-0.06);
							if (worldtime[0].getElapsed() > 1.7) {
								defSpw.getIValue().getObject()->setAngle(-defSpw.getIValue().getObject()->angleTo(Point(xpos, ypos)));
								defSpw.getIValue().getObject()->setDirection(-defSpw.getIValue().getObject()->angleTo(Point(xpos, ypos)));
								defSpw.getIValue().getObject()->setSpeed(8);
								worldtime[0].resetTime();
							}
						}
						
						if (Spw[0].getHealth() > 340 && Spw[0].getHealth() <= 340 + 13*SHOT_DAMAGE) {
							Spw[0].damage(13*SHOT_DAMAGE);
							Spw[0].getSpawnTimer().setTime(999999);
							worldtime[1].resetTime();
							Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 998, 999));
							Qu[0].getColorData()[0] = 0.5;
							Qu[0].getColorData()[1] = 0.4;
							Qu[0].getColorData()[2] = 0.8;
							Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 0.1, 1));
						}
						
						Tr.setBegin();
						for (int i = 0; i < Tr.size(); i++) {
							if (Tr.getIValue().getSpeed() < 0.05)
								Tr.getIValue().setSpeed(0);
							else
								Tr.getIValue().setSpeed(Tr.getIValue().getSpeed()-0.15);
							Tr.next();
						}
						normalDraw();
					}	
				}
			} break;
			case ID_EARTHGOD: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					switchLevel(ID_MAINMENU);
				} else if (!gameover) {
					if (!paused()) {
						if ((Ptt[0].distanceSquaredTo(pointmark) < 4) || (Ptt[0].getSpeed() > 3 && Ptt[0].getY() >= WINDOW_HEIGHT/5)) {
							if ((randomInt(0,1) == 0 && Ptt[0].getX() < WINDOW_WIDTH-400) || Ptt[0].getX() < 400)
								pointmark = Point(randomFloat(Ptt[0].getX()+100, Ptt[0].getX()+200), randomFloat(60, 180));
							else
								pointmark = Point(randomFloat(Ptt[0].getX()-100, Ptt[0].getX()-200), randomFloat(60, 180));
							Ptt[0].setSpeed(sqrt(Ptt[0].distanceSquaredTo(pointmark))/400);
							Ptt[0].setDirection(-Ptt[0].angleTo(pointmark));
						}
						
						defSpw.setBegin();
						for (int i = 0; i < defSpw.size() - 4; i++) {
							defSpw.next();
						}
						
						if (Spw[0].getHealth() > 360) {
							for (int i = 0; i < 4; i++) {
								defSpw.getIValue().getObject()->getColorData()[2] = 1.0 - (540 + 13*SHOT_DAMAGE - Spw[0].getHealth())/200;
								defSpw.next();
							}
						} else {
							if (worldtime[0].getElapsed() > 5) {
								Tr.add(TriangleObj(xpos, WINDOW_HEIGHT-130, 260, 240, 3, 4));
								Tr[0].setAngle(90);
								Tr.add(TriangleObj(xpos, WINDOW_HEIGHT+1800, 260, 240, 7));
								Tr[0].setAngle(90);
								Tr[0].setDirection(90);
								Tr[0].setSpeed(9);
								Tr.setBegin();
								for (int i = 0; i < 2; i++) {
									Tr.getIValue().getColorData()[0] = 0.4;
									Tr.getIValue().getColorData()[1] = 0.3;
									Tr.getIValue().getColorData()[2] = 0.0;
									Tr.next();
								}
								worldtime[0].resetTime();
							}
						}
						
						if (Spw[0].getHealth() > 360 && Spw[0].getHealth() <= 360 + 13*SHOT_DAMAGE) {
							Spw[0].damage(13*SHOT_DAMAGE);
							Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 998, 999));
							Qu[0].getColorData()[0] = 0.5;
							Qu[0].getColorData()[1] = 0.3;
							Qu[0].getColorData()[2] = 0.1;
							Qu.add(QuadObj(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, 0.1, 1));
						}
						
						normalDraw();
					}	
				}
			} break;
			case ID_SHOOTER6: {
				if (!paused() && !gameover && Spw.isEmpty() && worldtime[1].getElapsed() > 3.5) {
					switchLevel(ID_MAINMENU);
				} else if (!gameover) {
					if (!paused()) {
						if (!Spw.isEmpty()) {
							if (worldtime[0].getElapsed() > 18) {
								Spw.setBegin();
								for (int i = 0; i < Spw.size(); i++) {
									Spw.getIValue().getObject()->setSpeed(5);
									Spw.next();
								}
							} else if (worldtime[0].getElapsed() > 0.8 && Spw[0].getObject()->getSpeed() > 4) {
								Spw.setBegin();
								for (int i = 0; i < Spw.size(); i++) {
									Spw.getIValue().getObject()->setSpeed(0);
									Spw.getIValue().getObject()->setDirection(270);
									Spw.getIValue().getSpawnTimer().setTime(randomFloat(0.0, 900.0));
									Spw.next();
								}
							}
						}
						
						checkDamaged();
						drawObjects();
						if (Spw.isEmpty() && worldtime[1].getElapsed() > 4)
							worldtime[1].resetTime();
						drawCursor();
					}	
				}
			} break;
			case ZONE_TEST: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					switchLevel(ID_MAINMENU);
				} else if (!gameover) {
					if (!paused()) {
						if ((Spw[0].getObject()->distanceSquaredTo(pointmark) < 4) || (Spw[0].getObject()->getSpeed() > 5 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5)) {
							if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-400) || Spw[0].getObject()->getX() < 400)
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()+100, Spw[0].getObject()->getX()+200), randomFloat(90, 180));
							else
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()-100, Spw[0].getObject()->getX()-200), randomFloat(90, 180));
							Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/300);
							Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
						}
						normalDraw();
					}	
				}
			} break;
			/**case ZONE_TEST: {
				if (!paused() && !gameover && Spw.isEmpty()) {
					switchLevel(ID_MAINMENU);
				} else if (!gameover) {
					if (!paused()) {
						if ((Spw[0].getObject()->distanceSquaredTo(pointmark) < 4) || (Spw[0].getObject()->getSpeed() > 5 && Spw[0].getObject()->getY() >= WINDOW_HEIGHT/5)) {
							if ((randomInt(0,1) == 0 && Spw[0].getObject()->getX() < WINDOW_WIDTH-400) || Spw[0].getObject()->getX() < 400)
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()+100, Spw[0].getObject()->getX()+200), randomFloat(90, 180));
							else
								pointmark = Point(randomFloat(Spw[0].getObject()->getX()-100, Spw[0].getObject()->getX()-200), randomFloat(90, 180));
							Spw[0].getObject()->setSpeed(sqrt(Spw[0].getObject()->distanceSquaredTo(pointmark))/300);
							Spw[0].getObject()->setDirection(-Spw[0].getObject()->angleTo(pointmark));
						}
						normalDraw();
					}	
				}
			} break;**/
			case ID_HELP: {
				glVertexPointer (2, GL_FLOAT, 0, helptext);
				glLineWidth(2);
				glDrawArrays(GL_LINES, 0, helpmark[9]/2);
				drawCursor();
			} break;
			case ID_WIN: {
				glLineWidth(7);
				glVertexPointer (2, GL_FLOAT, 0, wintext);
				glColor4f(1.0,1.0,1.0,delaytime.getElapsed());
				glDrawArrays(GL_LINES, 0, winmark[2]/2);
			} break;
			case ID_STORY1: {
				glLineWidth(STORY_LINESIZE);
				glVertexPointer (2, GL_FLOAT, 0, story1text);
				glColor4f(1.0,1.0,1.0,worldtime[0].getElapsed());
				glDrawArrays(GL_LINES, 0, story1mark[2]/2);
				drawCursor();
				if (!paused() && !gameover && worldtime[0].getElapsed() > 3)
					switchLevel(ID_ZONE1);
			} break;
			case ID_STORY2: {
				glLineWidth(STORY_LINESIZE);
				glVertexPointer (2, GL_FLOAT, 0, story2text);
				glColor4f(1.0,1.0,1.0,worldtime[0].getElapsed());
				glDrawArrays(GL_LINES, 0, story2mark[1]/2);
				drawCursor();
				if (!paused() && !gameover && worldtime[0].getElapsed() > 3)
					switchLevel(ID_ZONE1B);
			} break;
			case ID_STORY3: {
				glLineWidth(STORY_LINESIZE);
				glVertexPointer (2, GL_FLOAT, 0, story3text);
				glColor4f(1.0,1.0,1.0,worldtime[0].getElapsed());
				glDrawArrays(GL_LINES, 0, story3mark[1]/2);
				drawCursor();
				if (!paused() && !gameover && worldtime[0].getElapsed() > 3)
					switchLevel(ID_WIN);
			} break;
			case ID_STORY4: {
				glLineWidth(STORY_LINESIZE);
				glVertexPointer (2, GL_FLOAT, 0, story4text);
				glColor4f(1.0,1.0,1.0,worldtime[0].getElapsed());
				glDrawArrays(GL_LINES, 0, story4mark[1]/2);
				drawCursor();
				if (!paused() && !gameover && worldtime[0].getElapsed() > 3)
					switchLevel(ID_WIN);
			} break;
			case ID_STORY5: {
				glLineWidth(STORY_LINESIZE);
				glVertexPointer (2, GL_FLOAT, 0, story5text);
				glColor4f(1.0,1.0,1.0,worldtime[0].getElapsed());
				glDrawArrays(GL_LINES, 0, story5mark[1]/2);
				drawCursor();
				if (!paused() && !gameover && worldtime[0].getElapsed() > 3)
					switchLevel(ID_WIN);
			} break;
			case ID_STORY6: {
				glLineWidth(STORY_LINESIZE);
				glVertexPointer (2, GL_FLOAT, 0, story6text);
				glColor4f(1.0,1.0,1.0,worldtime[0].getElapsed());
				glDrawArrays(GL_LINES, 0, story6mark[2]/2);
				drawCursor();
				if (!paused() && !gameover && worldtime[0].getElapsed() > 3)
					switchLevel(ID_WIN);
			} break;
			case ID_STORY7: {
				glLineWidth(STORY_LINESIZE);
				glVertexPointer (2, GL_FLOAT, 0, story7text);
				glColor4f(1.0,1.0,1.0,worldtime[0].getElapsed());
				glDrawArrays(GL_LINES, 0, story7mark[1]/2);
				drawCursor();
				if (!paused() && !gameover && worldtime[0].getElapsed() > 3)
					switchLevel(ID_WIN);
			} break;
			case ID_STORY8: {
				glLineWidth(STORY_LINESIZE);
				glVertexPointer (2, GL_FLOAT, 0, story8text);
				glColor4f(1.0,1.0,1.0,worldtime[0].getElapsed());
				glDrawArrays(GL_LINES, 0, story8mark[1]/2);
				drawCursor();
				if (!paused() && !gameover && worldtime[0].getElapsed() > 3)
					switchLevel(ID_WIN);
			} break;
			case ID_STORY9: {
				glLineWidth(STORY_LINESIZE);
				glVertexPointer (2, GL_FLOAT, 0, story9text);
				glColor4f(1.0,1.0,1.0,worldtime[0].getElapsed());
				glDrawArrays(GL_LINES, 0, story9mark[1]/2);
				drawCursor();
				if (!paused() && !gameover && worldtime[0].getElapsed() > 3)
					switchLevel(ID_WIN);
			} break;
			case ID_STORY10: {
				glLineWidth(STORY_LINESIZE);
				glVertexPointer (2, GL_FLOAT, 0, story10text);
				glColor4f(1.0,1.0,1.0,worldtime[0].getElapsed());
				glDrawArrays(GL_LINES, 0, story10mark[1]/2);
				drawCursor();
				if (!paused() && !gameover && worldtime[0].getElapsed() > 3)
					switchLevel(ID_WIN);
			} break;
			default: //ID_GAMEOVER
				if (delaytime.getElapsed() > 7) {
					storymode = false;
					switchLevel(ID_MAINMENU);
				}
				else if (delaytime.getElapsed() > 0.5) { 
					glLineWidth(7);
					glVertexPointer (2, GL_FLOAT, 0, gameovertext);
					glDrawArrays(GL_LINES, 0, gameovermark[1]/2);
					if (!storymode) {
						glLineWidth(4);
						glDrawArrays(GL_LINES, gameovermark[1]/2, (gameovermark[3]-gameovermark[1])/2);
					}
				}
		}
		
		///Draw title
		if (!disabled) {
			drawTitle();
			moveObjects();
		}
		
		///Draw timer
		if (!storymode && !disabled && !gameover && (gamemode > 0) && (gamemode <= ZONE_LIMIT)) { //strict limiter
			drawTimer();
		}
		
		///Shooting
		if (!gameover && gamemode > 0 && gamemode < ZONE_LIMIT && (spacepressed || autoshoot) && delaytime.getElapsed() > SHOT_DELAY) {
			QuadObj shot(xpos, ypos-7, 8, 20, 3);
			shot.setDirection(90);
			shot.setSpeed(12);
			Shots.add(shot);
			delaytime.resetTime();
		}
		
		///Draw borders
		glLineWidth(2);
		glColor4f(1.0,1.0,1.0,1.0);
		glVertexPointer (2, GL_FLOAT, 0, borders);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		
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
		Tr.setBegin();
		while ((!disabled) && (iter < Tr.size()) && (!gameover)) {
			if (Tr.getIValue().isMaterialised() && Tr.getIValue().isIn(Point(xpos, ypos))) {
				gameOver();
			}
			Tr.next();
			iter++;
		}
		iter = 0;
		Qu.setBegin();
		while ((!disabled) && (iter < Qu.size()) && (!gameover)) {
			if (Qu.getIValue().isMaterialised() && Qu.getIValue().isIn(Point(xpos, ypos))) {
				gameOver();
			}
			Qu.next();
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
		subSpw.setBegin();
		while ((!disabled) && (iter < subSpw.size()) && (!gameover)) {
			if (subSpw.getIValue().getObject()->isMaterialised() && subSpw.getIValue().getObject()->isIn(Point(xpos, ypos))) {
				gameOver();
			}
			subSpw.next();
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
