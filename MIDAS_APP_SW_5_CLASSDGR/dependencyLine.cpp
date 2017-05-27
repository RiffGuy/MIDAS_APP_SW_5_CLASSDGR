#include "stdafx.h"
#include "dependencyLine.h"
#include <math.h>

CPoint transformation(CPoint centerP, CPoint moveP, double angle);

dependencyLine::dependencyLine()
{
	drawMode = START;
}

dependencyLine::dependencyLine(CPoint centerPoint)
{
	drawMode = START;
	startPoint = centerPoint;
}
dependencyLine::dependencyLine(CPoint start, CPoint end){
	drawMode = START;
	startPoint.SetPoint(start.x, start.y);
	endPoint.SetPoint(end.x, end.y);
}

dependencyLine::~dependencyLine()
{
}



void dependencyLine::ReDraw(CDC* pDC) {
	//printf("Line ReDraw (%d,%d) , (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	pDC->MoveTo(startPoint.x, startPoint.y);
	pDC->LineTo(endPoint.x, endPoint.y);

	CPoint p1(endPoint.x - 20, endPoint.y + 20);
	CPoint p2(endPoint.x - 20, endPoint.y - 20);
	int x = endPoint.x - startPoint.x;
	int y = endPoint.y - startPoint.y;
	double angle = atan2(y, x);

	CPoint p1_new = transformation(endPoint, p1, angle);
	CPoint p2_new = transformation(endPoint, p2, angle);
	pDC->LineTo(p1_new.x, p1_new.y);
	pDC->MoveTo(endPoint.x, endPoint.y);
	pDC->LineTo(p2_new.x, p2_new.y);
}

bool dependencyLine::Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList) {
	//printf("DRAW - Line\n");
	switch (dmode) {
	case L_MOUSE_UP: {
		//printf("마우스 업 \n");
		break;
	}
	case L_MOUSE_DOWN: {
		//printf("마우스 클릭 \n");
		drawMode = END;
		break;
	}
	case MOUSE_MOVE: {
		//printf("now..in inheritance draw line, move mouse ! \n");
		if (drawMode == END)break;
		if (drawMode != START && (saveList->size() != 0))saveList->pop_back();
		drawMode = MOVE;
		saveList->push_back(new dependencyLine(startPoint, point));// save Polygon
		return true;

	}default: {
		break;
	}
	}
	return false;
}


void dependencyLine::addConnectedPoint(CPoint* p, CPoint* q) {

}


void dependencyLine::removeConnectedPoint() {
	
}

void dependencyLine::reConnectedPoint() {

}

void dependencyLine::saveData(CArchive& ar) {
	printf("Save dependencyLine ! \n");
	if (ar.IsStoring()) {
		// save
		printf("save dependencyLine (%d,%d) ~ (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		ar << startPoint << endPoint;
	}
	else {
		// load
		printf("load dependencyLine (%d,%d) ~ (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		ar >> startPoint >> endPoint;
	}
}
