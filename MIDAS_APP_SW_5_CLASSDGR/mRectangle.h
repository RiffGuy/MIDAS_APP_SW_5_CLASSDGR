#pragma once
#include "M_Polygon.h"
class mRectangle :
	public M_Polygon
{

public:
	int drawMode = 0;
	int WAIT = 0;
	int START = 1;
	int MOVE = 2;
	int END = 3;
	mRectangle();
	mRectangle(CPoint start, CPoint end);
	~mRectangle();
	virtual bool Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList);
	virtual void Draw(CPoint startPoint, CPoint endPoint, CDC* pDC);
	virtual void ReDraw(CDC* pDC);
	inline virtual int getType() { return D_MODE_RECT; }
};

