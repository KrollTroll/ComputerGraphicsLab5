/**
 * Connor Kroll
 * Graphics
 *
 * This file implements control to a line object
 * 		Lines extend shape and add an endpoint
 */

#include "line.h"

#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

	/**
 	 * line consructor
	 * @param x  : start point x coordinate
	 * @param y  : start point y coordinate
	 * @param R  : line red color value
	 * @param G  : line green color value
	 * @param B  : line blue color value
	 * @param x2 : end point x coordinate
	 * @param y2 : end point y coordinate
	 */
	line::line(float x, float y, int R, int G, int B, float x2, float y2):shape(x,y,R,G,B){
		this->x2 = x2;
		this->y2 = y2;
	}

	/**
	 * copy constructor for a line
	 * @param from : line to copy from
	 */
	line::line(const line& from):shape(from){
		this->x2 = from.x2;
		this->y2 = from.x2;
	}

	/**
	 * Destructor - there is nothing to free
	 */
	line::~line(){}

	/**
	 * draws a line to a garphics context interface
	 * @param GC : target interface
	 */
	void line::draw(GraphicsContext* GC){
		int color = (((this->RED << 8) + this->GREEN) << 8) + this->BLUE;
		GC->setColor(color);
		GC->drawLine(this->x, this->y, this->x2, this->y2);
	}

	/**
	 * assignment operator - sets one line equal to another
	 * @param from : line to assign from
	 * @return     :  address of newly assigned line
	 */
	line& line::operator=(const line& from){
		this->shape::operator=(from);
		this->x2 = from.x2;
		this->y2 = from.y2;
		return *this;
	}

	/**
	 * Copies one line into a new location in memory
	 * @return : address of newly allocated copy
	 */
	line& line::clone(){
		return *(new line(x, y, RED, GREEN, BLUE, x2, y2));
	}

	/**
	 * outputs line characteristics to desired output stream
	 * @param os : desired output stream
	 * @return   :  address of that same stream
	 */
	std::ostream& line::out(std::ostream& os) const{
		os << "START LINE" << "\n";
		shape::out(os);
		os << "  " << x2 << "\n";
		os << "  " << y2 << "\n";
		os << "END" << endl << endl;
		return os;
	}

	/**
	 * read in a single line from a file
	 * @param in : istream to parse from
	 * @return   : the new triangle object
	 */
	void line::in(std::istream& in) {
		//placeholder string for read in
		string holder;
		//read in data line by line
		getline(in, holder);
		//remove spaces
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
		getline(in, holder);
		holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
		this->x2 = stof(holder);
		getline(in, holder);
		holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
		this->y2 = stof(holder);
	}

	/**
	 * over-written global operator for easy output
	 * @param os  : target output stream
	 * @param rhs : object to output
	 * @return    : address of the same output stream
	 */
	std::ostream& operator<<(std::ostream& os, const line& rhs){
		rhs.out(os);
		return os;
	}
