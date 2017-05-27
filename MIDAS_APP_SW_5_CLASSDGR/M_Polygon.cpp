#include "stdafx.h"
#include "M_Polygon.h"
//#include "Resource.h"

M_Polygon::M_Polygon()
{
	startPoint = CPoint(0, 0);
	endPoint = CPoint(0, 0);
	isVisual = true;
	mpoly = NULL;
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
	//printf("HI? \n");
}

void M_Polygon::saveData(CArchive& ar) {
	// nothing
	printf("saveData in Polygon..\n");
}

void M_Polygon::addConnectedPoint(CPoint* p,CPoint* q) {
	
}

void M_Polygon::removeConnectedPoint() {

}

void M_Polygon::reConnectedPoint() {

}