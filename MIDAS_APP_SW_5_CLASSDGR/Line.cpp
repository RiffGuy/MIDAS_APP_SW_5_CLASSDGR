#include "stdafx.h"
#include "Line.h"
#include "Brushs.h"

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


}

void Line::Draw(CPoint startPoint, CPoint endPoint, CDC* pDC) {
	pDC->MoveTo(startPoint.x, startPoint.y);
	pDC->LineTo(endPoint.x, endPoint.y);
}

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


void Line::addConnectedPoint(CPoint* p, CPoint* q) {

}


void Line::removeConnectedPoint() {

}

void Line::reConnectedPoint() {

}