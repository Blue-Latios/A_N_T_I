#include "Point.hpp"

Point::Point() {
	x = 0;
	y = 0;
}
Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
}
Point::Point(const Point& P) {
	x = P.x;
	y = P.y;
}
Point::~Point() {
}
Point& Point::operator=(const Point& P) {
	this->x = P.x;
	this->y = P.y;
	return *this;
}
ofstream& operator << (ofstream& out, Point &P) {
	out << P.x << '\n';
	out << P.y << '\n';
	return out;
}
ifstream& operator >> (ifstream& in, Point &P) {
	in >> P.x;
	in >> P.y;
	return in;
}

double Point::getX() const {
	return x;
}
double Point::getY() const {
	return y;
}
void Point::setX(double x) {
	this->x = x;
}
void Point::setY(double y) {
	this->y = y;
}
double Point::distanceSquaredTo(const Point& P) {
	return (x-P.x)*(x-P.x) + (y-P.y)*(y-P.y);
}
double Point::angleTo(const Point& P) {
	return atan2((P.getY()-getY()), (P.getX()-getX()))*180/M_PI;
}
bool Point::operator ==(const Point& P) {
	return ((x == P.x) && (y == P.y));
}
double convertToRadian(double angle) {
	return angle*M_PI/180;
}
