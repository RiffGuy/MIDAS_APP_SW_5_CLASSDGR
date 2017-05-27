#include "stdafx.h"
#include "dependencyLine.h"


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
	CPen brushPen; // 선 종류를 결정
	CPen* oldPen;
	brushPen.DeleteObject();
	brushPen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	oldPen = pDC->SelectObject(&brushPen); 
	pDC->MoveTo(startPoint.x, startPoint.y);
	pDC->LineTo(endPoint.x, endPoint.y);
	pDC->SelectObject(oldPen);
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
		if (isVisual) {
			printf("save dependencyLine (%d,%d) ~ (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
			ar << startPoint << endPoint;
		}
	}
	else {
		// load
		if (isVisual) {
			ar >> startPoint >> endPoint;
			printf("load dependencyLine (%d,%d) ~ (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		}
	}
}
