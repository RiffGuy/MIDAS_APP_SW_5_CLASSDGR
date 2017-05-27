#include "stdafx.h"
#include "M_Polygon.h"
//#include "Resource.h"

M_Polygon::M_Polygon()
{

}


M_Polygon::~M_Polygon()
{

}

void M_Polygon::Draw(CPoint startPoint, CPoint endPoint, CDC* pDC) {

}

bool M_Polygon::Draw(CPoint point, int flag, int dmode, CDC* pDC, std::vector<M_Polygon*>* saveList) {
	//printf("DRAW - M_Polygon\n");
	return false;
}

void M_Polygon::ReDraw(CDC* pDC) {
	printf("HI? \n");
}

