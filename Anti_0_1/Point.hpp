#ifndef POINT_HPP
#define POINT_HPP

#include <fstream>
#include <cmath>
using namespace std;

class Point {
	private:
		double x, y;
	public:
		Point(); //default ctor
		Point(double x, double y); //ctor berparameter
		Point(const Point& P); //cctor
		virtual ~Point(); //dtor
		Point& operator=(const Point& P); //operator assignment
		friend ofstream& operator << (ofstream& out, Point &P);
		friend ifstream& operator >> (ifstream& in, Point &P);
		
		//Methods
		double getX() const;
		double getY() const;
		void setX(double x);
		void setY(double y);
		double distanceSquaredTo(const Point& P); //Jarak titik ini ke titik yang lain
		double angleTo(const Point& P); //sudut dari this ke To, East 0 derajat, North 90 derajat
		bool operator ==(const Point& P); //kesamaan
};

double convertToRadian(double angle); //mengubah derajat ke radian

#endif
