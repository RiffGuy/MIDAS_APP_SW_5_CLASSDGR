#include "stdafx.h"
#include "DiagramClass.h"
#include "Brushs.h"
#include <iostream>

DiagramClass::DiagramClass()
{
	drawMode = WAIT;
}


DiagramClass::~DiagramClass()
{
}

DiagramClass::DiagramClass(CPoint start, CPoint end) {
	drawMode = WAIT;
	startPoint.SetPoint(start.x, start.y);
	endPoint.SetPoint(end.x, end.y);
	type = 'C';
	str = "hello";
	status = NULL;
}


void DiagramClass::ReDraw(CDC* pDC) {
	//printf("mRectangle ReDraw (%d,%d) , (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	//start -> TopLeft, end -> BottomRight로 재설정 
	CPoint newStartPos;
	CPoint newEndPos;
	if (endPoint.y < startPoint.y) {
		newStartPos = endPoint;
		newEndPos = startPoint;
	}
	else {
		newStartPos = startPoint;
		newEndPos = endPoint;
	}

//status 표시
	if (status != NULL) {
		int curY = newStartPos.y;
		int curX = newStartPos.x;
		int centerWidth = newStartPos.x + (newEndPos.x - newStartPos.x) / 2;

		CString tmp = status->getClassName();
		int textWidth = pDC->GetTextExtent(tmp).cx;

		pDC->TextOutW(centerWidth - textWidth / 2, curY, tmp);

		curY += 20;
		for (int i = 0; i < status->getAttrbuteSize(); i++) {
			tmp = status->getAttrbute(i);
			pDC->TextOutW(newStartPos.x, curY, tmp);
			curY += 20;
		}
		
		for (int i = 0; i < status->getOperationSize(); i++) {
			tmp = status->getOperation(i);
			pDC->TextOutW(newStartPos.x, curY, tmp);
			curY += 20;
		}
		
	}
//	pDC->TextOutW(centerWidth - textWidth / 2, newStartPos.y, str);
	
}

void DiagramClass::Draw(CPoint startPoint, CPoint endPoint, CDC* pDC) {

	if (startPoint == endPoint) { return; }

	pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	//string text 출력
	CPoint newStartPos;
	CPoint newEndPos;
	if (endPoint.y < startPoint.y) {
		newStartPos = endPoint;
		newEndPos = startPoint;
	}else { newStartPos = startPoint;
			newEndPos = endPoint;
	}
	int centerWidth = newStartPos.x + (newEndPos.x - newStartPos.x) / 2;
	int textWidth = pDC->GetTextExtent(str).cx;
	pDC->TextOutW(centerWidth - textWidth / 2, newStartPos.y, str);


}

bool DiagramClass::Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList) {
	//printf("DRAW - Rectangle\n");
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
			saveList->push_back(new DiagramClass(startPoint, point));// save Polygon
			drawMode = MOVE;
			return true;
		}
		break;
	}
	}

	return false;
}
