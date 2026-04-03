// filename: Line2D.h 		(superclass of Line3D)
//						    (has-a-Point2D)
#ifndef LINE2D_H
#define LINE2D_H

#include <memory>
#include <ostream>  // for std::ostream
#include <string>   // for std::string 

class Point2D; 		// forward declaration

class Line2D
{
	private:
		std::shared_ptr<Point2D> pt1;
		std::shared_ptr<Point2D> pt2;

	protected:
		double length;

		// setter
		void setLength();

	public:
		// constructor
		Line2D(std::shared_ptr<Point2D> p1, std::shared_ptr<Point2D> p2);

		// destructor
		virtual ~Line2D() = default;
		
		void updateLength() { setLength(); }

		// getters
		std::shared_ptr<Point2D> getPt1() const;
		std::shared_ptr<Point2D> getPt2() const;
		double getScalarValue() const;

		// setters
		void setPt1(std::shared_ptr<Point2D> pt1);
		void setPt2(std::shared_ptr<Point2D> pt2);

		// overload operator
		bool operator==(const Line2D& other) const;
		
    	// operator<< overload
    	friend std::ostream& operator<<(std::ostream& os, const Line2D& line);
    	
    	// toString function
    	std::string toString() const;
    	
		// Comparator declarations
		static bool compareByPt1_ASC(const Line2D &a, const Line2D &b);
		static bool compareByPt1_DESC(const Line2D &a, const Line2D &b);

		static bool compareByPt2_ASC(const Line2D &a, const Line2D &b);
		static bool compareByPt2_DESC(const Line2D &a, const Line2D &b);

		static bool compareByLength_ASC(const Line2D &a, const Line2D &b);
		static bool compareByLength_DESC(const Line2D &a, const Line2D &b);
};



#endif
