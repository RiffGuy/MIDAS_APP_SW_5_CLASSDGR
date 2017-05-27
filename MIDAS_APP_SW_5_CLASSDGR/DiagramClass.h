#pragma once
#include "M_Polygon.h"
#include "NewClassAddDLG.h"
#include <iostream>
class DiagramClass :
	public M_Polygon
{

public:
	int drawMode = 0;
	int WAIT = 0;
	int START = 1;
	int MOVE = 2;
	int END = 3;
	NewClassAddDLG* status;
	DiagramClass();
	DiagramClass(CPoint start, CPoint end);
	~DiagramClass();
	virtual bool Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList);
	virtual void Draw(CPoint startPoint, CPoint endPoint, CDC* pDC);
	virtual void ReDraw(CDC* pDC);
	inline virtual int getType() { return D_MODE_RECT; }
	inline virtual void setClassContents() {
		if (status == NULL) {
			status = new NewClassAddDLG();
		}
		status->DoModal();
	}

};

