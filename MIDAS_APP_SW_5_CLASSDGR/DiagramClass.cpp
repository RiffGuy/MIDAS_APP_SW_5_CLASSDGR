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
		ar << startPoint << endPoint;
	}
	else {
		// load
		ar >> startPoint >> endPoint;
	}
	status->saveData(ar);
}