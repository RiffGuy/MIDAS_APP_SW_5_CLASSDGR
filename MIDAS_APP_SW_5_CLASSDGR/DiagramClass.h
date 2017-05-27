#pragma once
#include "M_Polygon.h"
#include "NewClassAddDLG.h"
#include <iostream>
#include <vector>
class DiagramClass :
	public M_Polygon
{
private:

public:
	int drawMode = 0;
	int WAIT = 0;
	int START = 1;
	int MOVE = 2;
	int END = 3;
	NewClassAddDLG* status;
	std::vector<CPoint*> lineList;
	DiagramClass();
	DiagramClass(CPoint start, CPoint end);
	~DiagramClass();
	inline virtual void printPoint() { printf("Diagram -> (%d,%d) ~ (%d,%d)\n", startPoint.x, startPoint.y, endPoint.x, endPoint.y); }
	virtual bool Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList);
	virtual void Draw(CPoint startPoint, CPoint endPoint, CDC* pDC);
	virtual void ReDraw(CDC* pDC);
	inline virtual int getType() { return D_MODE_CLASSDIAGRAM; }
	inline virtual void setContents() {
		if (status == NULL) {
			status = new NewClassAddDLG();
		}
		status->DoModal();
	}


	bool isClassContentsEmpty() {

		if (status->isEmpty()) {
			return true;
		}
		else {
			return false;
		}

	}

	virtual void saveData(CArchive& ar);
};

