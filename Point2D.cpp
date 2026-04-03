// filename: Point2D.cpp 		(superclass of Point3D)
#include "Point2D.h"

#include <string>
#include <cmath>
#include <iostream>   
#include <iomanip>   
#include <sstream>   

using namespace std;

// constructor
Point2D::Point2D(int x, int y)
{
	this->x = x;
	this->y	= y;
	
}

// destructor
Point2D::~Point2D()	{}

// getters
int Point2D::getX() const
{  return x;  }

int Point2D::getY() const
{  return y;  }


double Point2D::getScalarValue() const
{  return distFrOrigin;  }


// setters
void Point2D::setX(int x)
{
	this->x = x;
}

void Point2D::setY(int y)
{
	this->y = y;
}

void Point2D::setDistFrOrigin()
{
	distFrOrigin = sqrt(x * x + y * y);
}

// methods
bool Point2D::operator==(const Point2D& other) const {
    // Two points are equal if both x and y coordinates match exactly
    return (x == other.x && y == other.y);
}

// operator<< overload
ostream& operator<<(ostream& os, const Point2D& pt) {
    os << "["
       << right << setw(4) << pt.x << ", "
       << right << setw(4) << pt.y << "]   "
       << left << fixed << setprecision(3)
       << pt.getScalarValue();
    return os;
}

// toString() uses operator<< to generate string
string Point2D::toString() const {
    stringstream ss;
    ss << *this;
    return ss.str();
}

// static comparators for sorting

    bool Point2D::compareByX_ASC(const shared_ptr<Point2D> &a, const shared_ptr<Point2D> &b) {
        if (a->getX() == b->getX()) return a->getY() < b->getY();
        return a->getX() < b->getX();
    }
    bool Point2D::compareByX_DESC(const shared_ptr<Point2D> &a, const shared_ptr<Point2D> &b) {
        if (a->getX() == b->getX()) return a->getY() > b->getY();
        return a->getX() > b->getX();
    }

    bool Point2D::compareByY_ASC(const shared_ptr<Point2D> &a, const shared_ptr<Point2D> &b) {
        if (a->getY() == b->getY()) return a->getX() < b->getX();
        return a->getY() < b->getY();
    }
    bool Point2D::compareByY_DESC(const shared_ptr<Point2D> &a, const shared_ptr<Point2D> &b) {
        if (a->getY() == b->getY()) return a->getX() > b->getX();
        return a->getY() > b->getY();
    }

    bool Point2D::compareByDist_ASC(const shared_ptr<Point2D> &a, const shared_ptr<Point2D> &b) {
        return a->getScalarValue() < b->getScalarValue();
    }
    bool Point2D::compareByDist_DESC(const shared_ptr<Point2D> &a, const shared_ptr<Point2D> &b) {
        return a->getScalarValue() > b->getScalarValue();
    }


