#ifndef QUADOBJ_HPP
#define QUADOBJ_HPP

#include "Object2D.hpp"

class QuadObj : public Object2D {
	protected:
		float dim1;
		float dim2;
	public:
		QuadObj(float x, float y, float w, float h, float dtime);
		QuadObj(float x, float y, float w, float h, float dtime, float mtime);
		QuadObj(float x, float y, float w, float h, float angle, float dtime, float mtime);
		virtual ~QuadObj();

		float getDim1() const;
		float getDim2() const;
		void setDim1(float w);
		void setDim2(float h);
		void redraw();
};

#endif
