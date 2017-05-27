#include "stdafx.h"
#include "Brushs.h"
//#include "Resource.h"

//브랜치 병합 예제
#include <iostream>


Brushs::Brushs()
{
	DrawMode = D_MODE_NONE;
	mpoly = new M_Polygon();
}


Brushs::~Brushs()
{

}

void Brushs::setBrushWnd(CWnd* pWnd) {
	bWnd = pWnd;
}

bool Brushs::Draw(CPoint point, int flag, int dmode) {
	bool rst = mpoly->Draw(point, flag, dmode, brushCDC, &polygonList);

	if (mpoly->getType() == D_MODE_DUMMY) {
		return true;
	}
	//brushCDC->SelectObject(oldPen);
	//brushCDC->SelectObject(oldBrush);
	return rst;
}

void Brushs::Draw(CPoint startPoint, CPoint endPoint) {
	if (brushCDC != NULL && mpoly != NULL) {
		mpoly->Draw(startPoint, endPoint, brushCDC);
	}
}



void Brushs::setDrawMode(int MODE, M_Polygon *dPoly) {
	DrawMode = MODE;
	mpoly = dPoly;
	//intf("DRAW MODE : %d\n", MODE);
	//intf("+ polygonList Size : %d\n", polygonList.size());
}

void Brushs::ReDrawAll() {
	if (brushCDC == NULL)return;
	//printf("Brushs RedrawAll & PolygonList Size : %d\n", polygonList.size());
	for (int i = 0; i < polygonList.size(); i++) {
		//printf("redrawing.. %d\n", i+1);
		//polygonList[i]->printPoint();
		if (polygonList[i]->isVisual) {
			if (polygonList[i]->getType() == D_MODE_LINE_DEPENDENCY || polygonList[i]->getType() == D_MODE_LINE_INHERITANCE) {
				polygonList[i]->ReDraw(brushCDC);
			}
		}//brushCDC->SelectObject(oldPen);
		//brushCDC->SelectObject(oldBrush);
	}
	for (int i = 0; i < polygonList.size(); i++) {
		if (polygonList[i]->isVisual) {
			if (polygonList[i]->getType() == D_MODE_CLASSDIAGRAM) {
				polygonList[i]->ReDraw(brushCDC);
			}
		}
	}
}

void Brushs::Redo() {
	if (!polygonBackUp.empty()) {
		polygonList.push_back(polygonBackUp.top());
		if (polygonList.back()->mpoly != NULL) {
			polygonList.back()->mpoly->isVisual = false;
		}
		polygonBackUp.pop();
	}
	else {
		printf("더 이상 되돌릴 작업이 없습니다.");
	}
}

void Brushs::Undo() {
	if (polygonList.size() != 0) {
		polygonBackUp.push(polygonList[polygonList.size() - 1]);
		if (polygonList.back()->mpoly != NULL) {
			polygonList.back()->mpoly->isVisual = true;
		}
		polygonList.pop_back();
	}
	else {
		printf("더 이상 제거할 작업이 없습니다.\n");
	}
}

void Brushs::setCPenColor() {
	brushPen.DeleteObject();
	brushPen.CreatePen(PS_SOLID, 1, RGB(0 , 0 , 0));
	//if (brushCDC != NULL) {
		oldPen = brushCDC->SelectObject(&brushPen); // 이전에 선택되어 있던 펜 객체를 리턴한다.
	//}
}

void Brushs::setPenMode(int MODE) {
	brushPen.DeleteObject();
	brushPen.CreatePen(MODE, 1, RGB(0, 0, 0));
	//if (brushCDC != NULL) {
		oldPen = brushCDC->SelectObject(&brushPen);
	//}
	printf("Penmode : %d\npsdot : %d\npssolid : %d", MODE, PS_DOT, PS_SOLID);
}


void Brushs::setCBrushColor() {
	brushBrush.DeleteObject();
	//brushBrush.CreateStockObject(NULL_BRUSH); // 도형 속 색상이 투명색
	brushBrush.CreateSolidBrush(RGB(255, 255, 153));
	//if (brushCDC != NULL) {
		oldBrush = brushCDC->SelectObject(&brushBrush); // 이전에 선택되어 있던 브러시 객체를 리턴한다.
	//}
}

void Brushs::saveData(CArchive& ar) {
	for (int i = 0; i < polygonList.size(); i++) {
		polygonList[i]->saveData(ar);
	}
}
void Brushs::addPolygon(M_Polygon* newPoly) {
	polygonList.push_back(newPoly);
}
void Brushs::deletePolygon() {
	polygonList.pop_back();
}

M_Polygon*  Brushs::findRect(CPoint point) {
	for (int i = 0; i < polygonList.size(); i++) {
		if (polygonList[i]->getType() == D_MODE_CLASSDIAGRAM) {
			CPoint startPos = polygonList[i]->getStartPoint();
			CPoint endPos = polygonList[i]->getEndPoint();
			CPoint tmp;
			if (startPos.x > endPos.x) {
				tmp = endPos;
				endPos.x = startPos.x;
				startPos.x = tmp.x;
			}
			if (startPos.y > endPos.y) {
				tmp = endPos;
				endPos.y = startPos.y;
				startPos.y = tmp.y;
			}

			CRect rect(startPos, endPos);

			if (rect.PtInRect(point)) {
				return polygonList[i];
			}
		}
	}
	return NULL;
}


void Brushs::reConnectLinesForLoadData() {
	for (int i = 0; i < polygonList.size(); i++) {
		if (polygonList[i]->getType() == D_MODE_LINE_DEPENDENCY ||
			polygonList[i]->getType() == D_MODE_LINE_INHERITANCE) {

			// Start Line
			M_Polygon* tempRect = findRect(polygonList[i]->startPoint);
			if (tempRect != NULL) {
				tempRect->addConnectedPoint(&(polygonList[i]->startPoint), &(polygonList[i]->endPoint));
			}
			
			// End Line
			tempRect = findRect(polygonList[i]->endPoint);
			if (tempRect != NULL)tempRect->addConnectedPoint(&(polygonList[i]->endPoint), &(polygonList[i]->startPoint));
			
		}

	}
}
