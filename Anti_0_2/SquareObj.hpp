#ifndef SQUAREOBJ_HPP
#define SQUAREOBJ_HPP

#include "Object2D.hpp"

class SquareObj : public Object2D {
	protected:
		float radius;
		float angle;
	public:
		SquareObj(float x, float y, float side, float dtime);
		SquareObj(float x, float y, float side, float dtime, float mtime);
		SquareObj(float x, float y, float side, float angle, float dtime, float mtime);
		virtual ~SquareObj();

		float getRadius() const;
		float getAngle() const;
		void setRadius(float r);
		void setAngle(float a);
		void redraw();
};

#endif
