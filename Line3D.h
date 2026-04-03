// filename: Line3D.h 		(has-a-Point3D)
#ifndef LINE3D_H
#define LINE3D_H

#include <memory>
#include <ostream>  // for std::ostream
#include <string>   // for std::string 

#include "Line2D.h"		// subclass of Line2D
class Point3D; 			// forward declaration

class Line3D : public Line2D
{
	private:		// ( - )
		std::shared_ptr<Point3D> pt1;
		std::shared_ptr<Point3D> pt2;

	protected:		// ( # )
		void setLength();
		// Line3D inherits attribute length from Line2D
		// Line3D inherits method getScalarValue() from Line2D

	public:			// ( + )
		// constructor
		Line3D(std::shared_ptr<Point3D> p1, std::shared_ptr<Point3D> p2);
		
		void updateLength() { setLength(); }

		// getters
		std::shared_ptr<Point3D> getPt1() const;
		std::shared_ptr<Point3D> getPt2() const;

		// setters
		void setPt1(std::shared_ptr<Point3D> pt1);
		void setPt2(std::shared_ptr<Point3D> pt2);

		// overload operator
		bool operator==(const Line3D& other) const;
		
    	// operator<< overload
    	friend std::ostream& operator<<(std::ostream& os, const Line3D& line);
    	
    	// toString function
    	std::string toString() const;
    	
		// Comparator declarations
		static bool compareByPt1_ASC(const Line3D &a, const Line3D &b);
		static bool compareByPt1_DESC(const Line3D &a, const Line3D &b);

		static bool compareByPt2_ASC(const Line3D &a, const Line3D &b);
		static bool compareByPt2_DESC(const Line3D &a, const Line3D &b);

		static bool compareByLength_ASC(const Line3D &a, const Line3D &b);
		static bool compareByLength_DESC(const Line3D &a, const Line3D &b);
};

#endif
