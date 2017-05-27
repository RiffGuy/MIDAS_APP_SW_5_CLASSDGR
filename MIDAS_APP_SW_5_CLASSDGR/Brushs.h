#pragma once
#ifndef BRUSHS_H
#define BRUSHS_H

#include "M_Polygon.h"
#include "Dummy.h"
#include <vector>
#include <stack>
class Brushs
{
private:
	int DrawMode = D_MODE_NONE;
	bool undoFlag = false;
	CDC* brushCDC = NULL; // 그림을 그려주는 객체 , Brush 내에서 독자적으로 갖게 하여 색상 , 선 종류를 변경하기 용이하게 함
	CPen brushPen; // 선 종류를 결정
	CPen* oldPen;
	CBrush brushBrush; // 채우기 색상을 결정
	CBrush* oldBrush;
public:
	Brushs();
	~Brushs();
	M_Polygon* mpoly = NULL;
	CWnd* bWnd = NULL;

	void setBrushWnd(CWnd* pWnd);

	bool Draw(CPoint point, int flag, int dmode);
	void Draw(CPoint startPoint, CPoint endPoint);
	void setPenMode(int MODE);
	void setDrawMode(int MODE, M_Polygon *dPoly);
	int getDrawMode() { return DrawMode; }
	inline void TestDrawDot(CPoint point) {
		CClientDC dc(bWnd);
		dc.Rectangle(point.x - 1, point.y - 1, point.x + 1, point.y + 1);
	}

	inline void setCDC(CDC* pDC) {
		if(pDC != NULL)brushCDC = pDC;
		setCPenColor();
		setCBrushColor();
	}
	inline void InValidateAndUpdate() {
		if (bWnd != NULL) {
			bWnd->Invalidate();
			bWnd->UpdateWindow();
			//ReDrawAll();
		}
	}
	inline void eraseAllPolygonData() { while (polygonList.size() != 0)polygonList.pop_back(); }

	void ReDrawAll();

	std::vector<M_Polygon*> polygonList;
	std::stack<M_Polygon*> polygonBackUp;

	void Redo();
	void Undo();

	void setCPenColor();
	void setCBrushColor();
	void addPolygon(M_Polygon* newPoly);
	void deletePolygon();

	M_Polygon* getResentPolygon() {
		if (polygonList.size() > 0) {
			return polygonList[polygonList.size() - 1];
		}
		return NULL;
	};

	void saveData(CArchive& ar);

	void reConnectLinesForLoadData();
	M_Polygon* findRect(CPoint point);
};


#endif // !BRUSHS_H