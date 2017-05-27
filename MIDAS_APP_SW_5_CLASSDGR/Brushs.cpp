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
		
		if (polygonList[i]->getType() == D_MODE_LINE_DEPENDENCY || polygonList[i]->getType() == D_MODE_LINE_INHERITANCE) {
			polygonList[i]->ReDraw(brushCDC);
		}//brushCDC->SelectObject(oldPen);
		//brushCDC->SelectObject(oldBrush);
	}
	for (int i = 0; i < polygonList.size(); i++) {
		if (polygonList[i]->getType() == D_MODE_CLASSDIAGRAM) {
			polygonList[i]->ReDraw(brushCDC);
		}
	}
}

void Brushs::Redo() {
	if (!polygonBackUp.empty()) {
		polygonList.push_back(polygonBackUp.top());
		polygonBackUp.pop();
	}
	else {
		printf("더 이상 되돌릴 작업이 없습니다.");
	}
}

void Brushs::Undo() {
	if (polygonList.size() != 0) {
		polygonBackUp.push(polygonList[polygonList.size() - 1]);
		polygonList.pop_back();
	}
	else {
		printf("더 이상 제거할 작업이 없습니다.\n");
	}
}

void Brushs::setCPenColor() {
	brushPen.DeleteObject();
	brushPen.CreatePen(PS_SOLID, 1, RGB(0 , 0 , 0));

	oldPen = brushCDC->SelectObject(&brushPen); // 이전에 선택되어 있던 펜 객체를 리턴한다.
}

void Brushs::setPenMode(int MODE) {
	brushPen.DeleteObject();
	brushPen.CreatePen(MODE, 1, RGB(0, 0, 0));

	oldPen = brushCDC->SelectObject(&brushPen);
	printf("Penmode : %d\npsdot : %d\npssolid : %d", MODE, PS_DOT, PS_SOLID);
}


void Brushs::setCBrushColor() {
	brushBrush.DeleteObject();
	//brushBrush.CreateStockObject(NULL_BRUSH); // 도형 속 색상이 투명색
	brushBrush.CreateSolidBrush(RGB(255, 255, 153));
	oldBrush = brushCDC->SelectObject(&brushBrush); // 이전에 선택되어 있던 브러시 객체를 리턴한다.
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