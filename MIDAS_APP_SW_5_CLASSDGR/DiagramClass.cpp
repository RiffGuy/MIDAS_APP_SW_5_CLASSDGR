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
//start -> TopLeft, end -> BottomRight�� �缳�� 
	CPoint newStartPos;
	CPoint newEndPos;
	if (endPoint.y < startPoint.y) {
		newStartPos.y = endPoint.y;
		newEndPos.y = startPoint.y;
	}
	else {
		newStartPos.y = startPoint.y;
		newEndPos.y = endPoint.y;
	}
	if (endPoint.x < startPoint.x) {
		newStartPos.x = endPoint.x;
		newEndPos.x = startPoint.x;
	}
	else {
		newStartPos.x = startPoint.x;
		newEndPos.x = endPoint.x;
	}

//line size (���߿� ���ؾ���)
	int linesize = 1;

//status �ּ� ���� ���ϱ�
	if (status != NULL) {
		int curY = newStartPos.y;
		int maxX = 0;
//className
		CString tmp = status->getClassName();
		int textWidth = pDC->GetTextExtent(tmp).cx ;
		int textHeight = pDC->GetTextExtent(tmp).cy;
		curY += textHeight * 2;
		maxX = max(maxX, textWidth);
//line
		curY += linesize;
//attrbute
		for (int i = 0; i < status->getAttrbuteSize(); i++) {
			tmp = status->getAttrbute(i);
			textWidth = pDC->GetTextExtent(tmp).cx;
			curY += textHeight;
			maxX = max(maxX, textWidth);
		}
//line
		curY += linesize;
//opreation
		for (int i = 0; i < status->getOperationSize(); i++) {
			tmp = status->getOperation(i);
			textWidth = pDC->GetTextExtent(tmp).cx;
			curY += textHeight;
			maxX = max(maxX, textWidth);
		}
		curY += linesize;
//start, end point ������
		if (endPoint.y < curY) {
			newEndPos.y = curY;
		}
		if (endPoint.x < newStartPos.x + maxX + linesize) {
			newEndPos.x = newStartPos.x + maxX + linesize*2;
		}

		startPoint = newStartPos;
		endPoint = newEndPos;
		
	}
	pDC->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);

//status ǥ��
	if (status != NULL) {
		int curY = newStartPos.y;
		int centerWidth = newStartPos.x + (newEndPos.x - newStartPos.x) / 2;
//className ���
		CString tmp = status->getClassName();
		pDC->SetBkColor(RGB(255, 255, 153));
		int textWidth = pDC->GetTextExtent(tmp).cx;
		int textHeight = pDC->GetTextExtent(tmp).cy;
		pDC->TextOutW(centerWidth - textWidth / 2, curY + textHeight / 2, tmp);
		curY += textHeight * 2;
//line �׸���
		pDC->MoveTo(CPoint(newStartPos.x, curY));
		pDC->LineTo(CPoint(newEndPos.x, curY));
		curY += linesize;
//attrbute ���
		for (int i = 0; i < status->getAttrbuteSize(); i++) {
			tmp = status->getAttrbute(i);
			pDC->TextOutW(newStartPos.x + linesize, curY, tmp);
			textWidth = pDC->GetTextExtent(tmp).cx;
			curY += textHeight;
		}
//line �׸���
		pDC->MoveTo(CPoint(newStartPos.x, curY));
		pDC->LineTo(CPoint(newEndPos.x, curY));
		curY += linesize;
//opreation ���
		for (int i = 0; i < status->getOperationSize(); i++) {
			tmp = status->getOperation(i);
			pDC->TextOutW(newStartPos.x + linesize, curY, tmp);
			textWidth = pDC->GetTextExtent(tmp).cx;
			curY += linesize;
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
			saveList->push_back(new DiagramClass(startPoint, point));// save Polygon
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
		printf("save DiagramClass (%d,%d) ~ (%d,%d)\n",startPoint.x,startPoint.y,endPoint.x,endPoint.y);
		ar << startPoint << endPoint;
	}
	else {
		// load
		ar >> startPoint >> endPoint;
		printf("load DiagramClass (%d,%d) ~ (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	}
	status->saveData(ar);
}


void DiagramClass::addConnectedPoint(CPoint* p, CPoint* q) {
	if (p == NULL) {
		printf("The Point is NULL\n");
	}
	else {
		// ���� ��ǥ�� ����
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
	if (defX >= 0 && defY >= 0) {
		//1 ��и�
		if (defX > defY) {
			// p->x = p->x; 
			p->y = p->y - dy;
		}
		else {
			p->x = p->x - dx;
		}
	}
	else if (defX >= 0 && defY < 0) {
		// 4 ��и�
		defY = defY*(-1);
		if (defX > defY) {
			p->x = p->x - dx;
		}
		else {
			p->y = p->y + dy;
		}
	}
	else if (defX < 0 && defY >= 0) {
		// 2 ��и�
		defX = defX*(-1);
		if (defX > defY) {
			p->x = p->x + dx;
		}
		else {
			p->y = p->y - dy;
		}
	}
	else if (defX < 0 && defY < 0) {
		// 3 ��и�
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