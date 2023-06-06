 /*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
using namespace std;


void drawTriang(GWindow gw,GPoint p, double length){
	GPoint p1 = gw.drawPolarLine(p,length,0);
	GPoint p2 = gw.drawPolarLine(p1,length,120);
	GPoint p3 = gw.drawPolarLine(p2,length,240);
}
void drawFirstTriang(GWindow gw,GPoint p,GPoint &p2,GPoint &p3, double length){
	p2 = gw.drawPolarLine(p,length,0);
	p3 = gw.drawPolarLine(p2,length,120);
	GPoint p4 = gw.drawPolarLine(p3,length,240);
}

void sierpinski(GWindow gw,GPoint p1, double length,int n){
	if(n!=0){
	GPoint p2 ;
	GPoint p3 ;
	
	drawFirstTriang(gw,p1,p2,p3,length);
	sierpinski(gw,p1,length/2,n-1);
	//drawTriang(gw,p1,length);
	
	drawTriang(gw,p2,length);
	sierpinski(gw,p2,length/2,n-1);

	drawTriang(gw,p3,length);
	sierpinski(gw,p3,length/2,n-1);

	}
}

int main() {
	
	GWindow gw(800,700);
    cout << "Length: ";
	double length = getReal("");
	cout << "N: ";
	int n = getInteger("");
	double width = gw.getWidth();
    double height = gw.getHeight();
	GPoint p((width-length)/2,height-(height-(sqrt(3.0)/2*length))/2);
	drawTriang(gw,p,length);  
	sierpinski(gw,p,length/2,n);
    return 0;
}
