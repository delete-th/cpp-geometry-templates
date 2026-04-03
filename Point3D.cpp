// filename: Point3D.cpp
#include "Point3D.h"

#include <string>
#include <vector>
#include <cmath>
#include <iostream>   
#include <iomanip>   
#include <sstream>   

using namespace std;

// constructor
Point3D::Point3D(int x, int y, int z)
	: Point2D(x, y) 
{
	this->z=z;
	
}


void Point3D::setDistFrOrigin()
{
	distFrOrigin = sqrt(x * x + y * y + z * z);
}

		
// getter
int Point3D::getZ() const
{
	return z;
}
		
// setter
void Point3D::setZ(int z)
{
	this->z=z;
}

bool Point3D::operator==(const Point3D& other) const {
    // Two 3D points are equal if x, y, and z match exactly
    return (x == other.x && y == other.y && z == other.z);
}

// operator<< overload
ostream& operator<<(ostream& os, const Point3D& pt) {
    os << "["
       << right << setw(4) << pt.getX() << ", "
       << right << setw(4) << pt.getY() << ", "
       << right << setw(4) << pt.getZ() << "]   "
       << left << fixed << setprecision(3)
       << pt.getScalarValue();
    return os;
}

// toString() uses operator<< to generate string
string Point3D::toString() const {
    stringstream ss;
    ss << *this;
    return ss.str();
}

// static comparators for sorting

    bool Point3D::compareByX_ASC(const shared_ptr<Point3D> &a, const shared_ptr<Point3D> &b) {
        if (a->getX() == b->getX()) {
            if (a->getY() == b->getY()) return a->getZ() < b->getZ();
            return a->getY() < b->getY();
        }
        return a->getX() < b->getX();
    }
    bool Point3D::compareByX_DESC(const shared_ptr<Point3D> &a, const shared_ptr<Point3D> &b) {
        if (a->getX() == b->getX()) {
            if (a->getY() == b->getY()) return a->getZ() > b->getZ();
            return a->getY() > b->getY();
        }
        return a->getX() > b->getX();
    }

    bool Point3D::compareByY_ASC(const shared_ptr<Point3D> &a, const shared_ptr<Point3D> &b) {
        if (a->getY() == b->getY()) return a->getX() < b->getX();
        return a->getY() < b->getY();
    }
    bool Point3D::compareByY_DESC(const shared_ptr<Point3D> &a, const shared_ptr<Point3D> &b) {
        if (a->getY() == b->getY()) return a->getX() > b->getX();
        return a->getY() > b->getY();
    }

    bool Point3D::compareByZ_ASC(const shared_ptr<Point3D> &a, const shared_ptr<Point3D> &b) {
        return a->getZ() < b->getZ();
    }
    bool Point3D::compareByZ_DESC(const shared_ptr<Point3D> &a, const shared_ptr<Point3D> &b) {
        return a->getZ() > b->getZ();
    }

    bool Point3D::compareByDist_ASC(const shared_ptr<Point3D> &a, const shared_ptr<Point3D> &b) {
        return a->getScalarValue() < b->getScalarValue();
    }
    bool Point3D::compareByDist_DESC(const shared_ptr<Point3D> &a, const shared_ptr<Point3D> &b) {
        return a->getScalarValue() > b->getScalarValue();
    }

