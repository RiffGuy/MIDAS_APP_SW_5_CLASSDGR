#pragma once
#ifndef M_POLYGON_H
#define M_POLYGON_H
#include "Resource.h"
#include <vector>
class M_Polygon
{

protected:
	
	CDC* pDC;
public:
	CPoint startPoint;
	CPoint endPoint;
	bool isVisual;
	M_Polygon* mpoly;
	M_Polygon* parentPoly;
	M_Polygon();
	~M_Polygon();
	inline virtual void printPoint() { printf("-> (%d,%d) ~ (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y); }
	inline void setCDC(CDC* _pDC) { pDC = _pDC; }
	virtual bool Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList);
	virtual void Draw(CPoint startPoint, CPoint endPoint, CDC* pDC);
	virtual void ReDraw(CDC* pDC);
	virtual void addConnectedPoint(CPoint* p, CPoint* q);
	virtual void removeConnectedPoint();
	virtual void reConnectedPoint();
	inline virtual int getType() { return D_MODE_NONE; }
	inline CPoint getStartPoint() { return startPoint; }
	inline CPoint getEndPoint() { return endPoint; }
	inline void setStartPoint(CPoint point) { startPoint = point; }
	inline void setEndPoint(CPoint point) { endPoint = point; }
	inline virtual void setContents() {}
	virtual void saveData(CArchive& ar);
};
#endif // !M_POLYGON_H


