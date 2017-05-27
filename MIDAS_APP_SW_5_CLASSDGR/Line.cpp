#include "stdafx.h"
#include "Line.h"
#include "Brushs.h"
#include <math.h>

#define PI 3.141592265

//CPoint transformation(CPoint centerP, CPoint moveP, double angle);

Line::Line()
{
	drawMode = WAIT;
}


Line::~Line()
{
}

Line::Line(CPoint start, CPoint end) {
	drawMode = WAIT;
	startPoint.SetPoint(start.x, start.y);
	endPoint.SetPoint(end.x, end.y);
	
}

void Line::ReDraw(CDC* pDC) {
	//printf("Line ReDraw (%d,%d) , (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	pDC->MoveTo(startPoint.x, startPoint.y);
	pDC->LineTo(endPoint.x, endPoint.y);

	CRect rec;


}

void Line::Draw(CPoint startPoint, CPoint endPoint, CDC* pDC) {
	pDC->MoveTo(startPoint.x, startPoint.y);
	pDC->LineTo(endPoint.x, endPoint.y);

	/*CPoint p1(endPoint.x - 5, endPoint.y + 5);
	CPoint p2(endPoint.x - 5, endPoint.y - 5);
	int x = endPoint.x - startPoint.x;
	int y = endPoint.y - startPoint.y;
	double angle = atan2(y, x) * 180 / PI;

	printf("%lf angle@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n", angle);

	CPoint p1_new = transformation(endPoint, p1, angle);
	CPoint p2_new = transformation(endPoint, p2, angle);
	pDC->MoveTo(endPoint.x, endPoint.y);
	pDC->LineTo(p1_new.x, p1_new.y);
	pDC->MoveTo(endPoint.x, endPoint.y);
	pDC->LineTo(p2_new.x, p2_new.y);*/

}

/*CPoint transformation(CPoint centerP, CPoint moveP, double angle)
{
	double rx = (moveP.x - centerP.x)*cos(angle) - (moveP.y - centerP.y)*sin(angle) + centerP.x;
	double ry = (moveP.x - centerP.x)*sin(angle) + (moveP.y - centerP.y)*cos(angle) + centerP.y;
	return CPoint(rx, ry);
}*/
bool Line::Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList) {
	//printf("DRAW - Line\n");
	switch (dmode) {
	case L_MOUSE_UP: {
		drawMode = WAIT;

		break;
	}
	case L_MOUSE_DOWN: {
		drawMode = START;
		startPoint.SetPoint(point.x, point.y);
		break;
	}
	case MOUSE_MOVE: {
		if (drawMode == START || drawMode == MOVE) {
			if ((drawMode == MOVE) && (saveList->size() != 0))saveList->pop_back();
			saveList->push_back(new Line(startPoint, point));// save Polygon
			drawMode = MOVE;
			return true;
		}
		break;

	}default: {
		break;
	}
	}
	return false;
}

void Line::saveData(CArchive& ar) {
	printf("Save Line ! \n");
	if (ar.IsStoring()) {
		// save
		ar << startPoint << endPoint;
	}
	else {
		// load
		ar >> startPoint >> endPoint;
	}
}


void Line::addConnectedPoint(CPoint* p) {

}


void Line::removeConnectedPoint() {

}

void Line::reConnectedPoint() {

}