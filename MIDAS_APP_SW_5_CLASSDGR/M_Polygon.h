#pragma once
#ifndef M_POLYGON_H
#define M_POLYGON_H
#include "Resource.h"
#include <vector>
class M_Polygon
{

protected:
	CPoint startPoint;
	CPoint endPoint;
	CDC* pDC;
public:
	M_Polygon();
	~M_Polygon();
	inline void printPoint() { printf("-> (%d,%d) ~ (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y); }
	inline void setCDC(CDC* _pDC) { pDC = _pDC; }
	virtual bool Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList);
	virtual void Draw(CPoint startPoint, CPoint endPoint, CDC* pDC);
	virtual void ReDraw(CDC* pDC);
	inline virtual int getType() { return D_MODE_NONE; }
	inline CPoint getStartPoint() { return startPoint; }
	inline CPoint getEndPoint() { return endPoint; }
	inline void setStartPoint(CPoint point) { startPoint = point; }
	inline void setEndPoint(CPoint point) { endPoint = point; }

};
#endif // !M_POLYGON_H


