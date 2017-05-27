#pragma once
#include "Line.h"
class InheritanceLine : public Line
{
private:
	CPoint center;
	int drawMode;
	int START = 0;
	int MOVE = 1;
	int END = 2;
	int STOP = 3;
public:
	InheritanceLine();
	InheritanceLine(CPoint centerPoint);
	InheritanceLine(CPoint start, CPoint end);
	inline virtual int getType() { return D_MODE_LINE_INHERITANCE; }
	~InheritanceLine();
	virtual bool Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList);
	virtual void ReDraw(CDC* pDC);
};

