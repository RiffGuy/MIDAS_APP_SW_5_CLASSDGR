#include "stdafx.h"
#include "InheritanceLine.h"


InheritanceLine::InheritanceLine()
{
}

InheritanceLine::InheritanceLine(CPoint centerPoint)
{
	startPoint = centerPoint;
}
InheritanceLine::InheritanceLine(CPoint start, CPoint end) {
	startPoint.SetPoint(start.x, start.y);
	endPoint.SetPoint(end.x, end.y);
	type = 'L';
}
void InheritanceLine::ReDraw(CDC* pDC) {
	//printf("InheritanceLine Line ReDraw (%d,%d) , (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	pDC->MoveTo(startPoint.x, startPoint.y);
	pDC->LineTo(endPoint.x, endPoint.y);
}

bool InheritanceLine::Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList) {
	//printf("DRAW - Line\n");
	switch (dmode) {
	case L_MOUSE_UP: {
		
		break;
	}
	case L_MOUSE_DOWN: {
		// nothing
		IsFirst = true;
		break;
	}
	case MOUSE_MOVE: {
		//printf("now..in inheritance draw line, move mouse ! \n");
		if (!IsFirst && (saveList->size() != 0))saveList->pop_back();
		IsFirst = false;
		saveList->push_back(new InheritanceLine(startPoint, point));// save Polygon
		return true;
	}default: {
		break;
	}
	}
	return false;
}

InheritanceLine::~InheritanceLine()
{
}
