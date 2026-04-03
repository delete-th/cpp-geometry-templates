// filename: Line2D.cpp 		(superclass of Line3D)
//								(has-a-Point2D)
#include "Line2D.h"
#include "Point2D.h"

#include <memory> 
#include <cmath> 
#include <iostream>   
#include <iomanip>   
#include <sstream>   
#include <string>


using namespace std;


// constructor 
Line2D::Line2D(shared_ptr<Point2D> p1, shared_ptr<Point2D> p2)
    : pt1(p1), pt2(p2)
{
}

// getters
shared_ptr<Point2D> Line2D::getPt1() const { return pt1; }
shared_ptr<Point2D> Line2D::getPt2() const { return pt2; }

double Line2D::getScalarValue() const { return length; }

// setters
void Line2D::setPt1(shared_ptr<Point2D> pt) { pt1 = pt; }
void Line2D::setPt2(shared_ptr<Point2D> pt) { pt2 = pt; }

// compute length
void Line2D::setLength()
{
    double dx = pt2->getX() - pt1->getX();
    double dy = pt2->getY() - pt1->getY();
    length = sqrt(dx*dx + dy*dy);
}

// overload operator
bool Line2D::operator==(const Line2D& other) const
{
    return ((*pt1 == *other.pt1 && *pt2 == *other.pt2) ||
        	(*pt1 == *other.pt2 && *pt2 == *other.pt1));
}

// Line2D operator<< overload
ostream& operator<<(ostream& os, const Line2D& line) {
    os << "["
       << right << setw(4) << line.getPt1()->getX() << ", "
       << right << setw(4) << line.getPt1()->getY() << "]   "
       << "["
       << right << setw(4) << line.getPt2()->getX() << ", "
       << right << setw(4) << line.getPt2()->getY() << "]   "
       << left << fixed << setprecision(3)
       << line.getScalarValue();
    return os;
}

// Line2D toString()
string Line2D::toString() const {
    stringstream ss;
    ss << *this;
    return ss.str();
}


// static comparators for sorting
    bool Line2D::compareByPt1_ASC(const Line2D &a, const Line2D &b) {
        if (a.getPt1()->getX() == b.getPt1()->getX())
            return a.getPt1()->getY() < b.getPt1()->getY();
        return a.getPt1()->getX() < b.getPt1()->getX();
    }
    bool Line2D::compareByPt1_DESC(const Line2D &a, const Line2D &b) {
        if (a.getPt1()->getX() == b.getPt1()->getX())
            return a.getPt1()->getY() > b.getPt1()->getY();
        return a.getPt1()->getX() > b.getPt1()->getX();
    }

    bool Line2D::compareByPt2_ASC(const Line2D &a, const Line2D &b) {
        if (a.getPt2()->getX() == b.getPt2()->getX())
            return a.getPt2()->getY() < b.getPt2()->getY();
        return a.getPt2()->getX() < b.getPt2()->getX();
    }
    bool Line2D::compareByPt2_DESC(const Line2D &a, const Line2D &b) {
        if (a.getPt2()->getX() == b.getPt2()->getX())
            return a.getPt2()->getY() > b.getPt2()->getY();
        return a.getPt2()->getX() > b.getPt2()->getX();
    }

    bool Line2D::compareByLength_ASC(const Line2D &a, const Line2D &b) {
        return a.getScalarValue() < b.getScalarValue();
    }
    bool Line2D::compareByLength_DESC(const Line2D &a, const Line2D &b) {
        return a.getScalarValue() > b.getScalarValue();
    }


