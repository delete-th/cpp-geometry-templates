// filename: Point2D.h 		(superclass of Point3D)
#ifndef POINT2D_H
#define POINT2D_H

#include <ostream>  // for std::ostream
#include <string>   // for std::string 
#include <memory>

class Point2D
{
	protected:		// ( # )
		int x;
		int y;
		double distFrOrigin;
		
		// setter
		void setDistFrOrigin ();
		
	
	public:			// ( + )
		// constructor
		Point2D(int x, int y);
		
		// destructor
		virtual ~Point2D();
		
		void updateDistance() { setDistFrOrigin(); }	// public method in order
														// to set the distance from outside
		
		// getters
		int getX() const;
		int getY() const;
		double getScalarValue() const;
		
		// setters
		void setX(int x);
		void setY(int y);
		
		// overload== operator
    	bool operator==(const Point2D& other) const;
    	
    	// operator<< overload
    	friend std::ostream& operator<<(std::ostream& os, const Point2D& pt);
    	
    	// toString function
    	std::string toString() const;
    	
    	// Static comparator functions for sorting shared_ptr<Point2D>
		static bool compareByX_ASC(const std::shared_ptr<Point2D>& a, const std::shared_ptr<Point2D>& b);
		static bool compareByX_DESC(const std::shared_ptr<Point2D>& a, const std::shared_ptr<Point2D>& b);

		static bool compareByY_ASC(const std::shared_ptr<Point2D>& a, const std::shared_ptr<Point2D>& b);
		static bool compareByY_DESC(const std::shared_ptr<Point2D>& a, const std::shared_ptr<Point2D>& b);

		static bool compareByDist_ASC(const std::shared_ptr<Point2D>& a, const std::shared_ptr<Point2D>& b);
		static bool compareByDist_DESC(const std::shared_ptr<Point2D>& a, const std::shared_ptr<Point2D>& b);

};


#endif
