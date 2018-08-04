#ifndef OBJECT2D_HPP
#define OBJECT2D_HPP

#include <GLFW/glfw3.h>
#include <cmath>
#include "Dimensions.hpp"
#include "Point.hpp"
#include "Time.hpp"

class Object2D : public Dimensions, public Point {
	protected:
		GLfloat *pointData;
		int n; //number of Points
		
		float speed;
		float direction; //0 is East, counterclockwise
		Time lifetime;
		float deathtime;
		float mtime; //time to materialise
	public:
		Object2D(float x, float y, int size, float dtime);
		Object2D(float x, float y, int size, float dtime, float mtime);
		virtual ~Object2D() = 0;
		float getSpeed() const;
		float getDirection() const;
		void setSpeed(float s);
		void setTime(const Time& t);
		void setDirection(float d);
		Time& getLifeTime();
		bool isMaterialised() const;
		GLfloat* getPointData();
		int getNPoints() const;
		virtual void redraw() = 0;
		void move();
		bool isIn(const Point& P);
};

double widthConvert(double w);
double heightConvert(double h);

#endif
