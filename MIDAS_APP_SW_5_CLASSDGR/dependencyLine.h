#pragma once
#include "Line.h"
class dependencyLine : public Line
{
private:
	CPoint center;
	int drawMode = 0;
	int WAIT = 0;
	int START = 1;
	int MOVE = 2;
	int END = 3;
public:
	dependencyLine();
	dependencyLine(CPoint centerPoint);
	dependencyLine(CPoint start, CPoint end);
	inline virtual int getType() { return D_MODE_LINE_DEPENDENCY; }
	~dependencyLine();
	virtual bool Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList);
	virtual void ReDraw(CDC* pDC);
	virtual void addConnectedPoint(CPoint* p, CPoint* q);
	virtual void removeConnectedPoint();
	virtual void reConnectedPoint();
	virtual void saveData(CArchive& ar);
};

