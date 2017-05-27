#include "stdafx.h"
#include "Brushs.h"
//#include "Resource.h"

//�귣ġ ���� ����
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
	//intf("Brushs RedrawAll & PolygonList Size : %d\n", polygonList.size());
	for (int i = 0; i < polygonList.size(); i++) {
		//printf("redrawing.. %d\n", i+1);
		//polygonList[i]->printPoint();
		polygonList[i]->ReDraw(brushCDC);
		//brushCDC->SelectObject(oldPen);
		//brushCDC->SelectObject(oldBrush);
	}
}

void Brushs::Redo() {
	if (!polygonBackUp.empty()) {
		polygonList.push_back(polygonBackUp.top());
		polygonBackUp.pop();
	}
	else {
		printf("�� �̻� �ǵ��� �۾��� �����ϴ�.");
	}
}

void Brushs::Undo() {
	if (polygonList.size() != 0) {
		polygonBackUp.push(polygonList[polygonList.size() - 1]);
		polygonList.pop_back();
	}
	else {
		printf("�� �̻� ������ �۾��� �����ϴ�.\n");
	}
}

void Brushs::setCPenColor() {
	brushPen.DeleteObject();
	brushPen.CreatePen(PS_DOT, 3, RGB(255, 0, 0));

	oldPen = brushCDC->SelectObject(&brushPen); // ������ ���õǾ� �ִ� �� ��ü�� �����Ѵ�.
}

void Brushs::setCBrushColor() {
	brushBrush.DeleteObject();
	brushBrush.CreateStockObject(NULL_BRUSH);
	oldBrush = brushCDC->SelectObject(&brushBrush); // ������ ���õǾ� �ִ� �귯�� ��ü�� �����Ѵ�.
}

void Brushs::saveData(CArchive& ar) {
	for (int i = 0; i < polygonList.size(); i++) {
		polygonList[i]->saveData(ar);
	}
}