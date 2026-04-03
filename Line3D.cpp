// filename: Line3D.cpp 		(has-a-Point3D)
#include "Line3D.h"
#include "Point3D.h"

#include <memory> 
#include <cmath> 
#include <iostream>   
#include <iomanip>   
#include <sstream>   
#include <string>


using namespace std;

Line3D::Line3D(shared_ptr<Point3D> p1, shared_ptr<Point3D> p2)
    : Line2D(nullptr, nullptr), pt1(p1), pt2(p2) { }

// protected setter
void Line3D::setLength()
{
    // Compute distance between pt1 and pt2 in 3D
    double dx = pt2->getX() - pt1->getX();
    double dy = pt2->getY() - pt1->getY();
    double dz = pt2->getZ() - pt1->getZ();
    length = sqrt(dx*dx + dy*dy + dz*dz);
}

// getters
shared_ptr<Point3D> Line3D::getPt1() const { return pt1; }
shared_ptr<Point3D> Line3D::getPt2() const { return pt2; }

// setters
void Line3D::setPt1(shared_ptr<Point3D> pt) { pt1 = pt; }
void Line3D::setPt2(shared_ptr<Point3D> pt) { pt2 = pt; }

// overload operator
bool Line3D::operator==(const Line3D& other) const {
    return ((*pt1 == *other.pt1 && *pt2 == *other.pt2) ||
        	(*pt1 == *other.pt2 && *pt2 == *other.pt1));
}

// Line3D operator<< overload
ostream& operator<<(ostream& os, const Line3D& line) {
    os << "["
       << right << setw(4) << line.getPt1()->getX() << ", "
       << right << setw(4) << line.getPt1()->getY() << ", "
       << right << setw(4) << line.getPt1()->getZ() << "]   "
       << "["
       << right << setw(4) << line.getPt2()->getX() << ", "
       << right << setw(4) << line.getPt2()->getY() << ", "
       << right << setw(4) << line.getPt2()->getZ() << "]   "
       << left << fixed << setprecision(3)
       << line.getScalarValue();
    return os;
}

// Line3D toString()
string Line3D::toString() const {
    stringstream ss;
    ss << *this;
    return ss.str();
}


// static comparators for sorting
    bool Line3D::compareByPt1_ASC(const Line3D &a, const Line3D &b) {
        if (a.getPt1()->getX() == b.getPt1()->getX())
            return a.getPt1()->getY() < b.getPt1()->getY();
        return a.getPt1()->getX() < b.getPt1()->getX();
    }
    bool Line3D::compareByPt1_DESC(const Line3D &a, const Line3D &b) {
        if (a.getPt1()->getX() == b.getPt1()->getX())
            return a.getPt1()->getY() > b.getPt1()->getY();
        return a.getPt1()->getX() > b.getPt1()->getX();
    }

    bool Line3D::compareByPt2_ASC(const Line3D &a, const Line3D &b) {
        if (a.getPt2()->getX() == b.getPt2()->getX())
            return a.getPt2()->getY() < b.getPt2()->getY();
        return a.getPt2()->getX() < b.getPt2()->getX();
    }
    bool Line3D::compareByPt2_DESC(const Line3D &a, const Line3D &b) {
        if (a.getPt2()->getX() == b.getPt2()->getX())
            return a.getPt2()->getY() > b.getPt2()->getY();
        return a.getPt2()->getX() > b.getPt2()->getX();
    }

    bool Line3D::compareByLength_ASC(const Line3D &a, const Line3D &b) {
        return a.getScalarValue() < b.getScalarValue();
    }
    bool Line3D::compareByLength_DESC(const Line3D &a, const Line3D &b) {
        return a.getScalarValue() > b.getScalarValue();
    }


