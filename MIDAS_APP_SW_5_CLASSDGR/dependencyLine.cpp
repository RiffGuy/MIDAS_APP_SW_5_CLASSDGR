#include "stdafx.h"
#include "dependencyLine.h"


dependencyLine::dependencyLine()
{
}

dependencyLine::dependencyLine(CPoint centerPoint)
{
	startPoint = centerPoint;
}
dependencyLine::dependencyLine(CPoint start, CPoint end) {
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
}

bool dependencyLine::Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList) {
	//printf("DRAW - Line\n");
	switch (dmode) {
	case L_MOUSE_UP: {
		
		break;
	}
	case L_MOUSE_DOWN: {
		// nothing
		break;
	}
	case MOUSE_MOVE: {
		if ((saveList->size() != 0))saveList->pop_back();
		saveList->push_back(new dependencyLine(startPoint, point));// save Polygon
		return true;
	}default: {
		break;
	}
	}
	return false;
}


void dependencyLine::addConnectedPoint(CPoint* p) {

}


void dependencyLine::removeConnectedPoint() {
	
}

void dependencyLine::reConnectedPoint() {

}