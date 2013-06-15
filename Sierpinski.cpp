/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: Matt Kelly
 * Section: Summer '13
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

#define WINDOW_SIZE 800

void drawTriangle( GWindow gw, GPoint start, GPoint& br, GPoint& bl, double length );
void sierpinski( GWindow gw, GPoint start, int order, double length ) ;

int main() {
	double length = getReal("Please enter a side length: ");
	int order = getInteger("Please enter a fractal order: ");
	GWindow gw(WINDOW_SIZE, WINDOW_SIZE);
	GPoint start( WINDOW_SIZE/2.0, (WINDOW_SIZE - length * sin(acos(-1.0)/3))/2.0 );  //centers the triangle in the viewing window
	
	cout << "Click in graphic window to draw." << endl;
	waitForClick();
	sierpinski( gw, start, order, length);

    return 0;
}

//drawTriangle draws a triangle in the passed graphic window with sides as long as length
//It begins drawing at start and returns nothing but modifies br and bl to be used by
//the sierpinski function for drawing inner triangles
void drawTriangle( GWindow gw, GPoint start, GPoint& br, GPoint& bl, double length ) {
	br = gw.drawPolarLine(start, length/2, -60);  //upper part of right leg of triangle and save the endpoint
	GPoint next = gw.drawPolarLine(br, length/2, -60);  //lower part of right leg of triangle
	next = gw.drawPolarLine(next, length, 180);  //bottom of triangle
	bl = gw.drawPolarLine(next, length/2, 60);  //lower part of left leg of triangle and save the endpoint
	gw.drawPolarLine(bl, length/2, 60);  //upper part of left leg of triangle

	return;
}

//sierpinski draws the fractal triangles.  It first draws the outer triangle, then calls
//itself recursively to draw the three triangles inside it if it is on order > 0
void sierpinski( GWindow gw, GPoint start, int order, double length ) {
	if (order < 0) return;

	GPoint br, bl;
	drawTriangle( gw, start, br, bl, length);

	if (order > 0) {  //recursively draws the inner triangles
		sierpinski( gw, start, order - 1, length/2);  //top triangle
		sierpinski( gw, br, order - 1, length/2);  //bottom right triangle
		sierpinski( gw, bl, order - 1, length/2);  //bottom left triangle
	}
	return;
}