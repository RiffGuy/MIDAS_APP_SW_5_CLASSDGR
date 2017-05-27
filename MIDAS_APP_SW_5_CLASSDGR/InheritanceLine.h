#pragma once
#include "Line.h"
class InheritanceLine : public Line
{
private:
	CPoint center;
	int drawMode = 0;
	int WAIT = 0;
	int START = 1;
	int MOVE = 2;
	int END = 3;
public:
	InheritanceLine();
	InheritanceLine(CPoint centerPoint);
	InheritanceLine(CPoint start, CPoint end);
	inline virtual int getType() { return D_MODE_LINE_INHERITANCE; }
	~InheritanceLine();
	virtual bool Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList);
	virtual void ReDraw(CDC* pDC);
};

