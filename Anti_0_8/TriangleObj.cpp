#include "TriangleObj.hpp"

TriangleObj::TriangleObj(float x, float y, float w, float h, float dtime) : Object2D(x, y, 3, dtime) {
	dim1 = w;
	dim2 = h;
	this->redraw();
}
TriangleObj::TriangleObj(float x, float y, float w, float h, float dtime, float mtime) : Object2D(x, y, 3, dtime, mtime) {
	dim1 = w;
	dim2 = h;
	this->redraw();
}
TriangleObj::TriangleObj(float x, float y, float w, float h, float angle, float dtime, float mtime) : Object2D(x, y, 3, angle, dtime, mtime) {
	dim1 = w;
	dim2 = h;
	this->redraw();
}
TriangleObj::~TriangleObj() {
}
float TriangleObj::getDim1() const {
	return dim1;
}
float TriangleObj::getDim2() const {
	return dim2;
}
void TriangleObj::setDim1(float w) {
	dim1 = w;
}
void TriangleObj::setDim2(float h) {
	dim2 = h;
}
void TriangleObj::redraw() {
	pointData[0] = widthConvert(getX() + dim1*cos(convertToRadian(angle))*2/3);
	pointData[1] = heightConvert(getY() - dim1*sin(convertToRadian(angle))*2/3);
	
	pointData[2] = widthConvert(getX() - dim1*cos(convertToRadian(angle))/3 + dim2*sin(convertToRadian(angle))/2);
	pointData[3] = heightConvert(getY() + dim1*sin(convertToRadian(angle))/3 + dim2*cos(convertToRadian(angle))/2);
	
	pointData[4] = widthConvert(getX() - dim1*cos(convertToRadian(angle))/3 - dim2*sin(convertToRadian(angle))/2);
	pointData[5] = heightConvert(getY() + dim1*sin(convertToRadian(angle))/3 - dim2*cos(convertToRadian(angle))/2);
}
