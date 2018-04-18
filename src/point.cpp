/**
 * Connor Kroll
 * Graphics
 *
 * This file implements control to a point object
 * 		The most basic shape, has no extra features
 */

#include "point.h"

#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

/**
 * Point constructor
 * @param x : point x coordinate
 * @param y : point y coordinate
 * @param R : point red color value
 * @param G : point green color value
 * @param B : point blue color value
 */
point::point(float x, float y, int R, int G, int B):shape(x,y,R,G,B){}

/**
 * copy constructor
 * @param from : point to cpoy data from
 */
point::point(const point& from):shape(from){}

/**
 * destructor - doesn't do much
 */
point::~point(){}

/**
 * draws the shape to the appropriate graphicscontext interface
 * @param GC : target graphicscontext interface
 */
void point::draw(GraphicsContext* GC){
	int color = (((this->RED << 8) + this->GREEN) << 8) + this->BLUE;
	GC->setColor(color);
	GC->setPixel(this->x, this->y);
}

/**
 * Assignment operator
 * @param from : object to assign from
 * @return     : address of newly assigned object
 */
point& point::operator=(const point& from){
	this->shape::operator =(from);
	return *this;
}

/**
 * copies a point into another location in memory
 * @return : address of newly allocated point
 */
point& point::clone(){
	return *(new point(x, y, RED, GREEN, BLUE));
}

/**
 * prints point data to an output stream
 * @param os : target output stream
 * @return   : adress of same output stream
 */
std::ostream& point::out(std::ostream& os) const{
	os << "START POINT" << "\n";
	shape::out(os);
	os << "END" << endl << endl;
	return os;
}

/**
 * scans a single point from a file
 * @param in : desired file
 */
void point::in(std::istream& in) {
	//placeholder string for scanning
	string holder;
	//scan in line by line
	getline(in, holder);
	//remove whitespace
	holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
	//convert as necessary
	this->x = stof(holder);
	getline(in, holder);
	holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
	this->y = stof(holder);
	getline(in, holder);
	holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
	this->RED = stoi(holder);
	getline(in, holder);
	holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
	this->GREEN = stoi(holder);
	getline(in, holder);
	holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
	this->BLUE = stoi(holder);
}

/**
 * over-written global operator to print point data
 * @param os  : target output stream
 * @param rhs : point to output
 * @return    : adress of the same output stream
 */
std::ostream& operator<<(std::ostream& os, const point& rhs){
	rhs.out(os);
	return(os);
}
