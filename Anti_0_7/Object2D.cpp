#include "Object2D.hpp"

Object2D::Object2D(float x, float y, int size, float dtime) : Point(x, y) {
	deathtime = dtime;
	mtime = 0;
	speed = 0;
	direction = 0;
	n = size;
	pointData = new GLfloat[n*2];
	angle = 0;
}
Object2D::Object2D(float x, float y, int size, float dtime, float mtime) : Point(x, y) {
	deathtime = dtime;
	this->mtime = mtime;
	speed = 0;
	direction = 0;
	n = size;
	pointData = new GLfloat[n*2];
	angle = 0;
}
Object2D::Object2D(float x, float y, int size, float a, float dtime, float mtime) {
	deathtime = dtime;
	this->mtime = mtime;
	speed = 0;
	direction = 0;
	n = size;
	pointData = new GLfloat[n*2];
	angle = a;
}
Object2D::~Object2D() {
}
Object2D& Object2D::operator =(const Object2D& O) {
	n = O.n;
	pointData = new GLfloat[n*2];
	for (int i = 0; i < n; i++)
		pointData[i] = O.pointData[i];
	for (int i = 0; i < 3; i++)
		colorData[i] = O.colorData[i];
	speed = O.speed;
	direction = O.direction;
	lifetime = O.lifetime;
	deathtime = O.deathtime;
	mtime = O.mtime;
	angle = O.angle;
	return *this;
}
float Object2D::getSpeed() const {
	return speed;
}
float Object2D::getAngle() const {
	return angle;
}
float Object2D::getDirection() const {
	return direction;
}
void Object2D::setSpeed(float s) {
	speed = s;
}
void Object2D::setAngle(float a) {
	angle = a;
}
void Object2D::setTime(long ms) {
	lifetime.setTime(ms);
}
void Object2D::markTime() {
	lifetime.markTime();
}
void Object2D::continueTime() {
	lifetime.continueTime();
}
void Object2D::setDirection(float d) {
	direction = d;
}
float Object2D::getTimeElapsed() {
	return lifetime.getElapsed();
}
bool Object2D::isDead() const {
	return (lifetime.getElapsed() > deathtime);
}
bool Object2D::isMaterialised() const {
	return (lifetime.getElapsed() > mtime);
}
GLfloat* Object2D::getPointData() {
	return pointData;
}
GLfloat* Object2D::getColorData() {
	return colorData;
}
int Object2D::getNPoints() const {
	return n;
}
void Object2D::move() {
	setX(getX() + speed*cos(convertToRadian(direction)));
	setY(getY() - speed*sin(convertToRadian(direction)));
}
bool Object2D::isIn(const Point& P) {
	int i = 0;
	while ((i < n-1) && ((widthConvert(P.getX()) - pointData[i*2])*(pointData[i*2+3] - pointData[i*2+1]) - (heightConvert(P.getY()) - pointData[i*2+1])*(pointData[i*2+2] - pointData[i*2]) >= 0)) {
		i++;
	}
	return (((widthConvert(P.getX()) - pointData[i*2])*(pointData[1] - pointData[i*2+1]) - (heightConvert(P.getY()) - pointData[i*2+1])*(pointData[0] - pointData[i*2]) >= 0) && (i == n-1));
}

double widthConvert(double w) {
	return (2*w - Dimensions().getWidth()) / Dimensions().getWidth();
}
double heightConvert(double h) {
	return -(2*h - Dimensions().getHeight()) / Dimensions().getHeight();
}
