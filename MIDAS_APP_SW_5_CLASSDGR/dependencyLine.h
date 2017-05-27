#pragma once
#include "Line.h"
class dependencyLine : public Line
{
private:
	CPoint center;
	int drawMode;
	int START = 0;
	int MOVE = 1;
	int END = 2;
public:
	dependencyLine();
	dependencyLine(CPoint centerPoint);
	dependencyLine(CPoint start, CPoint end);
	inline virtual int getType() { return D_MODE_LINE_DEPENDENCY; }
	~dependencyLine();
	virtual bool Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList);
	virtual void ReDraw(CDC* pDC);
};

