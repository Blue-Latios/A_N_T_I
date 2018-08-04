#ifndef PATTERNOBJ_HPP
#define PATTERNOBJ_HPP

///class pembantu khusus game

#include "Object2D.hpp"
#include "Point.hpp"

class PatternObj : public Point {
	private:
		int n; //Number of bound objects
		Object2D** objData; //Pointer to ObjDatas
		float speed;
		float direction; //0 is East, counterclockwise
		int patterntype;
	public:
		PatternObj(float x, float y, int num, int type);
		virtual ~PatternObj();
		
		void add(Object2D* obj);
		int getObjNum() const;
		Object2D** getObjData();
		float getSpeed() const;
		float getDirection() const;
		void setSpeed(float s);
		void setDirection(float d);
		void move();
		void rotate(float ang);
		bool isDead() const;
};

#endif
