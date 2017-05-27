#include "stdafx.h"
#include "DiagramClass.h"
#include "Brushs.h"
#include <iostream>

DiagramClass::DiagramClass()
{
	drawMode = WAIT;
	status = new NewClassAddDLG;
}


DiagramClass::~DiagramClass()
{
}

DiagramClass::DiagramClass(CPoint start, CPoint end) {
	drawMode = WAIT;
	startPoint.SetPoint(start.x, start.y);
	endPoint.SetPoint(end.x, end.y);
	status = NULL;
}


void DiagramClass::ReDraw(CDC* pDC) {

//line size (나중에 구해야함)
	int lineSize = 1;

//status 최소 넓이 구하기
	if (status != NULL) {
		int curY = startPoint.y;
		int maxX = 0;
//className
		CString tmp = status->getClassName();
		int textWidth = pDC->GetTextExtent(tmp).cx ;
		int textHeight = pDC->GetTextExtent(tmp).cy;
		curY += textHeight * 2;
		maxX = max(maxX, textWidth);
//line
		curY += lineSize*3;
//attrbute
		for (int i = 0; i < status->getAttrbuteSize(); i++) {
			tmp = status->getAttrbute(i);
			textWidth = pDC->GetTextExtent(tmp).cx;
			curY += textHeight;
			maxX = max(maxX, textWidth);
		}
//line
		curY += lineSize*3;
//opreation
		for (int i = 0; i < status->getOperationSize(); i++) {
			tmp = status->getOperation(i);
			textWidth = pDC->GetTextExtent(tmp).cx;
			curY += textHeight;
			maxX = max(maxX, textWidth);
		}
		curY += lineSize;
//start, end point 재정의
		if (endPoint.y < curY) {
			endPoint.y = curY;
		}
		if (endPoint.x < startPoint.x + maxX + lineSize) {
			endPoint.x = startPoint.x + maxX + lineSize*2;
		}
		
	}
	pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);

//status 표시
	if (status != NULL) {
		int curY = startPoint.y;
		int centerWidth = startPoint.x + (endPoint.x - startPoint.x) / 2;
//className 출력
		CString tmp = status->getClassName();
		pDC->SetBkColor(RGB(255, 255, 153));
		int textWidth = pDC->GetTextExtent(tmp).cx;
		int textHeight = pDC->GetTextExtent(tmp).cy;
		pDC->TextOutW(centerWidth - textWidth / 2, curY + textHeight / 2, tmp);
		curY += textHeight * 2;
//line 그리기
		curY += lineSize;
		pDC->MoveTo(CPoint(startPoint.x, curY));
		pDC->LineTo(CPoint(endPoint.x, curY));
		curY += lineSize;
//attrbute 출력
		for (int i = 0; i < status->getAttrbuteSize(); i++) {
			tmp = status->getAttrbute(i);
			pDC->TextOutW(startPoint.x + lineSize, curY, tmp);
			textWidth = pDC->GetTextExtent(tmp).cx;
			curY += textHeight;
		}
//line 그리기
		curY += lineSize;
		pDC->MoveTo(CPoint(startPoint.x, curY));
		pDC->LineTo(CPoint(endPoint.x, curY));
		curY += lineSize;
//opreation 출력
		for (int i = 0; i < status->getOperationSize(); i++) {
			tmp = status->getOperation(i);
			pDC->TextOutW(startPoint.x + lineSize, curY, tmp);
			textWidth = pDC->GetTextExtent(tmp).cx;
			curY += lineSize;
		}
	}
}

void DiagramClass::Draw(CPoint startPoint, CPoint endPoint, CDC* pDC) {
	pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);


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

			//start -> TopLeft, end -> BottomRight로 재설정 
			CPoint newStartPos;
			CPoint newEndPos;
			if (point.y < startPoint.y) {
				newStartPos.y = point.y;
				newEndPos.y = startPoint.y;
			}
			else {
				newStartPos.y = startPoint.y;
				newEndPos.y = point.y;
			}
			if (point.x < startPoint.x) {
				newStartPos.x = point.x;
				newEndPos.x = startPoint.x;
			}
			else {
				newStartPos.x = startPoint.x;
				newEndPos.x = point.x;
			}

			saveList->push_back(new DiagramClass(newStartPos, newEndPos));// save Polygon
			drawMode = MOVE;
			return true;
		}
		break;
	}
	}

	return false;
}
void DiagramClass::saveData(CArchive& ar) {
	
	if (ar.IsStoring()) {
		// save
		ar << startPoint << endPoint;
	}
	else {
		// load
		ar >> startPoint >> endPoint;
	}
	status->saveData(ar);
}


void DiagramClass::addConnectedPoint(CPoint* p) {
	if (p == NULL) {
		printf("The Point is NULL\n");
	}
	else {
		
		// 센터 좌표로 보정
		p->x = (startPoint.x + endPoint.x) / 2;
		p->y = (startPoint.y + endPoint.y) / 2;

		printf("Add Point(%d,%d)\n", p->x, p->y);
	}
	lineList.push_back(p);
}


void DiagramClass::removeConnectedPoint() { // Twice !
	if(lineList.size() >= 0)lineList.pop_back();
	if (lineList.size() >= 0)lineList.pop_back();
	printf("Points removed!\n");
}

void DiagramClass::reConnectedPoint() {
	for (int i = 0; i < lineList.size(); i++) {
		lineList[i]->x = (startPoint.x + endPoint.x) / 2;
		lineList[i]->y = (startPoint.y + endPoint.y) / 2;
	}
}