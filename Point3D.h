// filename: Point3D.h
#ifndef POINT3D_H
#define POINT3D_H

#include <ostream>  // for std::ostream
#include <string>   // for std::string 
#include <memory>

#include "Point2D.h"		// subclass of Point2D

class Point3D : public Point2D
{
	protected:
		int z;
		
		void setDistFrOrigin();
		
	public:
		// constructor
		Point3D(int x, int y, int z);
		
		void updateDistance() { setDistFrOrigin(); }
		
		// getter
		int getZ() const;
		
		// setter
		void setZ(int z);
		
		// overload operator
    	bool operator==(const Point3D& other) const;
    	
    	// operator<< overload
    	friend std::ostream& operator<<(std::ostream& os, const Point2D& pt);
    	
    	// toString function
    	std::string toString() const;
    	
    	// Static comparator functions for sorting shared_ptr<Point3D>
		static bool compareByX_ASC(const std::shared_ptr<Point3D>& a, const std::shared_ptr<Point3D>& b);
		static bool compareByX_DESC(const std::shared_ptr<Point3D>& a, const std::shared_ptr<Point3D>& b);

		static bool compareByY_ASC(const std::shared_ptr<Point3D>& a, const std::shared_ptr<Point3D>& b);
		static bool compareByY_DESC(const std::shared_ptr<Point3D>& a, const std::shared_ptr<Point3D>& b);

		static bool compareByZ_ASC(const std::shared_ptr<Point3D>& a, const std::shared_ptr<Point3D>& b);
		static bool compareByZ_DESC(const std::shared_ptr<Point3D>& a, const std::shared_ptr<Point3D>& b);

		static bool compareByDist_ASC(const std::shared_ptr<Point3D>& a, const std::shared_ptr<Point3D>& b);
		static bool compareByDist_DESC(const std::shared_ptr<Point3D>& a, const std::shared_ptr<Point3D>& b);
		
};




#endif
