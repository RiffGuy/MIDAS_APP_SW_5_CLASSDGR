#pragma once
#ifndef LINE_H
#define LINE_H
#include "M_Polygon.h"
class Line :
	public M_Polygon
{
public:
	int drawMode = 0;
	int WAIT = 0;
	int START = 1;
	int MOVE = 2;
	int END = 3;
	Line();
	Line(CPoint start, CPoint end);
	~Line();
	virtual bool Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList);
	virtual void Draw(CPoint startPoint, CPoint endPoint, CDC* pDC);
	virtual void ReDraw(CDC* pDC);
	inline virtual int getType() { return D_MODE_LINE; }
	virtual void saveData(CArchive& ar);
};
#endif // !LINE_H


