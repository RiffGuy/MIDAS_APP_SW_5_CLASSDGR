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
			curY += textHeight;
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
		if (isVisual) {
			printf("save DiagramClass (%d,%d) ~ (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
			ar << startPoint << endPoint;
			status->saveData(ar);
		}
	}
	else {
		// load
		if (isVisual) {
			ar >> startPoint >> endPoint;
			status->saveData(ar);
			printf("load DiagramClass (%d,%d) ~ (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		}
	}
}


void DiagramClass::addConnectedPoint(CPoint* p, CPoint* q) {
	if (p == NULL) {
		printf("The Point is NULL\n");
	}
	else {
		// 센터 좌표로 보정
		CPoint center((startPoint.x + endPoint.x) / 2, (startPoint.y + endPoint.y) / 2);
		p->x = (startPoint.x + endPoint.x) / 2;
		p->y = (startPoint.y + endPoint.y) / 2;
		CPoint* curPoint = getCurPoint(p, q);
		p->x = curPoint->x;
		p->y = curPoint->y;
		printf("Add Point(%d,%d)\n", p->x, p->y);
		printf("~~~ Add Point(%d,%d)\n", q->x, q->y);
	}
	lineList.push_back(p);
	conntList.push_back(q);
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
		CPoint* curPoint = getCurPoint(
			lineList[i], conntList[i]
		);
		lineList[i]->x = curPoint->x;
		lineList[i]->y = curPoint->y;
	}
}

CPoint* DiagramClass::getCurPoint(CPoint* p, CPoint* q) {
	int dx = (endPoint.x - startPoint.x) / 2;
	if (dx < 0)dx = dx * -1;
	int dy = (endPoint.y - startPoint.y) / 2;
	if (dy < 0)dy = dy * -1;

	int defX = p->x - q->x;
	int defY = p->y - q->y;
	if (defX >= 0 && defY >= 0){
		//1 사분면
		if (defX > defY) {
			// p->x = p->x; 
			p->y = p->y - dy;
		}
		else {
			p->x = p->x - dx;
		}
	}
	else if (defX >= 0 && defY < 0) {
		// 4 사분면
		defY = defY*(-1);
		
		if (defX > defY) {
			p->x = p->x - dx;
		}
		else {
			p->y = p->y + dy;
		}
	}
	else if (defX < 0 && defY >= 0) {
		// 2 사분면
		defX = defX*(-1);
		if (defX > defY) {
			p->x = p->x + dx;
		}
		else {
			p->y = p->y - dy;
		}
	}
	else if (defX < 0 && defY < 0) {
		// 3 사분면
		defY = defY*(-1);
		defX = defX*(-1);
		if (defX > defY) {
			p->x = p->x + dx;
		}
		else {
			p->y = p->y + dy;
		}
	}

	return new CPoint(p->x, p->y);
}