#ifndef TRIANGLEOBJ_HPP
#define TRIANGLEOBJ_HPP

#include "Object2D.hpp"

class TriangleObj : public Object2D {
	protected:
		float dim1; //half width (triangle facing right standard)
		float dim2; //half height
	public:
		TriangleObj(float x, float y, float w, float h, float dtime);
		TriangleObj(float x, float y, float w, float h, float dtime, float mtime);
		TriangleObj(float x, float y, float w, float h, float angle, float dtime, float mtime);
		virtual ~TriangleObj();

		float getDim1() const;
		float getDim2() const;
		void setDim1(float w);
		void setDim2(float h);
		void redraw();
};


#endif
