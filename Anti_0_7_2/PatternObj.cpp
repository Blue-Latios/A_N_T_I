#include "PatternObj.hpp"

PatternObj::PatternObj(float x, float y, int num, int type) : Point(x, y) {
	objData = new Object2D*[num];
	n = 0;
	patterntype = type;
	speed = 0;
	direction = 0;
}
PatternObj::~PatternObj() {
}
void PatternObj::add(Object2D* obj) {
	objData[n] = obj;
	n++;
}
int PatternObj::getObjNum() const {
	return n;
}
Object2D** PatternObj::getObjData() {
	return objData;
}
float PatternObj::getSpeed() const {
	return speed;
}
float PatternObj::getDirection() const {
	return direction;
}
void PatternObj::setSpeed(float s) {
	speed = s;
}
void PatternObj::setDirection(float d) {
	direction = d;
}
bool PatternObj::isDead() const {
	int i = 0;
	while ((i < n) && (objData[i] == NULL)) {
		i++;
	}
	return (objData[i] == NULL);
}
void PatternObj::rotate(float ang) {
	ang = -ang;
	for (int i = 0; i < n; i++) {
		if (objData[i] != NULL) {
			float x = getX() + (objData[i]->getX() - getX())*cos(convertToRadian(ang)) - (objData[i]->getY() - getY())*sin(convertToRadian(ang));
			float y = getY() + (objData[i]->getX() - getX())*sin(convertToRadian(ang)) + (objData[i]->getY() - getY())*cos(convertToRadian(ang));
			objData[i]->setX(x);
			objData[i]->setY(y);
			objData[i]->setDirection(objData[i]->getDirection() - ang);
		}
	}
}
void PatternObj::checkMemberDead() {
	int i = 0;
	while (i < n) {
		if (objData[i] != NULL) {
			if (objData[i]->isDead()) {
				objData[i] = NULL;
				n--;
			} else
				i++;
		} else
			i++;
	}
}
