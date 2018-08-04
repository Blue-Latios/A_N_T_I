#include "Dimensions.hpp"

double Dimensions::width;
double Dimensions::height;

Dimensions::Dimensions() {
}
Dimensions::Dimensions(double w, double h) {
	width = w;
	height = h;
}
Dimensions::~Dimensions() {
}
double Dimensions::getWidth() const {
	return width;
}
double Dimensions::getHeight() const {
	return height;
}
