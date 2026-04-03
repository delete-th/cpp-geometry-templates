#include <iostream>      // cout, cin
#include <fstream>       // ifstream
#include <string>        // string
#include <vector>        // vector
#include <unordered_set> // unordered_set
#include <sstream>       // stringstream
#include <cstdlib>       // stoi
#include <cctype>        // isspace
#include <memory>
#include <algorithm>


#include "MyTemplates.h"
#include "Functions.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

using namespace std;

// Full Name: Thea Gardiola Saguid
// UOW Number: 8691836
// Assignment 3

// some function prototypes
// <here>


// persistent state sorting & filter variables
string curFilter = "Point2D";
string curSortCrit = "X-ordinate";
string curSortOrd = "ASC";


// displays assignment 3 menu
void displayMenu()
{
	cout << "Student ID: 8691836" << endl;
	cout << "Student Name: Thea Gardiola Saguid" << endl;
	cout << "------------------------------------" << endl;
	cout << "Welcome to Assn3 program!" << endl;
	cout << endl;
	
	cout << "1)   Read in data" << endl;
	cout << "2)   Specify filtering criteria (current : " << curFilter << ")" 
														  << endl;
	cout << "3)   Specify sorting criteria (current : " << curSortCrit << ")" 
														<< endl;
	cout << "4)   Specify sorting order (current : " << curSortOrd << ")" 
													 << endl;
	cout << "5)   View data"<< endl;
	cout << "6)   Store data"<< endl;
	cout << "7)   Exit"<< endl;

	cout << endl;
	cout << "Please enter your choice: ";

}

// global vectors of objects
// storage for points specified in the file
vector<shared_ptr<Point2D>> point2DVec;		
vector<shared_ptr<Point3D>> point3DVec;
// storage for points not in file but needed for lines
vector<shared_ptr<Point2D>> point2DNotInFile;
vector<shared_ptr<Point3D>> point3DNotInFile;
// storage for lines specified in the file
vector<Line2D> line2DVec;
vector<Line3D> line3DVec;

// === helper functions ===

// split line into top-level parts (ignore commas inside brackets)
vector<string> splitTopLevel(const string& line) {
    vector<string> parts;
    string current;
    int bracketLevel = 0;

    for (char c : line) {
        if (c == '[') bracketLevel++;
        else if (c == ']') bracketLevel--;

        if (c == ',' && bracketLevel == 0) {
            parts.push_back(current);
            current.clear();
        } else current.push_back(c);
    }
    if (!current.empty()) parts.push_back(current);
    
    // trim spaces
    for (auto& p : parts) {
        p.erase(0, p.find_first_not_of(' '));
        p.erase(p.find_last_not_of(' ') + 1);
    }

    return parts;
}

// remove brackets and spaces
string stripBrackets(const string& s) {
    string t;
    for (char c : s) if (c != '[' && c != ']' && !isspace(c)) t.push_back(c);
    return t;
}

// convert "[x, y]" or "[x, y, z]" into vector<int>
vector<int> parseCoordsInt(const string& coordStr) {
    string cleaned = stripBrackets(coordStr);
    vector<string> parts;
    stringstream ss(cleaned);
    string item;

    while (getline(ss, item, ',')) {
        item.erase(0, item.find_first_not_of(' '));
        item.erase(item.find_last_not_of(' ') + 1);
        parts.push_back(item);
    }

    vector<int> coords;
    for (auto& p : parts) coords.push_back(stoi(p));
    return coords;
}

// search for existing Point2D or create new one
shared_ptr<Point2D> findOrCreatePoint2D(int x, int y, bool fromFile = false) {
    Point2D temp(x, y);

    // check main vector first
    for (auto& p : point2DVec)
        if (*p == temp) return p;

    // check not-in-file vector
    for (auto& p : point2DNotInFile)
        if (*p == temp) return p;
	// if not found from either vector, make the point object 
    auto p = make_shared<Point2D>(x, y);
	
    if (fromFile)
        point2DVec.push_back(p);
    else	// put the notFound point to point2DNotInFile vector
        point2DNotInFile.push_back(p);

    return p;
}


// search for existing Point3D or create new one
shared_ptr<Point3D> findOrCreatePoint3D(int x, int y, int z, bool fromFile = false) {
    Point3D temp(x, y, z);
	// check if point is in point3DVec, if yes, return the point
    for (auto& p : point3DVec)
        if (*p == temp) return p;
	// check if point is in point3DNotInFile, if yes, return the point
    for (auto& p : point3DNotInFile)
        if (*p == temp) return p;
	// if not found from either vector, make the point object 
    auto p = make_shared<Point3D>(x, y, z);
	
    if (fromFile)
        point3DVec.push_back(p);
    else	    	// put the notFound point to point3DNotInFile vector
        point3DNotInFile.push_back(p);

    return p;
}


// remove duplicate lines in the file
vector<string> cleanDuplicates(const vector<string>& tempStorage) {
    vector<string> cleaned;
    unordered_set<string> seen;
    for (const auto& line : tempStorage) {
        if (seen.find(line) == seen.end()) {
            cleaned.push_back(line);
            seen.insert(line);
        }
    }
    return cleaned;
}

// create point objects first, then lines
void makeObject(const vector<string>& cleanLines) {
    // --- PASS 1: Points ---
    for (auto& line : cleanLines) {
        vector<string> parts = splitTopLevel(line);

		if (parts[0] == "Point2D") {
			auto coords = parseCoordsInt(parts[1]);
			findOrCreatePoint2D(coords[0], coords[1], true); // true = from file
		} else if (parts[0] == "Point3D") {
			auto coords = parseCoordsInt(parts[1]);
			findOrCreatePoint3D(coords[0], coords[1], coords[2], true); // true = from file
		}

    }

    // --- PASS 2: Lines ---
    for (auto& line : cleanLines) {
        vector<string> parts = splitTopLevel(line);

        if (parts[0] == "Line2D") {
            auto coords1 = parseCoordsInt(parts[1]);
            auto coords2 = parseCoordsInt(parts[2]);
			// find point objects already stored from the txt file
			// use as shared pointer 
            auto p1 = findOrCreatePoint2D(coords1[0], coords1[1]);
            auto p2 = findOrCreatePoint2D(coords2[0], coords2[1]);
            Line2D newLine(p1, p2);
			// checks line duplicates
            if (std::find(line2DVec.begin(), line2DVec.end(), newLine) == line2DVec.end())
                line2DVec.push_back(newLine);

        } else if (parts[0] == "Line3D") {
            auto coords1 = parseCoordsInt(parts[1]);
            auto coords2 = parseCoordsInt(parts[2]);
			// find point objects already stored from the txt file
			// use as shared pointer 
            auto p1 = findOrCreatePoint3D(coords1[0], coords1[1], coords1[2]);
            auto p2 = findOrCreatePoint3D(coords2[0], coords2[1], coords2[2]);
            Line3D newLine(p1, p2);
			// checks line duplicates
            if (std::find(line3DVec.begin(), line3DVec.end(), newLine) == line3DVec.end())
                line3DVec.push_back(newLine);
        }
    }
}

void updateDistancesAndLengths() {
    // Update distances for Point2D objects
    for (auto& p : point2DVec) {
        p->updateDistance();
    }

    // Update distances for Point3D objects
    for (auto& p : point3DVec) {
        p->updateDistance();
    }

    // Update lengths for Line2D objects
    for (auto& l : line2DVec) {
        l.updateLength();
    }

    // Update lengths for Line3D objects
    for (auto& l : line3DVec) {
        l.updateLength();
    }
}

// === end of helper functions ===

// === option1: read file ===
void option1() {
    string filename;
    cout << "\nPlease enter filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "\nCan't open file.\n";
        return;
    }

    vector<string> tempStorage;
    string line;
    while (getline(file, line)) {
    	// skip if empty line or comment line
    	if (line.empty() || line.substr(0,2) == "//") continue;
        tempStorage.push_back(line);
    }
	
	// clean duplicates from txt file
    vector<string> cleanLines = cleanDuplicates(tempStorage);
	// make objects from the processed lines
    makeObject(cleanLines);
    // set their distances and lengths
    updateDistancesAndLengths();
    
	cout << endl;
    cout << tempStorage.size() << " records read successfully!\n";
    cout << "Loaded "
         << point2DVec.size() << " Point2D, "
         << point3DVec.size() << " Point3D, "
         << line2DVec.size() << " Line2D, "
         << line3DVec.size() << " Line3D objects.\n\n";
    cout << "Going back to main menu ..." << endl << endl;
}


// updated function
void updateCurSortCrit(const std::string& newFilter) {
	char prevType = curFilter[0];
    char newType = (newFilter[0] == 'P') ? 'P' : (newFilter[0] == 'L') ? 'L' : ' ';

    // only update curSortCrit if type changes (P <-> L)
    if (prevType != ' ' && newType != ' ' && prevType != newType) {
        switch (newType) {
            case 'P':
                curSortCrit = "X-ordinate"; // default for Points
                break;
            case 'L':
                curSortCrit = "Pt. 1";      // default for Lines
                break;
        }
    }

}


// [Specify filtering criteria]
void option2 ()
{
	cout << "[ Specifying filtering criteria (current: " << curFilter 
		 << ") ]" << endl << endl;
	cout << "    a)    Point2D records"<< endl;
	cout << "    b)    Point3D records" << endl;
	cout << "    c)    Line2D records" << endl;
	cout << "    d)    Line3D records" << endl << endl;
	cout << "    Please enter your criteria (a—d): ";
	
	char choice;
	cin >> choice;
	choice = tolower(choice);	
	
	string newFilter;
	switch(choice) {
		case 'a': newFilter = "Point2D"; break;
		case 'b': newFilter = "Point3D"; break;
		case 'c': newFilter = "Line2D"; break;
		case 'd': newFilter = "Line3D"; break;
		default: cout << "    Invalid filter criteria." 
		              << endl << endl; break;
	}
	
    // update curSortCrit based on type change
    updateCurSortCrit(newFilter);
    curFilter = newFilter; // update the filter itself
	
	cout << "    Filter criteria successfully set to '" 
	     << curFilter << "'!" << endl << endl;
}


// [Specify sorting criteria]
void option3 ()
{
    cout << "[ Specifying sorting criteria (current: " << curSortCrit 
         << ") ]" << endl << endl;

    // show submenu depending on curFilter
    if (curFilter == "Point2D") {
        cout << "    a)    X ordinate value    (default)" << endl;
        cout << "    b)    Y ordinate value" << endl;
        cout << "    c)    Dist. Fr Origin value" << endl << endl;
        cout << "    Please enter your sorting criteria (a—c): ";

    } else if (curFilter == "Point3D") {
        cout << "    a)    X ordinate value    (default)" << endl;
        cout << "    b)    Y ordinate value" << endl;
        cout << "    c)    Z ordinate value" << endl;
        cout << "    d)    Dist. Fr Origin value" << endl << endl;
        cout << "    Please enter your sorting criteria (a—d): ";

    } else if (curFilter == "Line2D" || curFilter == "Line3D") {
        cout << "    a)    Pt. 1's (x, y) values    (default)" << endl;
        cout << "    b)    Pt. 2's (x, y) values" << endl;
        cout << "    c)    Length value" << endl << endl;
        cout << "    Please enter your sorting criteria (a—c): ";

    } else {
        cout << "    No sorting options available for this filter." << endl << endl;
        return; // exit if curFilter is invalid
    }

    // read user input
    char choice;
    cin >> choice;
    choice = tolower(choice);

    // update curSortCrit based on user input
    switch (curFilter[0]) { // using first letter of curFilter to choose submenu
        case 'P': // Point2D or Point3D
            if (curFilter == "Point2D") {
                switch (choice) {
                    case 'a': curSortCrit = "X-ordinate"; break;
                    case 'b': curSortCrit = "Y-ordinate"; break;
                    case 'c': curSortCrit = "Dist. Fr Origin"; break;
                    default: cout << "    Invalid sorting criteria." << endl << endl; return;
                }
            } else { // Point3D
                switch (choice) {
                    case 'a': curSortCrit = "X-ordinate"; break;
                    case 'b': curSortCrit = "Y-ordinate"; break;
                    case 'c': curSortCrit = "Z-ordinate"; break;
                    case 'd': curSortCrit = "Dist. Fr Origin"; break;
                    default: cout << "    Invalid sorting criteria." << endl << endl; return;
                }
            }
            break;

        case 'L': // Line2D or Line3D
            switch (choice) {
                case 'a': curSortCrit = "Pt. 1"; break;
                case 'b': curSortCrit = "Pt. 2"; break;
                case 'c': curSortCrit = "Length"; break;
                default: cout << "    Invalid sorting criteria." << endl << endl; return;
            }
            break;

        default:
            cout << "    Invalid filter." << endl << endl;
            return;
    }

    cout << "    Sorting criteria successfully set to '" 
         << curSortCrit << "'!" << endl << endl;
}


// [Specify sorting order]
void option4 ()
{
	cout << "[ Specifying filtering criteria (current: " << curSortOrd 
		 << ") ]" << endl << endl;
	cout << "    a)    ASC (Ascending order)" << endl;
	cout << "    b)    DSC (Descending order)" << endl << endl;
	cout << "    Please enter your criteria (a—b): ";
	
	char choice;
	cin >> choice;
	choice = tolower(choice);
	
	switch(choice) {
		case 'a': curSortOrd = "ASC"; break;
		case 'b': curSortOrd = "DSC"; break;
		default: cout << "    Invalid Sort Order criteria." 
		              << endl << endl; break;
	
	}
	
	cout << "    Sorting order successfully set to '" 
	     << curSortOrd << "'!" << endl << endl;
}

// display order functions
void dispPoint2Dheader() 
{
	cout << "    X     Y    Dist. Fr Origin" << endl;
	cout << "- - - - - - - - - - - - - - - - - - -" << endl;
}

void dispPoint3Dheader() 
{
	cout << "    X     Y     Z    Dist. Fr Origin" << endl;
	cout << "- - - - - - - - - - - - - - - - - - -" << endl;
}

void dispLine2Dheader()
{
	cout << " P1-X  P1-Y     P2-X  P2-Y    Length" << endl;
	cout << "- - - - - - - - - - - - - - - - - - -" << endl;
}

void dispLine3Dheader()
{
	cout << " P1-X  P1-Y  P1-Z     P2-X  P2-Y  P1-Z    Length" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
}


// global copies of the sorted vectors
vector<shared_ptr<Point2D>> selectedPoint2DVec;
vector<shared_ptr<Point3D>> selectedPoint3DVec;
vector<Line2D> selectedLine2DVec;
vector<Line3D> selectedLine3DVec;


// [View data]
void option5() {
    cout << "[ View data ... ]" << endl;    
    cout << "filtering criteria: " << curFilter << endl;
    cout << "sorting criteria: " << curSortCrit << endl;
    cout << "sorting order: " << curSortOrd << endl << endl;

	/*
	Steps for each filter:
		1. display header
		2. get global vector of unsorted objects
		3. sort the objects
		4. display objects using their toString()
	*/

    if (curFilter == "Point2D") {
        dispPoint2Dheader();		// display header
        auto vec = point2DVec;		// get vector of unsorted objects
		
		// sort vector
        if (curSortCrit == "X-ordinate") {
        		// sort and call object class comparators
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point2D::compareByX_ASC : Point2D::compareByX_DESC);
        } else if (curSortCrit == "Y-ordinate") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point2D::compareByY_ASC : Point2D::compareByY_DESC);
        } else if (curSortCrit == "Dist. Fr Origin") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point2D::compareByDist_ASC : Point2D::compareByDist_DESC);
		}
		
		// display vector objects using their toString functions
        for (auto &p : vec) cout << p->toString() << endl;
        cout << endl;
    }
    else if (curFilter == "Point3D") {
        dispPoint3Dheader();
        auto vec = point3DVec;

        if (curSortCrit == "X-ordinate") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point3D::compareByX_ASC : Point3D::compareByX_DESC);
        } else if (curSortCrit == "Y-ordinate") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point3D::compareByY_ASC : Point3D::compareByY_DESC);
        } else if (curSortCrit == "Z-ordinate") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point3D::compareByZ_ASC : Point3D::compareByZ_DESC);
        } else if (curSortCrit == "Dist. Fr Origin") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point3D::compareByDist_ASC : Point3D::compareByDist_DESC);
		}
		
        for (auto &p : vec) cout << p->toString() << endl;
        cout << endl;
    }
    else if (curFilter == "Line2D") {
        dispLine2Dheader();
        auto vec = line2DVec;

        if (curSortCrit == "Pt. 1") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line2D::compareByPt1_ASC : Line2D::compareByPt1_DESC);
        } else if (curSortCrit == "Pt. 2") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line2D::compareByPt2_ASC : Line2D::compareByPt2_DESC);
        } else if (curSortCrit == "Length") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line2D::compareByLength_ASC : Line2D::compareByLength_DESC);
		}
		
		
        for (auto &l : vec) cout << l.toString() << endl;
        cout << endl;
    }
    else if (curFilter == "Line3D") {
        dispLine3Dheader();
        auto vec = line3DVec;

        if (curSortCrit == "Pt. 1") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line3D::compareByPt1_ASC : Line3D::compareByPt1_DESC);
        } else if (curSortCrit == "Pt. 2") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line3D::compareByPt2_ASC : Line3D::compareByPt2_DESC);
        } else if (curSortCrit == "Length") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line3D::compareByLength_ASC : Line3D::compareByLength_DESC);
		}
		
		
        for (auto &l : vec) cout << l.toString() << endl;
        cout << endl;
    }
}


// [Store data]
void option6() {
    string filename;
    cout << "Please enter filename: ";
    cin >> filename;
    ofstream outFile(filename);

    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }
	int vecSize;
	
	// SAME AS option5() mechanics !!
	// but instead of displaying, it writes to the specified TXT FILE
    if (curFilter == "Point2D") {
    	// display header
        outFile << "    X     Y    Dist. Fr Origin" << endl;
        outFile << "- - - - - - - - - - - - - - - - - - -" << endl;
        // get sorted vector
        auto vec = point2DVec;

        if (curSortCrit == "X-ordinate") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point2D::compareByX_ASC : Point2D::compareByX_DESC);
        } else if (curSortCrit == "Y-ordinate") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point2D::compareByY_ASC : Point2D::compareByY_DESC);
        } else if (curSortCrit == "Dist. Fr Origin") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point2D::compareByDist_ASC : Point2D::compareByDist_DESC);
		}
        // display sorted vector
        for (auto &p : vec) {
            outFile << p->toString() << endl;
        vecSize = vec.size();
        }
    } else if (curFilter == "Point3D") {
        outFile << "    X     Y     Z    Dist. Fr Origin" << endl;
        outFile << "- - - - - - - - - - - - - - - - - - -" << endl;  
        
        auto vec = point3DVec;

        if (curSortCrit == "X-ordinate") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point3D::compareByX_ASC : Point3D::compareByX_DESC);
        } else if (curSortCrit == "Y-ordinate") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point3D::compareByY_ASC : Point3D::compareByY_DESC);
        } else if (curSortCrit == "Z-ordinate") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point3D::compareByZ_ASC : Point3D::compareByZ_DESC);
        } else if (curSortCrit == "Dist. Fr Origin") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Point3D::compareByDist_ASC : Point3D::compareByDist_DESC);
		}
              
        for (auto &p : vec) {
            outFile << p->toString() << endl;
        vecSize = vec.size();
        }
    } else if (curFilter == "Line2D") {
        outFile << " P1-X  P1-Y     P2-X  P2-Y    Length" << endl;
        outFile << "- - - - - - - - - - - - - - - - - - -" << endl; 
        
        auto vec = line2DVec;

        if (curSortCrit == "Pt. 1") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line2D::compareByPt1_ASC : Line2D::compareByPt1_DESC);
        } else if (curSortCrit == "Pt. 2") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line2D::compareByPt2_ASC : Line2D::compareByPt2_DESC);
        } else if (curSortCrit == "Length") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line2D::compareByLength_ASC : Line2D::compareByLength_DESC);
		}
               
        for (auto &l : vec) {
            outFile << l.toString() << endl;
        vecSize = vec.size();
        }
    } else if (curFilter == "Line3D") {
        outFile << " P1-X  P1-Y  P1-Z     P2-X  P2-Y  P1-Z    Length" << endl;
        outFile << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        
        auto vec = line3DVec;

        if (curSortCrit == "Pt. 1") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line3D::compareByPt1_ASC : Line3D::compareByPt1_DESC);
        } else if (curSortCrit == "Pt. 2") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line3D::compareByPt2_ASC : Line3D::compareByPt2_DESC);
        } else if (curSortCrit == "Length") {
		        sort(vec.begin(), vec.end(), (curSortOrd=="ASC") ? 
		        Line3D::compareByLength_ASC : Line3D::compareByLength_DESC);
		}
                
        for (auto &l : vec) {
            outFile << l.toString() << endl;
        vecSize = vec.size();
        }
    }

    outFile.close();
    cout << vecSize << " records output successfully!" 
         << endl << endl;
    
    cout << "Going back to main menu ..." << endl << endl;
}



// ______________some other functions_________________

void promptUser()
{
	cout << endl;
	cout << "Press <Enter> to go back to main menu ... ";
	cin.get();
	cout << endl;	
}

void exitProgram() 
{
	
	cout << "Exiting program ... \n";
	exit(0);
}
