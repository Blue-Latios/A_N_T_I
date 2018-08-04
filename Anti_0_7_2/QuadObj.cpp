#include "QuadObj.hpp"

QuadObj::QuadObj(float x, float y, float w, float h, float dtime) : Object2D(x, y, 4, dtime) {
	dim1 = w;
	dim2 = h;
	this->redraw();
}
QuadObj::QuadObj(float x, float y, float w, float h, float dtime, float mtime) : Object2D(x, y, 4, dtime, mtime) {
	dim1 = w;
	dim2 = h;
	this->redraw();
}
QuadObj::QuadObj(float x, float y, float w, float h, float angle, float dtime, float mtime) : Object2D(x, y, 4, angle, dtime, mtime) {
	dim1 = w;
	dim2 = h;
	this->redraw();
}
QuadObj::~QuadObj() {
}
float QuadObj::getDim1() const {
	return dim1;
}
float QuadObj::getDim2() const {
	return dim2;
}
void QuadObj::setDim1(float w) {
	dim1 = w;
}
void QuadObj::setDim2(float h) {
	dim2 = h;
}
void QuadObj::redraw() {
	pointData[0] = widthConvert(getX() + dim1*cos(convertToRadian(angle))/2 - dim2*sin(convertToRadian(angle))/2);
	pointData[1] = heightConvert(getY() - dim1*sin(convertToRadian(angle))/2 - dim2*cos(convertToRadian(angle))/2);
	
	pointData[2] = widthConvert(getX() + dim1*cos(convertToRadian(angle))/2 + dim2*sin(convertToRadian(angle))/2);
	pointData[3] = heightConvert(getY() - dim1*sin(convertToRadian(angle))/2 + dim2*cos(convertToRadian(angle))/2);
	
	pointData[4] = widthConvert(getX() - dim1*cos(convertToRadian(angle))/2 + dim2*sin(convertToRadian(angle))/2);
	pointData[5] = heightConvert(getY() + dim1*sin(convertToRadian(angle))/2 + dim2*cos(convertToRadian(angle))/2);
	
	pointData[6] = widthConvert(getX() - dim1*cos(convertToRadian(angle))/2 - dim2*sin(convertToRadian(angle))/2);
	pointData[7] = heightConvert(getY() + dim1*sin(convertToRadian(angle))/2 - dim2*cos(convertToRadian(angle))/2);

}
